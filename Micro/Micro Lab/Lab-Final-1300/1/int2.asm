LeO_Select	EQU P1.4
Right_Select	EQU P1.5
Segment_Port 	EQU P0
Pin_Intr0 	EQU P3.0
Pin_Intr1 	EQU P3.1

	ORG 	0000H
	JMP 	START
	ORG 	0003H
	JMP 	EX0_ISR
	ORG 	0013H
	JMP 	EX1_ROUTINE
	ORG 	0100H
START: 	SETB 	IT0
	SETB 	IT1 ; Edge Trigger
	MOV 	IE,#10000101B
	MOV 	R7,#50H	
Main_Loop:
	MOV 	A,R7
	CALL 	Show_7Segment
	JMP 	Main_Loop
;========================================
EX0_ISR:
	PUSH 	B
	PUSH 	Acc
	INC 	R7
	CALL 	Debounce
	CALL 	Debounce
	CLR 	IE0 ; Clear Ext.Intr_1 Flag
	POP 	Acc
	POP 	B
	RETI ; Return from Interrupt
	
;========================================
EX1_ROUTINE: 	
	PUSH B
	PUSH 	Acc
	DEC 	R7
	CALL 	Debounce
	CALL 	Debounce
	CLR 	IE1 ; Clear Ext.Intr_1 Flag
	POP 	Acc
	POP 	B
	RETI ; Return from Interrupt
;========================================
Debounce:
	CLR 	A
	MOV 	B,A
_Dly00:	DJNZ 	Acc,_Dly00
	DJNZ 	B,_Dly00
	RET
;========================================
Show_7Segment:
	SETB 	LeO_Select
	CLR 	Right_Select
	PUSH 	Acc
	CALL 	_Show0
	POP 	Acc
	SWAP 	A
	CLR 	LeO_Select
	SETB 	Right_Select
	
_Show0: ANL 	A,#0FH ; 0nly 0-F
	MOV 	DPTR,#CODE_TABLE
	MOVC 	A,@A+DPTR
	CPL 	A
	MOV 	Segment_Port,A
	CLR	A
	DJNZ 	Acc,$
	RET
	
CODE_TABLE:
	DB 77H, 11H, 6DH, 5DH ; Code 0123
	DB 1BH, 5EH, 7EH, 15H ; Code 4567
	DB 7FH, 5FH, 3FH, 7AH ; Code 89ab
	DB 66H, 79H, 6EH, 2EH ; Code cdef
	
	END