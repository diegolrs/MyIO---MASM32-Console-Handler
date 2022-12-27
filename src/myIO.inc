;-------------------------
; Library created to handle input and output commands
; Author: Diego Reis (@diegolrs)
; Date: 2022-12-26
; -------------------------

.data
;Console variables -------
_MyIO_inputInteger db 50 dup(0) ; Buffer variable to receive integers via console
_MyIO_break_line db 0AH, 0H

;Console handlers ----
_MyIO_inputHandle dd 0 ; Variable to store the input handle
_MyIO_outputHandle dd 0 ; Variable to store the output handle
_MyIO_console_count dd 0 ; Variable to store characters read/written in the console

.code
; Initialize input and output handlers to make use of MyIO functions ----
; Note: modifies EAX register
_MyIO_Setup PROC
    ;Prologue of the subroutine --------
    push ebp
    mov ebp, esp
    
    ;Configuring streams -----
    invoke GetStdHandle, STD_INPUT_HANDLE
    mov _MyIO_inputHandle, eax
    invoke GetStdHandle, STD_OUTPUT_HANDLE
    mov _MyIO_outputHandle, eax  

    ;Epilogue of the subroutine --------   
    mov esp, ebp
    pop ebp
    ret
_MyIO_Setup ENDP


; Print message to console --------
; param: offset string
; Note: modifies EAX register
_MyIO_LogMessage PROC
    ;Prologue of the subroutine --------
    push ebp
    mov ebp, esp
    sub esp, 4

    ;getting the address of the parameter string
    mov eax, DWORD PTR[ebp+8]
    mov DWORD PTR[ebp-4], eax
    
    invoke StrLen, DWORD PTR[ebp-4]
    invoke WriteConsole, _MyIO_outputHandle, DWORD PTR[ebp-4], eax, addr _MyIO_console_count, NULL

    ;Epilogue of the subroutine --------   
    mov esp, ebp
    pop ebp
    ret 4 ; returns and deallocates parameter (string address)
_MyIO_LogMessage ENDP


; Receives and integer and displays on console --------
; param: a integer do display
; Note: modifies EAX register
_MyIO_LogInteger PROC
    ;Prologue of the subroutine --------
    push ebp
    mov ebp, esp

    ;Call conversion
    mov eax, DWORD PTR[ebp+8]
    invoke dwtoa, eax, addr _MyIO_inputInteger ; save conversion locally
    push offset _MyIO_inputInteger
    call _MyIO_LogMessage

    ;Epilogue of the subroutine --------   
    mov esp, ebp
    pop ebp
    ret 4
_MyIO_LogInteger ENDP


; Writes breakline on console
; Note: modifies EAX register
_MYIO_BreakLine PROC
    ;Prologue of the subroutine --------
    push ebp
    mov ebp, esp

    push offset _MyIO_break_line
    call _MyIO_LogMessage

    ;Epilogue of the subroutine --------   
    mov esp, ebp
    pop ebp
    ret
_MYIO_BreakLine ENDP


; Receives and handles console input, removing CR character of the input string --------
; param: sizeof string, offset string
; Note: modifies EAX and ESI registers
_MyIO_ReadString PROC
    ;Prologue of the subroutine --------
    push ebp
    mov ebp, esp
 
    invoke ReadConsole, _MyIO_inputHandle, DWORD PTR[ebp+8], DWORD PTR[ebp+12], addr _MyIO_console_count, NULL

    mov eax, DWORD PTR[ebp+8]
    push eax
    call _MyIO_RemoveCarriageReturn

    ;Epilogue of the subroutine --------   
    mov esp, ebp
    pop ebp
    ret 8 ; deallocates both two parameters
_MyIO_ReadString ENDP
    

; Receives and handles console input, returning an integer in EAX --------
; Note: modifies EAX and ESI registers
; return: retorns the integer readed in EAX register
_MyIO_ReadInteger PROC
    ;Prologue of the subroutine --------
    push ebp
    mov ebp, esp
    
    ;Read from console
    invoke ReadConsole, _MyIO_inputHandle, addr _MyIO_inputInteger, sizeof _MyIO_inputInteger, addr _MyIO_console_count, NULL

    ;Removing CR character
    push offset _MyIO_inputInteger
    call _MyIO_RemoveCarriageReturn

    ;Call conversion
    invoke atodw, addr _MyIO_inputInteger ; the output integer will be saved in EAX

    ;Epilogue of the subroutine --------   
    mov esp, ebp
    pop ebp
    ret
_MyIO_ReadInteger ENDP


; Removing Carriage Return (CR, Enter)
; params: offset of a string to be treated
; Note: modifies EAX and ESI registers
_MyIO_RemoveCarriageReturn PROC
    ;Prologue of the subroutine --------
    push ebp
    mov ebp, esp

    ;esi=param
    mov esi, DWORD PTR[ebp+8] ; Store string pointer in esi
    
    _MyIO_RemoveCarriageReturn_Next:
        mov al, [esi] ; Move current character to al
        inc esi ; Point to the next character
        cmp al, 46 ; Check if less than ASCII 46 - FINALIZE
        jl _MyIO_RemoveCarriageReturn_End
        cmp al, 123 ; Check if less than ASCII 123 - CONTINUE
        jl _MyIO_RemoveCarriageReturn_Next
    _MyIO_RemoveCarriageReturn_End:
         dec esi ; Point to previous character
         xor al, al ; 0 or NULL
         mov [esi], al ; Insert NULL right after the end of the number

    ;Epilogue of the subroutine --------   
    mov esp, ebp
    pop ebp
    ret 4 ; returns and deallocates parameter (string address)
_MyIO_RemoveCarriageReturn ENDP