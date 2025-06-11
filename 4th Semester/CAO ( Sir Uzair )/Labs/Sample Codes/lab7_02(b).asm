.MODEL SMALL
.STACK 100h

.DATA
    INDEX DW 1
    MSG DB 'Current index: $'   
    nl DB 0Dh, 0Ah, '$'
    
.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX
    
    MOV CX, 50 
    MOV BX, 1
    
FOR_LOOP:
    MOV INDEX, BX  ; Store current index
    
    LEA DX, MSG
    MOV AH, 9
    INT 21H
    
    MOV AX, BX
    CALL PRINT_NUM
    

    LEA DX, nl
    MOV AH, 9
    INT 21h
    
    INC BX
    LOOP FOR_LOOP
    
    MOV AH, 4Ch
    INT 21h
MAIN ENDP

PRINT_NUM PROC     
    PUSH BX        
    PUSH CX        
    PUSH DX ; Save this at Top as needed for printNum   
    
    MOV CX, 0 
    MOV BX, 10 
    
    CMP AX, 0
    JNE CONVERT_LOOP
    MOV DL, '0'
    MOV AH, 2
    INT 21h
    JMP END_PRINT
    
CONVERT_LOOP:
    CMP AX, 0
    JE PRINT_DIGITS
    MOV DX, 0      ; Clear DX for division
    DIV BX         
    PUSH DX    
    INC CX 
    JMP CONVERT_LOOP
    
PRINT_DIGITS:
    POP DX 
    ADD DL, '0'
    MOV AH, 2 
    INT 21h
    DEC CX
    
    CMP CX, 0
    JNE PRINT_DIGITS
    
END_PRINT:
    ; Restore all in same order.
    POP DX         
    POP CX       
    POP BX      
    RET
PRINT_NUM ENDP

END MAIN