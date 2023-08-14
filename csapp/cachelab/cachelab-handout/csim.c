#include "cachelab.h"

#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verbose = 0, s, E, b, S, B;

int T = 0; // time variable for LRU
typedef __uint64_t uint64_t;
typedef struct lineNode {
    int valid;
    int t; // time
    uint64_t tag;
} * groutNode;


enum Category {HIT, MISS, EVICTION};
unsigned int resutl[3];
const char *categoryString[3] = {"hit ", "miss ", "eviction "};
groutNode *cache;

void init();
void destory();

FILE *opt(int argc, char **argv);
unsigned int result[3];
void findCache(uint64_t tag, int pos, char *result);

void print_usage() {
    printf("Usage: ./csim-ref [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n");
}

int main(int argc, char **argv)
{
    FILE *tracefile = opt(argc, argv);

    init();

    char oper[2];
    uint64_t addr;
    int size;

    while(fscanf(tracefile, "%s %lx,%d", oper, &addr, &size) != EOF) {
        if (oper[0] == 'I') {
            continue;
        }
        int group_pos = (addr >> b) & ~(~0u << s);
        uint64_t tag = addr >> (s + b);
        char resultV[20];
        memset(resultV, 0, sizeof(resultV));
        T++;
        findCache(tag, group_pos, resultV);
        if(oper[0] == 'M') {
            findCache(tag, group_pos, resultV);
        }
        if (verbose) {
            fprintf(stdout, "%s %lx,%d %s\n", oper, addr, size, resultV);
        }
    }
    printSummary(result[0], result[1], result[2]);

    return 0;
}

void init() {
    cache = (groutNode *)malloc(sizeof(groutNode) * S);
    for (int i = 0; i < S; i++) {
        // each set has E lines
        cache[i] = (groutNode)malloc(sizeof(struct lineNode) * E);
        for (int j = 0; j < E; j++) {
            cache[i][j].valid = 0;
            cache[i][j].tag = 0;
            cache[i][j].t = 0;
        }
    }
}

void destory() {
    for (int i = 0; i < S; i++) {
        free(cache[i]);
    }
    free(cache);
}

void setResult(groutNode group, enum Category category, int tag, int pos, char *resultV) {
    result[category]++;
    
    group[pos].tag = tag;
    group[pos].t = T;
    group[pos].valid = 1;

    if (verbose) {
        strcat(resultV, categoryString[category]);
    }
}

void findCache(uint64_t tag, int pos, char *result) {
    groutNode line = cache[pos];
    int min_t_pos = 0, empty_line = -1;
    for (int i=0; i<E; i++) {
        struct lineNode node = line[i];
        if (!node.valid) {
            empty_line = i;
        } else {
            //hit
            if (node.tag == tag) {
                setResult(line, HIT, tag, i, result);
                return;
            }
            if (line[min_t_pos].t > node.t) {
                min_t_pos = i;
            }
        }
    }
    setResult(line, MISS, tag, empty_line, result);
    if (empty_line == -1) {
        // evict happens
        setResult(line, EVICTION, tag, min_t_pos, result);
    }
}

FILE *opt(int argc, char **argv)
{
    FILE *tracefile;

    for(int c; (c = getopt(argc, argv, "hvsEbt")) != EOF;){
        switch (c) {
            case 'h':
                print_usage();
                break;
            case 'v':
                verbose = 1;
                break;
            case 's':
                s = atoi(argv[optind]);
                if (s <= 0) {
                    printf("s must be a positive integer\n");
                    exit(1);
                }
                S = 1 << s;
                break;
            case 'E':
                E = atoi(argv[optind]);
                if (E <= 0) {
                    printf("E must be a positive integer\n");
                    exit(1);
                }
                break;
            case 'b':
                b = atoi(argv[optind]);
                if (b <= 0) {
                    printf("b must be a positive integer\n");
                    exit(1);
                }
                B = 1 << b;
                break;
            case 't':
                printf("tracefile: %s\n", optarg);
                tracefile = fopen(argv[optind], "r");
                if (tracefile == NULL) {
                    printf("tracefile not found\n");
                    exit(1);
                }
                break;
        }
    }
    return tracefile;
}