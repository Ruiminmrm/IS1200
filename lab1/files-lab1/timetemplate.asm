  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,-1
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
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

delay :
        PUSH $ra
	li $t2, 0 			# int i = 0
	li $t3, 4711			# konstant  -----ändras under laben 
	while: 
		ble $a0, 0, delayend 	#  ms <= 0 branch till delayend 
		nop			
		sub $a0, $a0, 1		# ms = ms - 1
	
		for:
			beq $t2, $t3, while	#  i < 4711; i = 4711 branch till while loop 
			nop
			addi $t2, $t2, 1	# i = i + 1 
			j for			
			nop

delayend :
	POP $ra
	jr $ra
	nop
       
time2string : 

	PUSH $s1
        PUSH $ra
        move $s1,$a0 
        
        andi $t0,$a1, 0xf000 #ta de fösrta 4 bits
        srl  $a0,$t0, 12 #shift left 12 bits det blir sekund 1 
        jal  hexasc #visa number
        nop
        move $a2,$v0
        sb   $a2,0($s1) # return 
        
        andi $t0,$a1, 0x0f00 #ta de andra fösrta 4 bits
        srl  $a0,$t0, 8 #shift left 12 bits det blir sekund 2
        jal  hexasc #visa number
        nop
        move $a2,$v0
        sb   $a2,1($s1) # return 
       
        li   $t0,0x3a # tecken :
        sb   $t0,2($s1)
        
        andi $t0,$a1, 0x00f0 #ta de andra sista 4 bits
        srl  $a0,$t0, 4 #shift left 12 bits det blir minute 1 
        jal  hexasc #visa number
        nop
        move $a2,$v0
        sb   $a2,3($s1) # return 
        
        
        andi $t0,$a1, 0x000f #ta de sista 4 bits
        srl  $a0,$t0,0
        jal  hexasc #visa number
        nop
        move $a2,$v0
        sb   $a2,4($s1) # return ti i fjärde plats i s0
        
        li $t0, 0x0
	sb $t0, 5($s1) # Store string terminator
	
	POP  $ra
	POP  $s1
	jr   $ra
	nop

# which register are saved and restored by your subroutine ?----return värde och s1, return värde behöver save och restore för att man änvander efter varje ändring man gjort , 
                                                           #----s1 är för att man ska lägga den i stack och ändra den och print out den värde efter ändring 
#which register are used but not saved ? ----resten register. den värde de hade behöver inte änvandas efter loop. 

#if a0 = 0, which instructions in your subroutine are executed? how many times each ? ----delayend 