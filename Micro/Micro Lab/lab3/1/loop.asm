	ORG 	0000H
	MOV 	R1,#30H 
	MOV	DPTR,#1000H
	
LOOP1: 	MOV	A,#55H
	MOVX 	@DPTR,A
	INC 	DPTR
	DJNZ 	R1,Loop1
	
; ============================================
	
	MOV	DPTR,#1000H
	MOV 	R0,#30H
	MOV 	R1,#30H
	
LOOP2:	MOVX	A,@DPTR
	MOV	@R0,A
	INC 	DPTR
	INC	R0
	DJNZ 	R1,Loop2
	
	JMP $
	
	END