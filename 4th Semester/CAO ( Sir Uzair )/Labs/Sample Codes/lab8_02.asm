.MODEL SMALL
.STACK 100h
.DATA
    WELCOME_MSG DB '===== Simple Calculator =====', 0Dh, 0Ah, '$'
    PROMPT_NUM1 DB 'Enter first number: $'
    PROMPT_NUM2 DB 'Enter second number: $'
    PROMPT_OP DB 'Enter operation (+, -, *, /): $'
    
    RESULT_MSG DB 'Result: $'
    INVALID_OP DB 0Dh, 0Ah, 'Invalid Operation!$'
    ERROR_DIV_ZERO DB 'Error: Division by zero!', 0Dh, 0Ah, '$'
    CONTINUE_MSG DB 0Dh, 0Ah, 'Another calculation? (Y/N): $'
    NEGATIVE_MSG DB '-$'
    
    NUM1 DW ?
    NUM2 DW ?
    RESULT DW ?
    OPERATION DB ?

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX
    
    LEA DX, WELCOME_MSG
    MOV AH, 9
    INT 21h
    
    CALCULATOR_LOOP:
        CALL NEW_LINE
        LEA DX, PROMPT_NUM1
        MOV AH, 9
        INT 21h
        CALL READ_NUMBER
        MOV NUM1, AX
        
        CALL NEW_LINE
        LEA DX, PROMPT_NUM2
        MOV AH, 9
        INT 21h
        CALL READ_NUMBER
        MOV NUM2, AX
        
        CALL NEW_LINE
        LEA DX, PROMPT_OP
        MOV AH, 9
        INT 21h
        
        MOV AH, 1
        INT 21h
        MOV OPERATION, AL
        CALL PERFORM_OPERATION
        
        LEA DX, CONTINUE_MSG
        MOV AH, 9
        INT 21h
 
        MOV AH, 1
        INT 21h
        
        CMP AL, 'Y'
        JE CALCULATOR_LOOP
        CMP AL, 'y'
        JE CALCULATOR_LOOP
    
    MOV AH, 4Ch
    INT 21h
MAIN ENDP

PERFORM_OPERATION PROC
    MOV AL, OPERATION
    
    CMP AL, '+'
    JE DO_ADDITION
    
    CMP AL, '-'
    JE DO_SUBTRACTION
    
    CMP AL, '*'
    JE DO_MULTIPLICATION
    
    CMP AL, '/'
    JE DO_DIVISION
    
    LEA DX, INVALID_OP
    MOV AH, 9
    INT 21h
    JMP DISPLAY_RESULT
    
DO_ADDITION:
    CALL ADD_NUMBERS
    JMP DISPLAY_RESULT
    
DO_SUBTRACTION:
    CALL SUBTRACT_NUMBERS
    JMP DISPLAY_RESULT
    
DO_MULTIPLICATION:
    CALL MULTIPLY_NUMBERS
    JMP DISPLAY_RESULT
    
DO_DIVISION:
    CALL DIVIDE_NUMBERS
    
DISPLAY_RESULT:
    CALL NEW_LINE
    LEA DX, RESULT_MSG
    MOV AH, 9
    INT 21h
    
    MOV AX, RESULT
    CMP AX, 0
    JGE PRINT_POSITIVE
    
    ; Currently underflow case
    LEA DX, NEGATIVE_MSG
    MOV AH, 9
    INT 21h
    NEG AX
    
PRINT_POSITIVE:
    CALL PRINT_NUMBER
    RET
PERFORM_OPERATION ENDP

ADD_NUMBERS PROC
    MOV AX, NUM1
    ADD AX, NUM2
    MOV RESULT, AX
    RET
ADD_NUMBERS ENDP

SUBTRACT_NUMBERS PROC
    MOV AX, NUM1
    SUB AX, NUM2
    MOV RESULT, AX
    RET
SUBTRACT_NUMBERS ENDP

MULTIPLY_NUMBERS PROC
    MOV AX, NUM1
    IMUL NUM2    ; AX = AX * NUM2
    
    MOV RESULT, AX
    RET
MULTIPLY_NUMBERS ENDP

DIVIDE_NUMBERS PROC
    ; Check for division by zero
    CMP NUM2, 0
    JNE PERFORM_DIVISION
    
    CALL NEW_LINE
    LEA DX, ERROR_DIV_ZERO
    MOV AH, 9
    INT 21h
    
    MOV RESULT, 0
    RET
    
PERFORM_DIVISION:
    MOV AX, NUM1
    CWD          ; Sign-extend AX into DX:AX
    IDIV NUM2    ; AX = DX:AX / NUM2, DX = remainder
    
    MOV RESULT, AX
    RET
DIVIDE_NUMBERS ENDP


READ_NUMBER PROC
    PUSH BX
    PUSH CX
    PUSH DX
    
    XOR BX, BX
    XOR CX, CX ; CX is sign flag (0 = positive, 1 = negative)
   
    MOV AH, 1
    INT 21h
    JMP READ_NEXT_DIGIT
    
    READ_NEXT:
        MOV AH, 1
        INT 21h
        
    READ_NEXT_DIGIT:
        ; Check if valid digit
        CMP AL, '0'
        JB FINISH_READ
        CMP AL, '9'
        JA FINISH_READ
        
        PUSH AX
        MOV AX, BX    ; Move current number to AX
        MOV BX, 10
        MUL BX        ; AX = AX * 10
        MOV BX, AX    ; Move result back to BX
        POP AX        ; Restore AL (the digit)
        
        SUB AL, '0'
        XOR AH, AH 
        ADD BX, AX    ; BX = BX + digit 
        JMP READ_NEXT
        
    FINISH_READ:
        MOV AX, BX
        CMP CX, 1
        JNE DONE_READ
        NEG AX 
        
    DONE_READ:
        POP DX
        POP CX
        POP BX
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
        XOR DX, DX         ; Clear DX for division
        DIV BX             ; DX:AX / 10 => AX quotient, DX remainder
        PUSH DX            ; Push remainder (digit) onto stack
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

NEW_LINE PROC
    PUSH AX
    PUSH DX
    
    MOV AH, 2
    MOV DL, 0Dh    ; Carriage return
    INT 21h
    MOV DL, 0Ah    ; Line feed
    INT 21h
    
    POP DX
    POP AX
    RET
NEW_LINE ENDP

END MAIN