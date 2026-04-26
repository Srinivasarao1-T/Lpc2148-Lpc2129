SW EQU P2.7
LED EQU P3
CSEG AT 0 
MOV R3,#0X00
LOOP:
MOV LED,R3
JB SW,$                                                                                                                                                                                                                                                                                                                                                                                                                        
JNB SW,$
INC R3
SJMP LOOP
END
