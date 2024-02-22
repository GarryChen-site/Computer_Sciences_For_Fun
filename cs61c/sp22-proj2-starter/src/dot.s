.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:

	li t0, 1 # error detection
	blt a2, t0, array_len_err # if array length is less than 1, terminate the program with error code 36
	blt a3, t0, stride_len_err # if stride of arr0 is less than 1, terminate the program with error code 37
	blt a4, t0, stride_len_err # if stride of arr1 is less than 1, terminate the program with error code 37
	mv t0, x0 # reset counter to 0
	mv t5, x0 # reset result to 0


loop_start:
	# process the first element
	mul t1, a3, t0 # step stride
	slli t1, t1, 2 # convert to byte
	add t1, a0, t1 # get the address of the element
	lw t3, 0(t1) # load the element

	# process the second element
	mul t2, a4, t0 # step stride
	slli t2, t2, 2 # convert to byte
	add t2, a1, t2 # get the address of the element
	lw t4, 0(t2) # load the element

	# sum
	mul t3, t3, t4 # reuse t3 to store the product
	add t5, t5, t3 # accumulate the result
	addi t0, t0, 1 # increment counter
	bge t0, a2, loop_end # if counter >= a2, terminate the loop
	j loop_start # otherwise, continue the loop

array_len_err:
    li      a0, 36
    j       exit
stride_len_err:
    li      a0, 37
    j       exit


loop_end:

	# Epilogue

	mv 	a0, t5
	ret
