;==== Lab81Ex1.Asm ====
Data_Count EQU 40H
Left_Select EQU P1.4
Right_Select EQU P1.5
Segment_Port EQU P0
	ORG 0000H
	JMP START
	ORG 0013H
	JMP EX1_ROUTINE
	ORG 0100H
START: SETB IT1 ; Edge Trigger
	MOV IE,#10000100B
	MOV Data_Count,#52H
Main_Loop: 
	MOV A,Data_Count
	CALL Show_7Segment
	JMP Main_Loop
;========================================
EX1_ROUTINE: PUSH B
	PUSH Acc
	INC Data_Count
	MOV A,Data_Count
	DA A
	MOV Data_Count,A
	CALL Debounce
	CALL Debounce
	CLR IE1 ; Clear Ext.Intr_1 Flag
	POP Acc
	POP B
	RETI ; Return from Interrupt
;========================================
Debounce: 
	CLR A
	MOV B,A
_Dly00: DJNZ Acc,_Dly00
	DJNZ B,_Dly00
	RET
;========================================
Show_7Segment:
	SETB Left_Select
	CLR Right_Select
	PUSH Acc
	CALL SHOW
	POP Acc
	CLR Left_Select
	SETB Right_Select
	SWAP A
SHOW :
	ANL A,#0FH ; 0nly 0-F
	MOV DPTR,#CODE_TABLE
	MOVC A,@A+DPTR
	CPL A
	MOV Segment_Port,A
	;CALL DELAY20MS
	;CALL DELAY20MS
	;CALL DELAY20MS
	;CALL DELAY20MS
	;CALL DELAY20MS
	CALL DELAY20MS
	MOV Segment_Port,#0FFH
	RET
	
DELAY20MS: 
	MOV R6,#10 ; 50 * 500 = 20mS
DLY500U: 
	CALL DELAY500U ; Delay 500 MicroSec
	DJNZ R6,DLY500U
	RET

DELAY500U: 
	MOV R5,#230 ;1 MC
	DJNZ R5,$ ;(230*2)MC *12/11.0592
	RET ; = 499uSec
	
CODE_TABLE: 	DB 77H, 11H, 6DH, 5DH, 1BH, 5EH, 7EH, 15H ; Code 0123 4567
			DB 7FH, 5FH, 3FH, 7AH,66H ,79H,6EH, 2EH ; Code 89ab cdef
END