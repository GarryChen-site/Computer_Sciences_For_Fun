/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 *
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "wilson",
    /* First member's full name */
    "Garry Chen",
    /* First member's email address */
    "GarryChen@cs.cmu.edu",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define WSIZE 4
#define DSIZE 8

#define CHUNKSIZE (1 << 12)

#define LISTMAX 16

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) > (y) ? (y) : (x))

#define PACK(size, alloc) ((size) | (alloc))


#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (val))

#define SET_PTR(p, ptr) (*(unsigned int *)(p) = (unsigned int)(ptr))

#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)

#define HDRP(bp) ((char *)(bp)-WSIZE)
#define FTRP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)) - DSIZE)

#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(((char *)(bp)-WSIZE)))
#define PREV_BLKP(bp) ((char *)(bp)-GET_SIZE(((char *)(bp)-DSIZE)))

#define PRED_PTR(bp) ((char *)(bp))
#define SUCC_PTR(bp) ((char *)(bp) + WSIZE)

// get the predecessor block
#define PRED(bp) (*(char **)(bp))
// get the successor block
#define SUCC(bp) (*(char **)(SUCC_PTR(bp)))

void *segregated_free_lists[LISTMAX];

static void *extend_heap(size_t size);
static void *coalesce(void *bp);
static void *place(void *bp, size_t size);
/* insert free block into segregated free list */
static void insert_node(void *bp, size_t size);
/* delete free block from segregated free list */
static void delete_node(void *bp);

static void *extend_heap(size_t size)
{
    void *ptr;
    size = ALIGN(size);

    if ((ptr = mem_sbrk(size)) == (void *)-1)
        return NULL;

    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));
    // epilogue block
    PUT(HDRP(NEXT_BLKP(ptr)), PACK(0, 1));

    insert_node(ptr, size);

    return coalesce(ptr);
}

static void insert_node(void *ptr, size_t size) 
{
    int listNum = 0;
    void *search_ptr = NULL;
    void *insert_ptr = NULL;

    // find the proper list to insert
    while ((listNum < LISTMAX - 1) && (size > 1))
    {
        size >>= 1;
        listNum++;
    }

    // after find the list, search the list to find the proper place to insert
    search_ptr = segregated_free_lists[listNum];
    while ((search_ptr != NULL) && (size > GET_SIZE(HDRP(search_ptr))))
    {
        insert_ptr = search_ptr;
        search_ptr = PRED(search_ptr);
    }

    if (search_ptr != NULL)
    {
        if (insert_ptr != NULL)
        {
            // xx -> insert -> xx
            SET_PTR(PRED_PTR(ptr), search_ptr);
            SET_PTR(SUCC_PTR(search_ptr), ptr);
            SET_PTR(SUCC_PTR(ptr), insert_ptr);
            SET_PTR(PRED_PTR(insert_ptr), ptr);
        }
        else
        {
            // [listNum] -> insert -> xx, insert in head, but there are free blocks in the list
            SET_PTR(PRED_PTR(ptr), search_ptr);
            SET_PTR(SUCC_PTR(search_ptr), ptr);
            SET_PTR(SUCC_PTR(ptr), NULL);
            segregated_free_lists[listNum] = ptr;
        }
    }
    else
    {
        if (insert_ptr != NULL)
        {
            // -> xx -> insert
            SET_PTR(PRED_PTR(ptr), insert_ptr);
            SET_PTR(SUCC_PTR(insert_ptr), ptr);
            SET_PTR(SUCC_PTR(ptr), NULL);
        }
        else
        {
            // insert to the first place, and the list is empty
            SET_PTR(PRED_PTR(ptr), NULL);
            SET_PTR(SUCC_PTR(ptr), insert_ptr);
            segregated_free_lists[listNum] = ptr;
        }
    }

}

static void delete_node(void *ptr)
{
    int listNum = 0;
    size_t size = GET_SIZE(HDRP(ptr));

    while ((listNum < LISTMAX - 1) && (size > 1))
    {
        size >>= 1;
        listNum++;
    }

    if (PRED(ptr) != NULL)
    {
        if (SUCC(ptr) != NULL)
        {
            // xx -> ptr -> xx
            SET_PTR(SUCC_PTR(PRED(ptr)), SUCC(ptr));
            SET_PTR(PRED_PTR(SUCC(ptr)), PRED(ptr));
        }
        else
        {
            // [listNum] -> ptr -> xx, same as insert_node
            SET_PTR(SUCC_PTR(PRED(ptr)), NULL);
            segregated_free_lists[listNum] = PRED(ptr);
        }
    }
    else
    {
        if (SUCC(ptr) != NULL)
        {
            // [listNum] -> ptr -> xx
            SET_PTR(PRED_PTR(SUCC(ptr)), NULL);
        }
        else
        {
            // [listNum] -> ptr -> xx
            segregated_free_lists[listNum] = NULL;
        }
    }
}

static void *coalesce(void *ptr)
{
    size_t prev_alloc = GET_ALLOC(HDRP(PREV_BLKP(ptr)));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(ptr)));
    size_t size = GET_SIZE(HDRP(ptr));

    // case 1
    if (prev_alloc && next_alloc)
    {
        return ptr;
    }
    // case 2
    else if (prev_alloc && !next_alloc)
    {
        delete_node(ptr);
        delete_node(NEXT_BLKP(ptr));
        size += GET_SIZE(HDRP(NEXT_BLKP(ptr)));
        PUT(HDRP(ptr), PACK(size, 0));
        PUT(FTRP(ptr), PACK(size, 0));
    }
    // case 3
    else if (!prev_alloc && next_alloc)
    {
        delete_node(ptr);
        delete_node(PREV_BLKP(ptr));
        size += GET_SIZE(HDRP(PREV_BLKP(ptr)));
        PUT(FTRP(ptr), PACK(size, 0));
        PUT(HDRP(PREV_BLKP(ptr)), PACK(size, 0));
        ptr = PREV_BLKP(ptr);
    }
    // case 4
    else
    {
        delete_node(ptr);
        delete_node(PREV_BLKP(ptr));
        delete_node(NEXT_BLKP(ptr));
        size += GET_SIZE(HDRP(PREV_BLKP(ptr))) + GET_SIZE(FTRP(NEXT_BLKP(ptr)));
        PUT(HDRP(PREV_BLKP(ptr)), PACK(size, 0));
        PUT(FTRP(NEXT_BLKP(ptr)), PACK(size, 0));
        ptr = PREV_BLKP(ptr);
    }

    insert_node(ptr, size);
    return ptr;
}

static void *place(void *ptr, size_t size) 
{
    size_t ptr_size = GET_SIZE(HDRP(ptr));

    size_t remainder = ptr_size - size;

    if (remainder < DSIZE * 2)
    {
        PUT(HDRP(ptr), PACK(ptr_size, 1));
        PUT(FTRP(ptr), PACK(ptr_size, 1));
    }
    else 
    {
        PUT(HDRP(ptr), PACK(size, 1));
        PUT(FTRP(ptr), PACK(size, 1));
        PUT(HDRP(NEXT_BLKP(ptr)), PACK(remainder, 0));
        PUT(FTRP(NEXT_BLKP(ptr)), PACK(remainder, 0));
        insert_node(NEXT_BLKP(ptr), remainder);
    }
    return ptr;

}

/*
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    int listNum;
    char *heap;

    for (listNum = 0; listNum < LISTMAX; listNum++)
    {
        segregated_free_lists[listNum] = NULL;
    }

    if ((long)(heap = mem_sbrk(4 * WSIZE)) == -1)
        return -1;
    
    PUT(heap, 0);
    PUT(heap + (1 * WSIZE), PACK(DSIZE, 1));
    PUT(heap + (2 * WSIZE), PACK(DSIZE, 1));
    PUT(heap + (3 * WSIZE), PACK(0, 1));

    if (extend_heap(CHUNKSIZE / WSIZE) == NULL)
        return -1;

    return 0;
}

/*
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    if (size == 0) 
    {
        return NULL;
    }
    if (size <= DSIZE) 
    {
        size = 2 * DSIZE;
    }
    else 
    {
        size = ALIGN(size + DSIZE);
    }

    int listNum = 0;
    size_t searchSize = size;
    void *ptr = NULL;

    while(listNum < LISTMAX)
    {
        if (((searchSize <= 1) && (segregated_free_lists[listNum] != NULL)))
        {
            ptr = segregated_free_lists[listNum];
            while ((ptr != NULL) && ((size > GET_SIZE(HDRP(ptr)))))
            {
                ptr = PRED(ptr);
            }
            if (ptr != NULL)
            {
                break;
            }
        }
        searchSize >>= 1;
        listNum++;
    }

    if (ptr == NULL)
    {
        if ((ptr = extend_heap(MAX(size, CHUNKSIZE))) == NULL)
        {
            return NULL;
        }
    }

    ptr = place(ptr, size);

    return ptr;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    size_t size = GET_SIZE(HDRP(ptr));

    PUT(HDRP(ptr), PACK(size, 0));
    PUT(FTRP(ptr), PACK(size, 0));

    insert_node(ptr, size);
    coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *new_block = ptr;

    int remainder;

    if (size == 0)
    {
        return NULL;
    }

    if (size <= DSIZE)
    {
        size = 2 * DSIZE;
    }
    else
    {
        size = ALIGN(size + DSIZE);
    }

    if ((remainder = GET_SIZE(HDRP(ptr)) - size) >= 0)
    {
        return ptr;
    }
    // next block is free or epilogue block
    else if (!GET_ALLOC(HDRP(NEXT_BLKP(ptr))) || !GET_SIZE(HDRP(NEXT_BLKP(ptr)))) 
    {
        // extend_heap if add the size of next block is not enough
        if ((remainder = GET_SIZE(HDRP(ptr)) +GET_SIZE(HDRP(NEXT_BLKP(ptr))) - size) < 0)
        {
            if (extend_heap(MAX(-remainder, CHUNKSIZE)) == NULL)
            {
                return NULL;
            }
            remainder += MAX(-remainder, CHUNKSIZE);
        }
        // delete the next block from segregated free list
        delete_node(NEXT_BLKP(ptr));
        PUT(HDRP(ptr), PACK(size + remainder, 1));
        PUT(FTRP(ptr), PACK(size + remainder, 1));
    }
    // no consecutive free block
    else 
    {
        new_block = mm_malloc(size);
        memcpy(new_block, ptr, MIN(size, GET_SIZE(HDRP(ptr))));
        mm_free(ptr);
    }
    return new_block;
}
