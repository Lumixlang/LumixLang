CC = gcc
FILE = ./index.lum
OUTPUT = ./src/compiler/build/run.exe

# Folder names
SRC = src
COMPILER = compiler
MAIN = main
FILEREADER = fileReader
LEXER = lexer
SUBBIN = subbin
BIN = bin
CLI = cli
BUILD = build

# File names
INDEX_C = index.c
INDEX_O = index.o
FILEREADER_C = fileReader.c
FILEREADER_O = fileReader.o
LEXER_C = lexer.c
LEXER_O = lexer.o
LEXERFUNCTIONS_C = lexerFunctions.c
LEXERFUNCTIONS_O = lexerFunctions.o
LUMIX_BAT = lumix.bat

lumix build: ./$(SRC)/$(COMPILER)/$(MAIN)/$(INDEX_C) ./$(SRC)/$(COMPILER)/$(FILEREADER)/$(FILEREADER_C) ./$(SRC)/$(COMPILER)/$(LEXER)/$(LEXER_C) ./$(SRC)/$(COMPILER)/$(LEXER)/$(LEXERFUNCTIONS_C)
	@$(CC) -c ./$(SRC)/$(COMPILER)/$(MAIN)/$(INDEX_C) -o ./$(SRC)/$(COMPILER)/$(BIN)/$(INDEX_O)
	@$(CC) -c ./$(SRC)/$(COMPILER)/$(FILEREADER)/$(FILEREADER_C) -o ./$(SRC)/$(COMPILER)/$(BIN)/$(FILEREADER_O)
	@$(CC) -c ./$(SRC)/$(COMPILER)/$(LEXER)/$(LEXER_C) -o ./$(SRC)/$(COMPILER)/$(BIN)/$(LEXER_O)
	@$(CC) -c ./$(SRC)/$(COMPILER)/$(LEXER)/$(LEXERFUNCTIONS_C) -o ./$(SRC)/$(COMPILER)/$(SUBBIN)/$(LEXERFUNCTIONS_O)
	@$(CC) ./$(SRC)/$(COMPILER)/$(BIN)/$(LEXER_O) ./$(SRC)/$(COMPILER)/$(SUBBIN)/$(LEXERFUNCTIONS_O) ./$(SRC)/$(COMPILER)/$(BIN)/$(INDEX_O) ./$(SRC)/$(COMPILER)/$(BIN)/$(FILEREADER_O) -o $(OUTPUT)

clean:
	@del /Q .\$(SRC)\$(COMPILER)\$(BIN)\$(FILEREADER_O) .\$(SRC)\$(COMPILER)\$(BIN)\$(INDEX_O) .\$(SRC)\$(COMPILER)\$(BIN)\$(LEXER_O) .\$(SRC)\$(COMPILER)\$(SUBBIN)\lexerFunctions.o .\$(SRC)\$(COMPILER)\$(BUILD)\run.exe

run: ./src/$(CLI)/$(LUMIX_BAT)
	@cmd.exe /c "call ./$(SRC)/$(CLI)/$(LUMIX_BAT) ${FILE}"

ruild rab rb: ./$(SRC)/$(COMPILER)/$(MAIN)/$(INDEX_C) ./$(SRC)/$(COMPILER)/$(FILEREADER)/$(FILEREADER_C) ./$(SRC)/$(COMPILER)/$(LEXER)/$(LEXER_C) ./$(SRC)/$(COMPILER)/$(LEXER)/$(LEXERFUNCTIONS_C) ./$(SRC)/$(CLI)/$(LUMIX_BAT)
	@$(CC) -c ./$(SRC)/$(COMPILER)/$(MAIN)/$(INDEX_C) -o ./$(SRC)/$(COMPILER)/$(BIN)/$(INDEX_O)
	@$(CC) -c ./$(SRC)/$(COMPILER)/$(FILEREADER)/$(FILEREADER_C) -o ./$(SRC)/$(COMPILER)/$(BIN)/$(FILEREADER_O)
	@$(CC) -c ./$(SRC)/$(COMPILER)/$(LEXER)/$(LEXER_C) -o ./$(SRC)/$(COMPILER)/$(BIN)/$(LEXER_O)
	@$(CC) -c ./$(SRC)/$(COMPILER)/$(LEXER)/$(LEXERFUNCTIONS_C) -o ./$(SRC)/$(COMPILER)/$(SUBBIN)/$(LEXERFUNCTIONS_O)
	@$(CC) ./$(SRC)/$(COMPILER)/$(BIN)/$(LEXER_O) ./$(SRC)/$(COMPILER)/$(SUBBIN)/$(LEXERFUNCTIONS_O) ./$(SRC)/$(COMPILER)/$(BIN)/$(INDEX_O) ./$(SRC)/$(COMPILER)/$(BIN)/$(FILEREADER_O) -o $(OUTPUT)
	@cmd.exe /c "call ./$(SRC)//$(CLI)/$(LUMIX_BAT) ${FILE}"