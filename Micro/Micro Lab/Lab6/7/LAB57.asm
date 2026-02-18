
		ORG 	0000H
		JMP 	0100H
		ORG 	0100H
		MOV 	SP,#3FH
		CLR 	EA
LOOP: 		CALL 	ScanKey
		MOV 	DPTR,#Seg_Table
		MOVC 	A,@A+DPTR
		CPL 	A 			; Active Low
		MOV 	P0,A
		SETB 	P1.4 			; Left not Show
		CLR 	P1.5 			; Right Show
		CALL 	Delay
		JMP 	LOOP

Seg_Table: 	DB 77H,11H,6DH,5DH 		; 00 01 02 03
		DB 1BH,5EH,7EH,15H 		; 04 05 06 07
		DB 7FH,5FH,3FH,7AH 		; 08 09 0A 0B
		DB 66H,79H,6EH,2EH 		; 0C 0D 0E 0F
		DB 08H 				; 10

Delay: 		CLR 	A
		MOV 	B,A
_Dly00: 	DJNZ	Acc,_Dly00
		DJNZ 	B,_Dly00
		RET
		
ScanKey: 
; Row 1
		MOV 	P2,#11111110B
		MOV 	B,#01H
		JNB 	P2.4, _Exit
		MOV 	B,#02H
		JNB 	P2.5, _Exit
		MOV 	B,#03H
		JNB 	P2.6, _Exit
		MOV 	B,#0AH
		JNB 	P2.7, _Exit
		
; Row 2
		MOV 	P2,#11111101B
		MOV 	B,#04H
		JNB 	P2.4, _Exit
		MOV 	B,#05H
		JNB 	P2.5, _Exit
		MOV 	B,#06H
		JNB 	P2.6, _Exit
		MOV 	B,#0BH
		JNB 	P2.7, _Exit
; Row 3
		MOV 	P2,#11111011B
		MOV 	B,#07H
		JNB 	P2.4, _Exit
		MOV 	B,#08H
		JNB 	P2.5, _Exit
		MOV 	B,#09H
		JNB 	P2.6, _Exit
		MOV 	B,#0CH
		JNB 	P2.7, _Exit
; Row4
		MOV 	P2,#11110111B
		MOV 	B,#0EH
		JNB 	P2.4, _Exit
		MOV 	B,#00H
		JNB 	P2.5, _Exit
		MOV 	B,#0FH
		JNB 	P2.6, _Exit
		MOV 	B,#0DH
		JNB 	P2.7, _Exit
		
; no press
		MOV 	B,#10H
		
_Exit: 		MOV A,B
		RET
		END