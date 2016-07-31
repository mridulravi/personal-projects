
###########################
####  text segment   #####
###########################

.text
.globl main
main:

la $a1, farray # $a1 is the base address of myarray
la $a2, sarray # $a1 is the base address of myarray
la $a3, tarray

li $v0, 4
la $a0, msg3
syscall
li $v0, 5
syscall
move $t5, $v0 #t5 keeps track of the number of elements to be sorted
move $t6, $v0

la $a0, msg4
li $v0, 4
syscall

li $t0, 0 # i = 0; = 4*$t5
loop:		# to insert the elements in myarray
blez $t5, second
li $v0, 5
syscall
addi $t5,$t5,-1
addi $t0,$t0,4
sw $v0, ($a1)
addi $a1, $a1, 4 # move the array over by one element
j loop

second:
la $a0, msg5
li $v0, 4
syscall

loop2:		# to insert the elements in myarray
blez $t6, doplus
li $v0, 5
syscall
addi $t6,$t6,-1
sw $v0, ($a2)
addi $a2, $a2, 4 # move the array over by one element
j loop2

doplus:
move $t1, $t0
la $a1, farray # $a1 is the base address of myarray
la $a2, sarray # $a1 is the base address of myarray
la $a3, tarray
loop3:
blez $t0, printArray
lw $t4, 0($a1)
lw $t7, 0($a2)
beq $t4, $t7, anszero
li $v0, 1

j ansone
anszero:
li $v0, 0
ansone:

sw $v0, ($a3)
addi $a1, $a1, 4
addi $a2, $a2, 4
addi $a3, $a3, 4
addi $t0, $t0, -4
j loop3

printArray:
la $a3,tarray
la $a0, msg6
li $v0, 4
syscall
loop4:
blez $t1, done
li $v0, 1
lw $a0, 0($a3)
syscall
la $a0, msg1
li $v0, 4
syscall
addi $a3, $a3, 4
addi $t1, $t1, -4
j loop4


done:
li $v0, 10
syscall

###########################
####   data segment   #####
###########################

.data
farray: .space 1000
sarray: .space 1000
tarray: .space 1000
msg1: .asciiz " "
msg2: .asciiz "Sorted List:\n"
msg3: .asciiz "Please enter count:\ncount="
msg4: .asciiz "Please enter the first set of elements:\n"
msg5: .asciiz "Please enter the second set of elements:\n"
msg6: .asciiz "\nThird array is "