LF_SEG 	EQU P1.4
RG_SEG 	EQU P1.5
PT_SEG 	EQU P0
	
	ORG 0000H
	JMP 0100H
	
	ORG 	0100H
	MOV 	SP,#2FH
	CLR 	RG_SEG
	SETB 	LF_SEG
	MOV 	R7,#00H
	
LOOP: 	
	MOV 	A,R7        
	;ANL 	A,#0FH     
	MOV 	DPTR,#T_SEG 
	MOVC 	A,@A+DPTR  
	CPL 	A           
	MOV 	PT_SEG,A    
	CALL 	DELAY           
	INC	R7
	CJNE 	R7,#11H,LOOP
	MOV 	R7,#00H
	JMP 	LOOP        


T_SEG: 	
	DB 40H    ; _ 
	DB 7AH    ; B
	DB 7EH    ; 6
	DB 5EH    ; 5
	DB 11H    ; 1
	DB 5EH    ; 5
	DB 7EH    ; 6
	DB 5EH    ; 5
	DB 6DH    ; 2
	DB 00H    ; 
	DB 1FH    ; G
	DB 28H	  ; R
	DB 3FH    ; A
	DB 79H    ; D
	DB 6EH    ; E
	DB 48H    ; =
	DB 3FH    ; A
	
T_SEG1: 	
	DB 77H    ; 0 
	DB 11H    ; 1
	DB 6DH    ; 2
	DB 5DH    ; 3
	DB 1BH    ; 4
	DB 5EH    ; 5
	DB 7EH    ; 6
	DB 15H    ; 7
	DB 7FH    ; 8
	DB 5FH    ; 9
	DB 3FH    ; A
	DB 7AH	  ; B
	DB 66H    ; C
	DB 79H    ; D
	DB 6EH    ; E
	DB 2EH    ; F

DELAY: 	PUSH 07H 
	PUSH 06H 
	PUSH 05H 
	PUSH 04H 
	MOV R4,#30 
_DLY_4: MOV R5,#30 
_DLY_5: MOV R6,#30 
_DLY_6: MOV R7,#27 
_DLY_7: DJNZ R7,_DLY_7 
	DJNZ R6,_DLY_6 
	DJNZ R5,_DLY_5 
	DJNZ R4,_DLY_4 
	POP 04H 
	POP 05H 
	POP 06H 
	POP 07H 
	RET
	
	END
