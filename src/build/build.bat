@echo off
gcc -c ./src/compiler/main/index.c -o ./src/compiler/bin/index.o
gcc -c ./src/compiler/lexer/lexer.c -o ./src/compiler/bin/lexer.o
gcc ./src/compiler/bin/lexer.o ./src/compiler/bin/index.o -o ./src/compiler/build/run.exe
echo Done building Lumix!