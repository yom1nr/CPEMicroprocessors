ORG 	8000H
LOOP: 	MOV 	R0,#00H ; Position 1st
	MOV 	R1,#06DH ; Display All On
	CALL 	DISP_OUT
	CALL 	DELAY_500M
	MOV 	R0,#01H ; Position 1st
	MOV 	R1,#006H ; Display All On
	CALL 	DISP_OUT
	CALL 	DELAY_500M
	MOV 	R0,#02H ; Position 1st
	MOV 	R1,#06DH ; Display All On
	CALL 	DISP_OUT
	CALL 	DELAY_500M
	MOV 	R0,#03H ; Position 1st
	MOV 	R1,#07DH ; Display All On
	CALL 	DISP_OUT
	CALL 	DELAY_500M
	MOV 	R0,#04H ; Position 1st
	MOV 	R1,#06DH ; Display All On
	CALL 	DISP_OUT
	CALL 	DELAY_500M
	MOV 	R0,#05H ; Position 1st
	MOV 	R1,#05BH ; Display All On
	CALL 	DISP_OUT
	CALL 	DELAY_500M
	JMP 	LOOP
;************************************************
; Display Digit_R0 by Value_R1
;************************************************
DISP_OUT: 	MOV 	DPTR,#0E002H ; Send Position
		MOV 	A,R0
		MOVX 	@DPTR,A
		MOV 	DPTR,#0E001H ; Send Value
		MOV 	A,R1
		MOVX 	@DPTR,A
		CLR 	A
		DJNZ 	Acc,$
		RET
;************************************************
; Delay Subroutine
;************************************************
DELAY_2SEC: 	CALL 	DELAY_1SEC ; Delay 1 Sec
		CALL 	DELAY_1SEC ; Delay 1 Sec
		RET
		
DELAY_1SEC: 	CALL 	DELAY100MS ; Delay 100 mSec
		CALL 	DELAY100MS ; Delay 100 mSec
		CALL 	DELAY100MS ; Delay 100 mSec
		CALL 	DELAY100MS ; Delay 100 mSec
		CALL 	DELAY100MS ; Delay 100 mSec
		CALL 	DELAY100MS ; Delay 100 mSec
		CALL 	DELAY100MS ; Delay 100 mSec
		CALL 	DELAY100MS ; Delay 100 mSec
		CALL 	DELAY100MS ; Delay 100 mSec
		CALL 	DELAY100MS ; Delay 100 mSec
		RET
		
DELAY_500M: 	CALL 	DELAY100MS ; Delay 100 mSec
		CALL 	DELAY100MS ; Delay 100 mSec
		CALL 	DELAY100MS ; Delay 100 mSec
		CALL 	DELAY100MS ; Delay 100 mSec
		CALL 	DELAY100MS ; Delay 100 mSec
		RET
		
DELAY100MS: 	MOV 	R6,#200 ; 200 * 500 = 100mS

DLY100MS: 	CALL 	DELAY500U ; Delay 500 MicroSec
		DJNZ 	R6,DLY100MS
		RET
		
DELAY500U: 	MOV 	R5,#230 ;1 MC
		DJNZ R5,$ ;(230*2)MC *12/11.0592
		RET ; = 499uSec
		
		END
