# DO NOT REMOVE THIS LINE WHEN SUBMITTING
.import input.S
# to interatct with input.s
.text
# text seg
.globl	main
# print a number
print_int:
  mv a1, a0 # a1 to pass ecall
  li a0, 1 # 1 for print_int
  ecall # call the ecall
  ret # return

# print a space
print_space:
  li a1, 32 # ' ' == 32
  li a0, 11 # 11 for print_character
  ecall # call the ecall
  ret # return

# print a '\n'
print_line:
  li a1, 10 # '\n' == 10
  li a0, 11 # 11 for print_character
  ecall # call the ecall
  ret # return

# insert a0 into heap
heap_insert:
  la t0, len # get &len
  lw t1, 0(t0) # get len
  li t2, 32 # max len = 32
  beq t1, t2, error_exit # error, overflow
  addi t1, t1, 1
  sw t1, 0(t0) # ++len;
  # t1 = n
  la t0, heap
  # t0 = d
  addi t0, t0, -4 # 1-indexed heap
  slli t2, t1, 2 # t2 = len * 4
  add t2, t2, t0 # t2 = &heap[len]
  sw a0, 0(t2) # heap[len] = a0
  # t2 = k = n
  mv t2, t1
  heap_shift_up_loop:
    li t3, 1 # for compare k < 1
    ble t2, t3, heap_shift_up_loop_done # if (k < 1) break;
    srli t3, t2, 1 # t3 = k >> 1
    slli t3, t3, 2 # t3 = (k >> 1) * 4
    add t3, t3, t0 # t3 = &d[k >> 1]
    slli t4, t2, 2 # t4 = t2 * 4
    add t4, t4, t0 # t4 = &d[k]
    lw t5, 0(t3) # t5 = d[k >> 1]
    lw t6, 0(t4) # t6 = d[k]
    bge t6, t5, heap_shift_up_loop_done # if (d[k] >= d[k >> 1]) break;
    # std::swap(d[k], d[k >> 1]);
    sw t5, 0(t4) # d[k] = t5;
    sw t6, 0(t3) # d[k >> 1] = t6
    srli t2, t2, 1 # k >>= 1
    j heap_shift_up_loop # continue loop

  heap_shift_up_loop_done:
  ret # return

# shift down heap
heap_shift_down:
  # int *d = a0
  # int k = a1
  # int n = a2
  heap_shift_down_loop:
    # int nk = k << 1
    slli t0, a1, 1
    # t0 = nk
    bgt t0, a2, heap_shift_down_loop_done # if (nk > n) break;
    ori t1, t0, 1 # t1 = t0 | 1
    bgt t1, a2, heap_shift_down_nk_done # no need for nk | 1
    slli t2, t0, 2 # t2 = nk * 4
    add t2, t2, a0 # t2 = &d[nk]
    lw t2, 0(t2) # t2 = d[nk]
    slli t3, t1, 2 # t3 = (nk | 1) * 4
    add t3, t3, a0 # t3 = &d[nk | 1]
    lw t3, 0(t3) # t3 = d[nk | 1]
    bge t3, t2, heap_shift_down_nk_done # if (d[nk | 1] < d[nk])
    ori t0, t0, 1 # nk |= 1
    heap_shift_down_nk_done:
    slli t2, t0, 2 # t2 = nk * 4
    add t2, t2, a0 # t2 = &d[nk]
    lw t2, 0(t2) # t2 = d[nk]
    slli t1, a1, 2 # t1 = k * 4
    add t1, t1, a0 # t1 = &d[k]
    lw t1, 0(t1) # t1 = d[k]
    bge t2, t1, heap_shift_down_loop_done # if (d[nk] >= d[k]) break;
    # std::swap(d[nk], d[k]), t1 = d[k], t2 = d[nk]
    slli t3, a1, 2 # t3 = k * 4
    add t3, t3, a0 # t3 = &d[k]
    sw t2, 0(t3) # d[k] = t2
    slli t3, t0, 2 # t3 = nk * 4
    add t3, t3, a0 # t3 = &d[nk]
    sw t1, 0(t3) # d[nk] = t1

    mv a1, t0 # k = nk
    j heap_shift_down_loop # continue loop

  heap_shift_down_loop_done:
  ret # return

# pop heap
heap_pop:
  addi sp, sp, -4 # move stack
  sw ra, 0(sp) # save ra

  la t0, len # get &len
  lw t1, 0(t0) # get len
  beqz t1, error_exit # if len == 0, underflow
  addi t1, t1, -1 # --len because of pop
  sw t1, 0(t0)
  la t2, heap # get &heap
  lw a0, 0(t2) # get heap[0]
  jal print_int # print(heap[0])
  jal print_line # print('\n')
  slli t3, t1, 2 # t3 = (old_len - 1) * 4
  add t3, t3, t2 # t3 = &heap[old_len - 1]
  lw t3, 0(t3) # t3 = heap[old_len - 1]
  sw t3, 0(t2) # heap[0] = heap[n - 1]
  mv a0, t2 # a0 = &heap[0]
  addi a0, a0, -4 # move a0 forward because I want to use 1-indexed array
  li a1, 1 # root
  mv a2, t1 # n = len
  jal heap_shift_down # down(heap - 1, 1, n)

  lw ra, 0(sp) # reload ra
  addi sp, sp, 4 # free stack
  ret # return

# print heap
heap_print:
  addi sp, sp, -4 # move stack
  sw ra, 0(sp) # save ra
  la t0, heap # t0 = &heap
  addi t0, t0, -4 # for 1-indexed array
  la t1, len # t1 = &len
  lw t1, 0(t1) # t1 = len
  li t2, 1 # i = 1
  heap_print_loop:
    bge t2, t1, heap_print_loop_done # if (i >= len) break
    slli a0, t2, 2 # a0 = i * 4
    add a0, a0, t0 # a0 = &heap[i]
    lw a0, 0(a0) # a0 = &heap[i]
    jal print_int # print(a0)
    jal print_space # print(' ')
    addi t2, t2, 1 # i++;
    j heap_print_loop

  heap_print_loop_done: # for last element
    bne t2, t1, heap_print_return
    slli t3, t2, 2 # t3 = len * 4
    add t3, t3, t0 # t3 = &heap[len]
    lw a0, 0(t3) # t3 = heap[len]
    jal print_int # print(t3)
    jal print_line # print('\n')
  
  heap_print_return:
  lw ra, 0(sp) # reload ra
  addi sp, sp, 4 # free stack
  ret # return

# exit with -1
error_exit:
  li a1, -1 # exit status with -1
  li a0, 17 # 17 for exit2
  ecall # ecall

# main function
main:
  addi sp, sp, -8 # move stack to store
  sw s1, 0(sp) # save s1
  sw s2, 4(sp) # save s2
  la s1, input_len # get the input_len
  lw s1, 0(s1) # s1 = input_len
  la s2, input # s2 = &input[0]

  input_loop:
    # while (input_len)
    beqz s1, input_loop_done
    lw a0, 0(s2) # a0 = *s1, get the input number
    bge a0, x0, input_insert # >= 0, insert the number
    li t0, -1 # set t0 = -1 to compare a0 == -1
    beq a0, t0, input_pop # jump to pop
    li t0, -2 # set t0 = -2 to compare a0 == -2
    beq a0, t0, input_print # print heap
    input_insert: # insert
      jal heap_insert
      j input_continue # skip the process below
    input_pop: # pop
      jal heap_pop
      j input_continue # skip the process below
    input_print: # print
      jal heap_print
    input_continue: # continue the loop
    addi s2, s2, 4 # s1++;
    addi s1, s1, -1 # --input_len;
    j input_loop # continue the loop

  input_loop_done: # loop done

  lw s1, 0(sp) # reload s1
  lw s2, 4(sp) # reload s2
  addi sp, sp, 8
  mv a1, zero # set exit status to 0
  li a0, 17 # exit(0)
  ecall