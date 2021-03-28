.data

# Input array
# Non-negative integers are insert operations.
# -1 is the pop operation.
# You should print the popped item, while maintaining the heap property.
# -2 is the print heap operation.
# You should the print the internal representation (array) of the heap.
# DO NOT MODIFY THIS VARIABLE
.globl	input
input:
	.word	0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31 32

# Constant integer specifying the number of operations
# DO NOT MODIFY THIS VARIABLE
.globl  input_len
input_len:
        .word  33

# Statically allocated array for the heap data structure
# You may assume that the maximum capacity is 32.
# Any operation that causes the array to hold more than 32 elements is an overflow.
.globl	heap
heap:
	.word	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

# Global variable that holds the current length of the heap
# You should modify this variable accordingly when inserting or popping elements.
.globl	len
len:
	.word	0
