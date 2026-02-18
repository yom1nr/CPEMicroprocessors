;==== Lab81Ex1.Asm ====
Data_Count 	EQU 40H
Left_Select 	EQU P1.4
Right_Select 	EQU P1.5
Segment_Port 	EQU P0

		ORG 0000H
		JMP START
	
		ORG 0013H
		JMP EX1_ROUTINE
	
		ORG 0100H	
START: 		
		SETB IT1 ; Edge Trigger
		MOV IE,#10000100B
		MOV Data_Count,#0
Main_Loop: 	
		MOV A,Data_Count
		CALL Show_7Segment
		JMP Main_Loop
;========================================
EX1_ROUTINE: 	PUSH B
			PUSH Acc
			INC Data_Count
			CALL Debounce
			CALL Debounce
			CLR IE1 ; Clear Ext.Intr_1 Flag
			POP Acc
			POP B
			RETI ; Return from Interrupt
;========================================
Debounce: 	CLR A
			MOV B,A
_Dly00: 		DJNZ Acc,_Dly00
			DJNZ B,_Dly00
			RET
;========================================
Show_7Segment:
			CLR Left_Select
			CLR Right_Select
			ANL A,#0FH ; 0nly 0-F
			MOV DPTR,#CODE_TABLE
			MOVC A,@A+DPTR
			CPL A
			MOV Segment_Port,A
			RET
CODE_TABLE: 	
		DB 0FH, 78H, 0FH, 78H, 0FH, 78H, 0FH, 78H ; Code 0FH 0 TOP
		DB 0FH, 78H, 0FH, 78H, 0FH, 78H, 0FH, 78H ; Code 78H 0 BUTTOM
		END