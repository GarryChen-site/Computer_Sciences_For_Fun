.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
	# Prologue
	li t0, 1 # set cmp length to 1
	blt a1, t0, exception # if length is less than 1, exit
	mv t0, x0 # reset index to 0
	mv t3, x0 # set maximum element index to zero

loop_start:
	slli t1, t0, 2 # calculate the offset
	add t1, a0, t1 # calculate the address of the element
	lw t2, 0(t1) # load the element
	beq t0, x0, cache_first # if it's the first element, cache it
	bgt t2, t4, update_index # if it's greater than the current max, update the index
	j loop_continue # otherwise, continue

cache_first:
	lw t4, 0(t1) # cache the first element
	j loop_continue

update_index:
	mv t3, t0 # update the index
	mv t4, t2 # update the max element

loop_continue:
	addi t0, t0, 1 # increment the index
	blt t0, a1, loop_start # if we haven't reached the end, continue
	j loop_end # otherwise, end the loop

exception:
	li a0, 36
	j exit

loop_end:
	# Epilogue
	mv a0, t3 # return the index
	ret
