  # analyze.asm
  # This file written 2015 by F Lundevall
  # Copyright abandoned - this file is in the public domain.

	.text
main:
	li	$s0,0x30        # -----$s0 = 0
loop:
	move	$a0,$s0		# copy from s0 to a0 ----- $a0 = $s0
	
	li	$v0,11	        # syscall with v0 = 11 will print out-----???
	syscall			# one byte from a0 to the Run I/O window-----???

	addi	$s0,$s0,3	# change 1
	                       # what happens if the constant is changed?-----det kommer hoppa över nagra tecken beror på constant, 
	                       # -----om constant ar 0, kommer det visa bara en tecken , 
	                       # -----om constant n > 1, kommer hoppar över n-1 st tecken i mellan tva utskrivit teckenerna  
	                       # -----for att det ska 'print out every third character', vilket betyder att hoppa 2 st tecken, sa constant andras till 3 
	
	li	$t0,0x5b       # -----$t0 = 91 ( 5*16+11) ( Z = 91 i char ) 
	ble	$s0,$t0,loop   # change 2 
	                       # -----bne  till ble 
	                       # -----nar ( $s0 <= t0, t0 = 91), hoppar det till loop
	nop			# delay slot filler (just in case)

stop:	j	stop		# loop forever here
	nop			# delay slot filler (just in case)
	
	# s0 = 0              a0 = s0 = 0
	# s0 = s0 + 1 = 1     a0 = s0 = 1
	#........             ........
	# s0 = s0 + 1 = 91    ------stop, finns inte a0 

