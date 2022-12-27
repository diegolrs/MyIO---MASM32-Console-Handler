.686
.model flat, stdcall
option casemap :none

include \masm32\include\windows.inc
include \masm32\include\kernel32.inc
include \masm32\include\masm32.inc
includelib \masm32\lib\kernel32.lib
includelib \masm32\lib\masm32.lib

;Libraries created
include console-messages.inc
include myIO.inc

.data
    ;program variables
    integer1 dd 0H
    integer2 dd 0H
    string1 db 50 dup(0) ; string with max size = 50

.code   
start:
    call _MyIO_Setup ; Console input and output handler setup

    ;---- Writing string on console -----
    push offset CONSOLE_MSG_HELLO
    call _MyIO_LogMessage
    
    ;Requesting string -----------------
        ;---- Print message ----
        push offset CONSOLE_MSG_REQUEST_STR1
        call _MyIO_LogMessage

        ;---- Wait and handle input ----
        push sizeof string1
        push offset string1
        call _MyIO_ReadString

    ;Requesting first integer ---------
        ;---- Print message ----
        push offset CONSOLE_MSG_REQUEST_INT1
        call _MyIO_LogMessage

        ;---- Wait and handle input ----
        call _MyIO_ReadInteger
        mov integer1, eax

    ;Requesting second integer ---------
        ;---- Print message ----
        push offset CONSOLE_MSG_REQUEST_INT2
        call _MyIO_LogMessage

        ;---- Wait and handle input ----
        call _MyIO_ReadInteger
        mov integer2, eax

    ;Output ------------
        ;---- Print string readed ----
        push offset string1
        call _MyIO_LogMessage
        call _MYIO_BreakLine

        ;--- Print first integer ----
        push integer1
        call _MyIO_LogInteger
        call _MYIO_BreakLine

        ;--- Print second integer ----
        push integer2
        call _MyIO_LogInteger
        call _MYIO_BreakLine

        ;--- Print sum of the two integers inputs ----
        mov eax, integer1
        add eax, integer2 ; integer1 and integer2 already can be used as integers variables
        push eax
        call _MyIO_LogInteger
        
    invoke ExitProcess, 0
end start