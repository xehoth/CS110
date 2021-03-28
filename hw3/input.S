.data
.globl input
input:
.word 51 13 80 -1 35 -2 -1 26 -1 -2 -2 -2 13 55 -1 42 -1 -1 33 -1 14 64 78 61 -1 96 16 -2 -1 35 -2 66 -2 -1 23 16 83 57 
.globl input_len
input_len:
.word 38

.globl	heap
heap:
	.word	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

# Global variable that holds the current length of the heap
# You should modify this variable accordingly when inserting or popping elements.
.globl	len
len:
	.word	0
  