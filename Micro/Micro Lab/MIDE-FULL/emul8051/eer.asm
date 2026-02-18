ORG	8100H
	MOV	B,#56H	; Data Fill
	MOV	DPTR,#9100H
	
Loop_Fill:	MOV	A,B	; ReLoad Data
	MOVX	@DPTR,A
	INC	DPTR
	INC	B
	
	MOV	A,DPH
	CJNE	A,#92H,Loop_Fill
	MOV	A,DPL
	CJNE	A,#40H,Loop_Fill
	
	SJMP	$
	
	END