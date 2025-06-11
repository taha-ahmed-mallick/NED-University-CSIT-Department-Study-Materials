.MODEL SMALL
.STACK 100h
.DATA
    PROMPT_A DB 'Enter value of a: $'
    PROMPT_B DB 0DH, 0AH, 'Enter value of b: $'
    PROMPT_C DB 0DH, 0AH, 'Enter value of c: $'
    RESULT_MSG DB 0DH, 0AH, 'Value of b*b-4*a*c: $'
    NEGATIVE_MSG DB '-$'
    
    A DW ?
    B DW ?
    C DW ?
    RESULT DW ?
    
.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX
    
    LEA DX, PROMPT_A
    MOV AH, 09h
    INT 21h
    CALL READ_NUMBER
    MOV A, AX
    
    LEA DX, PROMPT_B
    MOV AH, 09h
    INT 21h
    CALL READ_NUMBER
    MOV B, AX
    
    LEA DX, PROMPT_C
    MOV AH, 09h
    INT 21h
    CALL READ_NUMBER
    MOV C, AX
    

    CALL COMPUTE_DISCRIMINANT
    MOV RESULT, AX
    
    LEA DX, RESULT_MSG
    MOV AH, 09h
    INT 21h
    
    MOV AX, RESULT
    CMP AX, 0
    JGE PRINT_RESULT
    
    LEA DX, NEGATIVE_MSG
    MOV AH, 09h
    INT 21h
    NEG AX    ; Convert to positive
    
    PRINT_RESULT:
        CALL PRINT_NUMBER

    MOV AH, 4Ch
    INT 21h
MAIN ENDP


COMPUTE_DISCRIMINANT PROC
    MOV AX, B
    IMUL AX    ; AX = AX * AX = b * b
    MOV BX, AX 
    
    MOV AX, 4
    IMUL A
    IMUL C     ; AX = 4 * a * c
    
    SUB BX, AX
    MOV AX, BX ; Move result to AX for return
    
    RET
COMPUTE_DISCRIMINANT ENDP

READ_NUMBER PROC
    XOR BX, BX    ; BX will hold the result
    XOR CX, CX    ; CX is sign flag (0 = positive, 1 = negative)
    
    MOV AH, 01h
    INT 21h
    
    CMP AL, '-'
    JNE CHECK_DIGIT
    MOV CX, 1     ; Set sign flag
    JMP READ_NEXT
    
    CHECK_DIGIT:
        CMP AL, '0'
        JB FINISH_READ
        CMP AL, '9'
        JA FINISH_READ
        
        SUB AL, '0'
        XOR AH, AH
        MOV BX, AX
        
        READ_NEXT:
            MOV AH, 01h
            INT 21h
            
            CMP AL, '0'
            JB FINISH_READ
            CMP AL, '9'
            JA FINISH_READ
            
            PUSH AX
            MOV AX, 10
            IMUL BX   
            MOV BX, AX
            POP AX
            
            SUB AL, '0'
            XOR AH, AH
            ADD BX, AX 
            
            JMP READ_NEXT
        
        FINISH_READ:
            MOV AX, BX
            CMP CX, 1
            JNE DONE_READ
            NEG AX 
        
        DONE_READ:
            RET
READ_NUMBER ENDP


PRINT_NUMBER PROC
    PUSH BX
    PUSH CX
    PUSH DX
    
    MOV CX, 0
    MOV BX, 10   
    
    CMP AX, 0
    JNE START_CONVERSION
    MOV DL, '0'
    MOV AH, 2
    INT 21h
    JMP END_PRINT
    
    START_CONVERSION:
        CMP AX, 0
        JE PRINT_DIGITS
        XOR DX, DX 
        DIV BX  
        PUSH DX 
        INC CX      
        JMP START_CONVERSION
    
    PRINT_DIGITS:
        CMP CX, 0
        JE END_PRINT
        POP DX   
        ADD DL, '0' 
        MOV AH, 2
        INT 21h
        DEC CX
        JMP PRINT_DIGITS
    
    END_PRINT:
        POP DX
        POP CX
        POP BX
        RET
PRINT_NUMBER ENDP

END MAIN