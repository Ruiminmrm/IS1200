  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,2         # change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out--------------
	syscall			# one byte from a0 to the Run I/O window----------------
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  # 
hexasc: 
       andi $t0, $a0 , 0xf
       li   $t1, 9
       li   $t2, 15
       ble  $t0, $t1, number
       nop
       ble  $t0, $t2, letter
       nop
       number:
             addi $v0, $t0, 0x30
             jr $ra
             nop
       letter: 
             addi $v0, $t0, 55# 55+10=65 , 65 = A
             jr $ra
             nop

       #if the argument is 17, what is the return value ? 
       # -----1
       #if your solution contains a conditional-branch instruction : which input value cause the instruction to actually branch to another location ?
       # om sista fyra bit ät <=9 , branch den till number
       # om sista fyra bit är (9,15], branch den till letter 
       

   
       


       
