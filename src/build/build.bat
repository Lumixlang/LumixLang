@echo off
gcc -c ./src/compiler/main/index.c -o ./src/compiler/bin/index.o
gcc -c ./src/compiler/fileReader/fileReader.c -o ./src/compiler/bin/fileReader.o
gcc -c ./src/compiler/lexer/lexer.c -o ./src/compiler/bin/lexer.o
gcc -c ./src/compiler/lexer/lexerFunctions.c -o ./src/compiler/subbin/lexerFunctions.o
gcc ./src/compiler/bin/lexer.o ./src/compiler/subbin/lexerFunctions.o ./src/compiler/bin/index.o ./src/compiler/bin/fileReader.o -o ./src/compiler/build/run.exe
echo Done building Lumix!