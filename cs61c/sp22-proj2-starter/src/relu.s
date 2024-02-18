.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
	# Prologue
	li t0, 1 # set cmp length to 1
	blt a1, t0, exception # if length is less than 1, exit
	mv t0, x0 # reset index to a0

loop_start:
	slli t1, t0, 2 # multiply index by 4
	add t1, a0, t1 # add index to array
	lw t2, 0(t1) # load value from array
	blt t2, x0, set_zero # if value is less than 0, set to 0

loop_continue:
	addi t0, t0, 1 # increment index
	blt t0, a1, loop_start # if index is less than length, loop again
	j loop_end # else, end loop

set_zero:
	sw x0, 0(t1) # set value to 0
	j loop_continue

exception:
	li a0, 36
	j exit

loop_end:
	# Epilogue
	ret
