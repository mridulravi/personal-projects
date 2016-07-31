.data
msg1:.asciiz "Please insert first hexadecimal number: "
msg2:.asciiz "Please insert the value of n:"
msg3:.asciiz "\nPlease insert second hexadecimal number: "
newline:.asciiz "\n"
result: .space 8
        .asciiz "\n"
str1: .space 20
str2: .space 20
.text
.globl main
main:

li $v0, 4
la $a0, msg2
syscall
li $v0, 5
syscall
move $t5, $v0

li $t4, 0
loop:
blez $t5, nFound
addi $t5, $t5, -4
addi $t4, $t4, 1
j loop

nFound:

li $v0, 1
la $a0, ($t4)
syscall

move $s0, $t4   # access s0 same as t4

li $v0,4
la $a0,msg1
syscall
li $v0,8
la $a0,str1
addi $a1, $zero, 1
add $a1,$a1, $t4
syscall   #got string 1

la $t1,str1  #pass address of str1
li $s1, 0
access:
addi $t4,$t4,-1   #this will give you the power of 16 to be multiplied to the int corresponding to char
lb $t3($t1)
beqz $t3,done1hex
la $a0, ($t3)

beq $a0, 48, int
beq $a0, 49, int
beq $a0, 50, int
beq $a0, 51, int
beq $a0, 52, int
beq $a0, 53, int
beq $a0, 54, int
beq $a0, 55, int
beq $a0, 56, int
beq $a0, 57, int
beq $a0, 97, char
beq $a0, 98, char
beq $a0, 99, char
beq $a0, 100, char
beq $a0, 101, char
beq $a0, 102, char

b integer
int:
addi $a0, $a0, -48
integer:

b character
char:
addi $a0, $a0, -87
character:

beq $t4, 3, raise3
beq $t4, 2, raise2
beq $t4, 1, raise1
beq $t4, 0, raise0

b r3
raise3:
sll $t5, $a0, 12 
r3:

b r2
raise2:
sll $t5, $a0, 8
r2:

b r1
raise1:
sll $t5, $a0, 4
r1:

b r0
raise0:
sll $t5, $a0, 0
r0:

add $s1, $s1, $t5
addi $t1,$t1,1
j access

done1hex:
li $v0, 4
la $a0, newline
syscall
li $v0, 1
la $a0, ($s1)
syscall

move $s2, $s1

move $t4, $s0

li $v0,4
la $a0,msg3
syscall
li $v0,8
la $a0,str2
addi $a1, $zero, 1
add $a1,$a1, $t4
syscall   #got string 2

la $t1,str2  #pass address of str2
move $t4, $s0
li $s1, 0
access2:
addi $t4,$t4,-1   #this will give you the power of 16 to be multiplied to the int corresponding to char
lb $t3($t1)
beqz $t3,done2hex
la $a0, ($t3)

beq $a0, 48, int2
beq $a0, 49, int2
beq $a0, 50, int2
beq $a0, 51, int2
beq $a0, 52, int2
beq $a0, 53, int2
beq $a0, 54, int2
beq $a0, 55, int2
beq $a0, 56, int2
beq $a0, 57, int2
beq $a0, 97, char2
beq $a0, 98, char2
beq $a0, 99, char2
beq $a0, 100, char2
beq $a0, 101, char2
beq $a0, 102, char2

b integer2
int2:
addi $a0, $a0, -48
integer2:

b character2
char2:
addi $a0, $a0, -87
character2:

beq $t4, 3, raise23
beq $t4, 2, raise22
beq $t4, 1, raise21
beq $t4, 0, raise20

b r23
raise23:
sll $t5, $a0, 12 
r23:

b r22
raise22:
sll $t5, $a0, 8
r22:

b r21
raise21:
sll $t5, $a0, 4
r21:

b r20
raise20:
sll $t5, $a0, 0
r20:

add $s1, $s1, $t5
addi $t1,$t1,1
j access2





done2hex:
li $v0, 4
la $a0, newline
syscall
li $v0, 1
la $a0, ($s1)
syscall

move $s3, $s1

xor $t4, $s2, $s3 
li $v0, 4
la $a0, newline
syscall
li $v0, 1
la $a0, ($t4)
syscall


li $t0, 8
la $t3, result

loop3:
rol $t4, $t4, 4
and $t1, $t4, 0xf
ble $t1, 9, print
add $t1, $t1, 7
print:
add $t1, $t1, 0x30
sb $t1, ($t3)
add $t3, $t3, 1
add $t0, $t0, -1
bnez $t0, loop3


li $v0, 4
la $a0, newline
syscall
la $a0, result
li $v0, 4
syscall

li $v0, 10
syscall