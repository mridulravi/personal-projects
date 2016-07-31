
###########################
####  text segment   #####
###########################

.text
.globl main
main:


li $v0, 4
la $a0, msg1
syscall                     # display to take input v
li $v0, 5
syscall
move $t1, $v0               # take as input v, and put it into $t1

li $v0, 4
la $a0, msg2
syscall                     # display to take input w
li $v0, 5
syscall
move $t2, $v0               # take as input w, and put it into $t2


li $v0, 4
la $a0, msg3
syscall                     # display to take input x
li $v0, 5
syscall
move $a1, $v0               # take as input x, and put it into $a1

li $v0, 4
la $a0, msg4
syscall                     # display to take input y
li $v0, 5
syscall
move $a2, $v0               # take as input y, and put it into $a2

li $v0, 4
la $a0, msg5
syscall                     # display to take input z
li $v0, 5
syscall
move $a3, $v0               # take as input z, and put it into $a3

move $a0, $t2

addi $sp, $sp, -4
sw $t1, 0($sp)

#addi $sp, $sp, 4

jal function                # fucntion call here with parameters as v, w, x, y, z in $t1, $a0, $a1, $a2 ,$a3
move $s2, $v0               # store the result in $s2

b done

function:                   # Function body starts here
lw $s5, 0($sp)
#addi $sp, $sp, 4
addi $sp, $sp, -32          # adjust the stack to make room for 6 items
sw $s5, 0($sp)
sw $a0, 4($sp)              # save regieter $a1 for use afterwards
sw $a1, 8($sp)              # save regieter $a1 for use afterwards
sw $a2, 12($sp)              # save regieter $a2 for use afterwards
sw $a3, 16($sp)             # save regieter $a3 for use afterwards
sw $s0, 20($sp)             # save regieter $s0 for use afterwards
sw $s1, 24($sp)             # save regieter $s1 for use afterwards
sw $ra, 28($sp)             # save the return address



bltz $s5, lessThanZero
bltz $a0, lessThanZero
bltz $a1, lessThanZero      # Base case when any of the arguments is less than zero
bltz $a2, lessThanZero
bltz $a3, lessThanZero


beqz $s5, equalToZero
beqz $a0, equalToZero
beqz $a1, equalToZero      # Base case when any of the arguments is equal to zero
beqz $a2, equalToZero
beqz $a3, equalToZero

                           # otherwise recurse

addi $s5, $s5, -1
addi $a0, $a0, -2          # x = x - 1 
addi $sp, $sp, -4
sw $s5, 0($sp)
jal function               # f(x, y, z)
lw $s5, 0($sp)
addi $sp, $sp, 4
move $s0, $v0              # save the result of first call to $s0
addi $s5, $s5, 1           # x = x + 1
addi $a0, $a0, 1
addi $a1, $a1, -1          # y = y - 1
addi $sp, $sp, -4
sw $s5, 0($sp)
jal function               # f(x, y-1, z)
lw $s5, 0($sp)
addi $sp, $sp, 4
move $s1, $v0              # save the result of second call to $s1
addi $a0, $a0, 1           # y = y + 1
addi $a1, $a1, -1 
addi $a2, $a2, -2  
addi $a3, $a3, -1          # z = z + 1
addi $sp, $sp, -4
sw $s5, 0($sp)
jal function               # f(x, y, z-2)
lw $s5, 0($sp)
addi $sp, $sp, 4
add $v0, $v0, $s0
add $v0, $v0, $s1          # f(x-1, y, z) + f(x, y-1, z) + f(x, y, z-2)

lw $s5, 0($sp)
lw $a0, 4($sp)             # restore register $a0 for caller
lw $a1, 8($sp)             # restore register $a1 for caller
lw $a2, 12($sp)             # restore register $a2 for caller
lw $a3, 16($sp)             # restore register $a3 for caller
lw $s0, 20($sp)            # restore register $s0 for caller
lw $s1, 24($sp)            # restore register $s1 for caller
lw $ra, 28($sp)            # restore return address
addi $sp, $sp, 32          # adjust stack pointer to pop 6 elements
jr $ra                     # return to the caller



b ltz
lessThanZero:
move $v0, $zero            # f(x, y, z) = 0 if one (or more) of x, y and z is negative
lw $s5, 0($sp)
lw $a0, 4($sp)             # restore register $a0 for caller
lw $a1, 8($sp)             # restore register $a1 for caller
lw $a2, 12($sp)             # restore register $a2 for caller
lw $a3, 16($sp)             # restore register $a3 for caller
lw $s0, 20($sp)            # restore register $s0 for caller
lw $s1, 24($sp)            # restore register $s1 for caller
lw $ra, 28($sp)            # restore return address
addi $sp, $sp, 32          # adjust stack pointer to pop 6 elements
jr $ra                     # return to the caller
ltz:

b etz
equalToZero:
add $v0, $s5, $a0
add $v0, $v0, $a1
add $v0, $v0, $a2
add $v0, $v0, $a3          # f(x, y, z) = v + w + x + y + z  if one (or more) of x, y and z is 0.
lw $s5, 0($sp)
lw $a0, 4($sp)             # restore register $a0 for caller
lw $a1, 8($sp)             # restore register $a1 for caller
lw $a2, 12($sp)             # restore register $a2 for caller
lw $a3, 16($sp)             # restore register $a3 for caller
lw $s0, 20($sp)            # restore register $s0 for caller
lw $s1, 24($sp)            # restore register $s1 for caller
lw $ra, 28($sp)            # restore return address
addi $sp, $sp, 32          # adjust stack pointer to pop 6 elements
jr $ra                     # return to the caller
etz:


done:

li $v0, 4
la $a0, msg6
syscall                    # display the final message
move $a0, $s2
li $v0, 1
syscall                    # display the answer

li $v0, 10
syscall                    # program ends here



###########################
####   data segment   #####
###########################

.data
msg1: .asciiz "\nEnter the value of v: "
msg2: .asciiz "Enter the value of w: "
msg3: .asciiz "Enter the value of x: "
msg4: .asciiz "Enter the value of y: "
msg5: .asciiz "Enter the value of z: "
msg6: .asciiz "f(v,w,x,y,z): "
