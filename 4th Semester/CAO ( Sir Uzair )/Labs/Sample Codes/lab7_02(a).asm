.MODEL SMALL
.STACK 100h

.DATA
    SUM DW 0 ; Used to store vals for printNum after msg.
    COUNT DW 1
    MSG DB 'Final Sum: $'
    COUNT_MSG DB 0Dh, 0Ah, 'Count: $'
    ; RESULT DB 6 DUP('$')  ; Buffer for result  

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX
    
    MOV AX, 0
    MOV CX, 1
    
    RUN_LOOP:
        ADD AX, CX
        INC CX
        
        CMP AX, 1000
        JLE RUN_LOOP
    
    DEC CX ; As it will be incremented 1-extra.
    MOV SUM, AX
    MOV COUNT, CX
    
    LEA DX, MSG
    MOV AH, 9
    INT 21H
    
    MOV AX, SUM
    CALL PRINT_NUM
    
    MOV AX, COUNT
    LEA DX, COUNT_MSG
    MOV AH, 9
    INT 21H
    MOV AX, COUNT
    CALL PRINT_NUM
    
    MOV AH, 4Ch
    INT 21h
MAIN ENDP


PRINT_NUM PROC
    MOV CX, 0 
    MOV BX, 10
    
    CMP AX, 0 ; while(num)
    JNE CONVERT_LOOP
    MOV DL, '0'
    MOV AH, 2
    INT 21H
    RET
    
    CONVERT_LOOP:
; Can avoid this if condition is checked below as JNE CONVERT_LOOP and PRINT_DIGITS is called separately above.
        CMP AX, 0
        JE PRINT_DIGITS
        MOV DX, 0      ; Clear DX for division
        DIV BX         ; DX:AX / 10 => AX quotient, DX remainder
        PUSH DX        ; Push remainder (digit) onto stack
        INC CX
        JMP CONVERT_LOOP
        
    PRINT_DIGITS:
        CMP CX, 0
        JE END_PRINT
        POP DX         ; Pop digit from stack
        ADD DL, '0'    ; Convert to ASCII
        MOV AH, 2 
        INT 21H
        DEC CX
        JMP PRINT_DIGITS
        
    END_PRINT:
        RET
PRINT_NUM ENDP

END MAIN
