  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #


.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4

.endm
  #
  # Please add your own code below this line
  #
.global delay
.global time2string
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
	li $t2, 0 			# int i = 0
	li $t3, 205110			# konstant  
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
	jr $ra
	nop
       
time2string: 

	PUSH $s1
        PUSH $ra
        move $s1,$a0 
        
        andi $t0,$a1, 0xf000 #ta de f?srta 4 bits
        srl  $a0,$t0, 12 #shift left 12 bits det blir sekund 1 
        jal  hexasc #visa number
        nop
        move $a2,$v0
        sb   $a2,0($s1) # return 
        
        andi $t0,$a1, 0x0f00 #ta de andra f?srta 4 bits
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
        sb   $a2,4($s1) # return ti i fj?rde plats i s0
        
        li $t0, 0x0
	sb $t0, 5($s1) # Store string terminator
	
	POP  $ra
	POP  $s1
	jr   $ra
	nop
	#What is the effect of the assembler directive .global? Why is the directive particularly important in this assignment? The teachers will help you with this if necessary.
        #-----utan global ?r alla function private , s? att andra function kan inte anropa de direkt. s? 
        #genom att anv?nda global g?r attt vissa functioen blev public, s? att det funckar.  
