CC = gcc

lumix: ./src/compiler/main/index.c ./src/compiler/fileReader/fileReader.c ./src/compiler/lexer/lexer.c ./src/compiler/lexer/lexerFunctions.c
	$(CC) -c ./src/compiler/main/index.c -o ./src/compiler/bin/index.o
	$(CC) -c ./src/compiler/fileReader/fileReader.c -o ./src/compiler/bin/fileReader.o
	$(CC) -c ./src/compiler/lexer/lexer.c -o ./src/compiler/bin/lexer.o
	$(CC) -c ./src/compiler/lexer/lexerFunctions.c -o ./src/compiler/subbin/lexerFunctions.o
	$(CC) ./src/compiler/bin/lexer.o ./src/compiler/subbin/lexerFunctions.o ./src/compiler/bin/index.o ./src/compiler/bin/fileReader.o -o ./src/compiler/build/run.exe