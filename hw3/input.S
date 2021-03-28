.data
.globl input
input:
.word 76 32 -2 57 -2 20 -2 -1 -2 81 -1 -2 78 -2 15 47 21 32 -2 42 13 -2 14 3 30 -2 -1 2 -2 11 -1 71 16 7 -1 10 83 69 25 30 86 44 3 49 16 -2 -1 -2 -1 -1 6 
.globl input_len
input_len:
.word 51

.globl	heap
heap:
	.word	0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

# Global variable that holds the current length of the heap
# You should modify this variable accordingly when inserting or popping elements.
.globl	len
len:
	.word	0
  