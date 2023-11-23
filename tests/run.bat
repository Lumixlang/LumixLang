@echo off
C:\Users\mathi\AppData\Local\bin\NASM\nasm.exe -f elf64 -o ./tests/connect.o ./tests/connect.asm
gcc -o ./tests/asm.exe ./tests/asm.c ./tests/connect.o
.\tests\asm.exe