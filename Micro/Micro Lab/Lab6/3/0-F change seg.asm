LF_SEG 	EQU P1.4
RG_SEG 	EQU P1.5
PT_SEG 	EQU P0
	
	ORG 0000H
	JMP 0100H
	
	ORG 0100H
	MOV SP,#2FH
	SETB RG_SEG
	CLR LF_SEG
	MOV R7,#15
LOOP: 	
	MOV A,R7        
	ANL A,#0FH     
	MOV DPTR,#T_SEG 
	MOVC A,@A+DPTR  
	CPL A           
	MOV PT_SEG,A    
	CALL DELAY      
	CALL DELAY      
	DEC R7         
	CJNE R7,#0,LOOP 
	JMP LOOP        

T_SEG: 	
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

Delay: 	
	MOV R0, #5
	MOV B,#150
	MOV A,#150
_DLY00: 
	DJNZ Acc,_DLY00
	DJNZ B,_DLY00
	DJNZ R0,_DLY00
	RET
	
	END
