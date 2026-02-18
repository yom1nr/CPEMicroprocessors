LOC. OBJECT          LINE    SOURCE
*
0000 E4                1         CLR  A
0001 F8                2         MOV  R0,A
0002                   3     L:
0002 08                4         INC  R0
0003 28                5         ADD  A,R0
0004 B80AFB            6         CJNE R0,#10,L
*                      7         END
