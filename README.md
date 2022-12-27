# MyIO - MASM32 Console Handler
A library to handle console inputs using MASM32 Assembly. Allows the user to read strings and integers and write on console without use a macro library.

## How to run
- Requirements:
    - <a href="https://www.masm32.com/">Assembly Programming Language (MASM32 version)</a>
- First of all, you need to import MyIO Library to you source code. You can do this with the code:
```assembly
include myIO.inc
```
- Second of all, you need to setup MyIO Library to enable console write and read. You can do this with the code:
```assembly
call _MyIO_Setup
```
- After these steps, you will be able to use all MyIO Library functions.

## MyIO Library Functions
### Write string on console:
<dd>Convert integer to ASCII characters and then display on console:

```assembly
push offset stringVariable
call _MyIO_LogMessage
```
</dd>

### Write integer on console
<dd>Convert integer to ASCII characters and then display on console:

```assembly
push integerVariable
call _MyIO_LogInteger
```
</dd>

### Write break line ('/n') on console
<dd>Type enter on console:

```assembly
call _MYIO_BreakLine
```
</dd>

### Read an string
<dd>Read input from console, removing CR(enter) character from the end of the string:

```assembly
push sizeof stringVariable
push offset stringVariable
call _MyIO_ReadString ; save input readed into string variable
```
</dd>

### Read a integer
<dd>Read string and remove CR(enter), then make conversion to integer:

```assembly
call _MyIO_ReadInteger
mov integerVariable, eax
```
</dd>

## Authors
 - [@Diego Reis](https://www.github.com/diegolrs)
