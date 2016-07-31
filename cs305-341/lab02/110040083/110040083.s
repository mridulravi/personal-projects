
###########################
####  text segment   #####
###########################

.text
.globl main
main:

la $a1, myarray # $a1 is the base address of myarray

li $v0, 4
la $a0, msg3
syscall
li $v0, 5
syscall
move $t5, $v0 #t5 keeps track of the number of elements to be sorted

la $a0, msg4
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

sort:           # use bubble sort to sort the array

la $t1, myarray #t1 points to lower index in outer loop
la $t4, myarray #t4 points to lower index in outer loop
addi $t4,$t4,4
la $t9,myarray #t9 points to higher index in inner loop
add $t9,$t0,$t9
la $t8,myarray #t8 points to higher index in outer loop
add $t8,$t0,$t8
addi $t8,$t8,-4
loops: lw $t3,($t1) #get number 1 outter loop
lw $t2,($t4) #get number 2 inner loop
blt $t3,$t2,next #don't need to swap
sw $t2,($t1) #swap
sw $t3,($t4)
next: addi $t4,$t4,4
blt $t4,$t9,loops #check if inner loop is over
addi $t1,$t1,4 #yes-increment outter loop
move $t4,$t1
addi $t4,$t4,4
blt $t1,$t8,loops #check if outter loop is over

printArray:
la $a1,myarray
move $t7, $t0 # t7 is later used to find median
la $a0, msg2
li $v0, 4
syscall
loop1:
blez $t0, insert
li $v0, 1
lw $a0, 0($a1)
syscall
la $a0, msg1
li $v0, 4
syscall
addi $a1, $a1, 4
addi $t0, $t0, -4
j loop1

insert:
la $a2, myarray # $a2 is the base address of the myarray
la $a1, remarray # $a1 is the base address of the remarray
li $t6, 0 # i = 0; to maintain count of elements in remarray
la $a0, msg5
li $v0, 4
syscall
loop2:
blez $t7, median
#li $v0, 1
lw $a0, 0($a2)
lw $t9, -4($a2)
beq $t9,$a0,dupli # if elements are duplicate dont insert in remarray
                 
addi $t6,$t6,4   # otherwise insert
sw $a0, ($a1)
addi $a1, $a1, 4 # move the array over by one element
dupli:
addi $a2, $a2, 4
addi $t7, $t7, -4 # for one element in sorted myarray increase the count by two
j loop2


median:
la $a1,remarray # $a1 is the base address of the remarray
loop5:
blez $t6, done
li $v0, 1
lw $a0, 0($a1)
#syscall
addi $a1, $a1, 4
addi $t6, $t6, -8
j loop5




done:
syscall # this will display the last value stored in $a0 which is the median
li $v0, 10
syscall





###########################
####   data segment   #####
###########################

.data
myarray: .space 5000
remarray: .space 5000
msg1: .asciiz " "
msg2: .asciiz "Sorted List:\n"
msg3: .asciiz "Please enter count:\ncount="
msg4: .asciiz "Please enter the elements to be sorted:\n"
msg5: .asciiz "\nMedian element is "
