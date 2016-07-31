# Submitted by : 110040083
# Mridul Ravi Jain
# CSE BTech3



# The goal of this mini-assignment is to compute the gcd of two positive integers.
# The program  take as input the two integers from the user and outputs the gcd between them



# Using the Logic that GCD(a,b) = GCD (b, a%b)
# untill a%b is zero, final result is b



###########################
####  text segment   #####
###########################

.text
.globl main
main:

la $a1, myarray # $a1 is the base address of myarray

li $v0, 4
la $a0, msg4
syscall
li $v0, 5
syscall
move $t5, $v0 #t5 keeps track of the number of elements to be sorted

la $a0, msg5
li $v0, 4
syscall

li $t0, 0 # i = 0; = 4*$t5
loop:		# to insert the elements in myarray
blez $t5,sort
li $v0, 5
syscall
addi $t5,$t5,-1
addi $t0,$t0,4
sw $v0, ($a1)
addi $a1, $a1, 4 # move the array over by one element
j loop


.text
.globl main
main:
li $v0, 4                  
la $a0, msg1
syscall                         # print the message on screen
li $v0, 5                         
syscall                         # take first number as input
move $t0, $v0

li $v0, 4
la $a0, msg2
syscall                         # print the message on screen
li $v0, 5
syscall                         # take second number as input
move $t1, $v0


loop:
blez $t1, done
move $t2, $t1                   # save $t1 in a temporary variable in $t2
rem $t1, $t0, $t1               # compute a%b and save the result in $t1
move $t0, $t2                   # copy the value of $t1 in $t0
j loop

done: 
li $v0, 4
la $a0, msg3
syscall
li $v0, 1
move $a0, $t0
syscall 
li $v0, 10
syscall

###########################
####   data segment   #####
###########################

.data
myarray: .space 20000
msg1: .asciiz "\nPlease insert a number: "
msg2: .asciiz "Please insert a number: "
msg3: .asciiz "GCD of two numbers is: "
msg4: .asciiz "\nPlease insert the number of elements: "
msg5: .asciiz "Insert the elements : "
