.data
A: .word 27,20,2,24,7,19,2,10,10,22

.text
la   x10, A          # put the base address of array A in x10
addi x11, x0, 10     # put the length of array A in x11
addi x5,  x0, 0      # the temperary variable i
addi x6,  x0, 0      # the temperary variable j
addi x7,  x0, 0      # the temperary variable temp

## insert your code here
outer_loop:                    # for (i = 0; i < LENGTH; i++)
    bge  x5, x11, exit
    addi x6, x5,  1            # j = i + 1

inner_loop:                    #for (j = i + 1; j < LENGTH; j++)
    bge  x6,  x11, outer_end    
    # load the A[i]
    slli x12, x5,  2                  # x12 = i * 4
    add  x8,  x10, x12                # x8  = A + i * 4
    lw   x28, 0(x8)                   # x28 = A[i]

    # load the A[j]
    slli x13, x6,  2                  # x13  = j * 4
    add  x9,  x10, x13                # x9  = A + j * 4
    lw   x29, 0(x9)                   # x29 = A[j]

    # compare A[i]>A[j]
    ble  x28, x29, no_swap
    add  x7,  x28, x0                 # temp  = A[i]
    sw   x29, (0)x8                   # A[i]  = A[j]
    sw   x7,  (0)x9                   # A[j]  = temp

no_swap:
    addi x6,  x6, 1
    jal  x0,  inner_loop

outer_end:
    addi x5,  x5, 1
    jal  x0,  outer_loop

exit:
    nop
