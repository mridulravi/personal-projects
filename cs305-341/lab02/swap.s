
###########################
####  text segment   #####
###########################

.text
.globl main
main:

la $a1, myarray # $a1 is the base address of the array

li $v0, 4
la $a0, message3
syscall
li $v0, 5
syscall
move $t5, $v0 #t5 keeps track of the number of elements to be sorted

la $a0, message4
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

sort:

la $t4, myarray #t0 is number up to outter loop
la $t1, myarray #t1 is number comparing to inner loop
addi $t1,$t1,4
la $t8,myarray
add $t8,$t0,$t8
la $t9,myarray
add $t9,$t0,$t9
addi $t9,$t9,-4
loops: lw $t2,($t4) #get number 1 outter loop
lw $t3,($t1) #get number 2 inner loop
blt $t2,$t3,next #don't need to swap
sw $t3,($t4) #swap
sw $t2,($t1)
next: addi $t1,$t1,4
blt $t1,$t8,loops #inner loop done?
addi $t4,$t4,4 #yes-increment outter loop
move $t1,$t4
addi $t1,$t1,4
blt $t4,$t9,loops #outter loop done?

printArray:
la $a1,myarray
move $t7, $t0 # t7 is later used to find median
la $a0, message2
li $v0, 4
syscall
loop1:
blez $t0, median
li $v0, 1
lw $a0, 0($a1)
syscall
la $a0, message1
li $v0, 4
syscall
addi $a1, $a1, 4
addi $t0, $t0, -4
j loop1

median:
la $a2,myarray

la $a0, message5
li $v0, 4
syscall
loop2:
blez $t7, done
li $v0, 1
lw $a0, 0($a2)
addi $a2, $a2, 4
addi $t7, $t7, -8 # for one element in sorted myarray increase the count by two
j loop2

done:
syscall
li $v0, 10
syscall


###########################
####   data segment   #####
###########################

.data
myarray: .space 5000
message1: .asciiz " "
message2: .asciiz "Sorted List:\n"
message3: .asciiz "Please enter count:\ncount="
message4: .asciiz "Please enter the elements to be sorted:\n"
message5: .asciiz "\nMedian element is "