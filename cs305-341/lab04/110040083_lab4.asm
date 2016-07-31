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
msg1: .asciiz "\nPlease insert a number: "
msg2: .asciiz "Please insert a number: "
msg3: .asciiz "GCD of two numbers is: "
