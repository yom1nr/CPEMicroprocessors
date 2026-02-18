ORG 0000H
    JMP 0100H
    ORG 0100H
    MOV SP,#3FH
    CLR EA
    CALL Delay_250M
    CALL Initial_Serial
    CALL Send_ClrScr
    MOV R7,#10 
Main_Loop: 
    MOV DPTR,#User
    CALL Send_Table
    CALL Send_LineFeed
    CALL Delay_500M
    DJNZ R7,Main_Loop
    MOV DPTR,#MSG
    CALL Send_Table
    CALL Send_LineFeed
    JMP $

$INCLUDE (myDelay.A51)
$INCLUDE (mySerial.A51)

User: 
    DB 'B6511975 SUPALUCK TOHTHONG',00

MSG: 
    DB 'I Want A',00
END