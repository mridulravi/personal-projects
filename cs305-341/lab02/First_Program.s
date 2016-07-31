.data
msg1: .asciiz "\nPlease insert a number: "
msg2: .asciiz "Please insert another number: "
msg3: .asciiz "Larger of two given numbers is: "

.text
main:
li $v0, 4
la $a0, msg1
syscall
li $v0, 5
syscall
move $t0, $v0

li $v0, 4
la $a0, msg2
syscall
li $v0, 5
syscall
move $t1, $v0

bgt $t0, $t1, t0_bigger
move $t2, $t1
b endif

t0_bigger:
move $t2, $t0

endif:
li $v0, 4
la $a0, msg3
syscall
move $a0, $t2
li $v0, 1
syscall

li $v0, 10
syscall









