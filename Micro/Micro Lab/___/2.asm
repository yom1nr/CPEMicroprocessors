T2CON EQU 0C8H
RCAP2L EQU 0CAH
RCAP2H EQU 0CBH

	ORG 0000H ; Lab10Srl2.Sub
	JMP 0100H

	ORG 0100H
	MOV SP,#3FH
	CLR EA ; Disable All
	MOV SCON,#01010000B ; Mode1 Serial Port
	MOV RCAP2H,#0FFH ; Reload values for desired
	MOV RCAP2L,#0C4H ; baud rate 9600@11.0592
	MOV T2CON,#00110100B ; Timer 2 as baud rate generator
						; and turn on Timer 2

Main_Loop: CLR RI ; Ready for New Data
	JNB RI,$ ; Wait Until Data In
	MOV A,SBUF ; Get Data In

_IS_ASCII_0: CJNE A,#'0',_IS_ASCII_1
	SETB P3.7
	MOV A,#01H
	CALL Display
	JMP Main_Loop
	
_IS_ASCII_1: CJNE A,#'1',_IS_ASCII_2
	SETB P3.7
	MOV A,#02H
	CALL Display
	JMP Main_Loop
	
_IS_ASCII_2: CJNE A,#'2',_IS_ASCII_3
	SETB P3.7
	MOV A,#03H
	CALL Display
	JMP Main_Loop
	
_IS_ASCII_3: CJNE A,#'3',_IS_ASCII_4
	SETB P3.7
	MOV A,#04H
	CALL Display
	JMP Main_Loop
	
_IS_ASCII_4: CJNE A,#'4',_IS_ASCII_5
	SETB P3.7
	MOV A,#05H
	CALL Display
	JMP Main_Loop
	
_IS_ASCII_5: CJNE A,#'5',_IS_ASCII_6
	SETB P3.7
	MOV A,#06H
	CALL Display
	JMP Main_Loop
	
_IS_ASCII_6: CJNE A,#'6',_IS_ASCII_7
	SETB P3.7
	MOV A,#07H
	CALL Display
	JMP Main_Loop

_IS_ASCII_7: CJNE A,#'7',_IS_ASCII_8
 	SETB P3.7
	MOV A,#08H
	CALL Display
	JMP Main_Loop

_IS_ASCII_8: CJNE A,#'8',_IS_ASCII_9
	SETB P3.7
	MOV A,#09H
	CALL Display
	JMP Main_Loop
	
_IS_ASCII_9: CJNE A,#'9',_IS_ASCII_Etc
	SETB P3.7
	MOV A,#0AH
	CALL Display
	JMP Main_Loop
	
_IS_ASCII_Etc: NOP
	SETB P3.7
	MOV A,#00H
	CALL Display
	JMP Main_Loop

Display:
Blink:
	MOV DPTR,#Seg_Tab
	MOVC A,@A+DPTR
	CPL A
	MOV P0,A
	CLR P1.4
	CLR P1.5
	RET

Seg_Tab: 	DB 08H, 77H, 11H, 6DH, 5DH, 1BH, 5EH, 7EH, 15H
		DB 7FH, 5FH, 3FH, 7AH, 66H, 79H, 6EH, 2EH
	
Delay: 		MOV	 R3,#3
			MOV A,R3
			MOV B,R3
_Dly00: 		DJNZ R3,_Dly00
			DJNZ Acc,_Dly00
			DJNZ B,_Dly00
			RET

	END