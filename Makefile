CC = gcc

FILE = ./index.lum

OUTPUT = ./src/compiler/build/run.exe

lumix build: ./src/compiler/main/index.c ./src/compiler/fileReader/fileReader.c ./src/compiler/lexer/lexer.c ./src/compiler/lexer/lexerFunctions.c
	@$(CC) -c ./src/compiler/main/index.c -o ./src/compiler/bin/index.o
	@$(CC) -c ./src/compiler/fileReader/fileReader.c -o ./src/compiler/bin/fileReader.o
	@$(CC) -c ./src/compiler/lexer/lexer.c -o ./src/compiler/bin/lexer.o
	@$(CC) -c ./src/compiler/lexer/lexerFunctions.c -o ./src/compiler/subbin/lexerFunctions.o
	@$(CC) ./src/compiler/bin/lexer.o ./src/compiler/subbin/lexerFunctions.o ./src/compiler/bin/index.o ./src/compiler/bin/fileReader.o -o $(OUTPUT)

clean:
	@del /Q .\src\compiler\bin\fileReader.o .\src\compiler\bin\index.o .\src\compiler\bin\lexer.o .\src\compiler\subbin\lexerFunctions.o .\src\compiler\build\run.exe

run: ./src/cli/lumix.bat
	@cmd.exe /c "call ./src/cli/lumix.bat ${FILE}"

ruild rab rb: ./src/compiler/main/index.c ./src/compiler/fileReader/fileReader.c ./src/compiler/lexer/lexer.c ./src/compiler/lexer/lexerFunctions.c ./src/cli/lumix.bat
	@$(CC) -c ./src/compiler/main/index.c -o ./src/compiler/bin/index.o
	@$(CC) -c ./src/compiler/fileReader/fileReader.c -o ./src/compiler/bin/fileReader.o
	@$(CC) -c ./src/compiler/lexer/lexer.c -o ./src/compiler/bin/lexer.o
	@$(CC) -c ./src/compiler/lexer/lexerFunctions.c -o ./src/compiler/subbin/lexerFunctions.o
	@$(CC) ./src/compiler/bin/lexer.o ./src/compiler/subbin/lexerFunctions.o ./src/compiler/bin/index.o ./src/compiler/bin/fileReader.o -o $(OUTPUT)
	@cmd.exe /c "call ./src/cli/lumix.bat ${FILE}"