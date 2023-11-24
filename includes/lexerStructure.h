#ifndef LEXERSTRUCTURE_H
#define LEXERSTRUCTURE_H

struct Token {

    // Function
    struct Function {
        struct KeywordFunction {
            char value[MAX_LEN];
        } keywordFunction;
        struct InsideFunction {
            char value[MAX_LEN];
            char type[10];
        } insideFunction;
    } function;

    // Variable
    struct Variable {
        struct TypeVariable {
            char value[MAX_LEN];
        } typeVariable;
        struct NameVariable {
            char value[MAX_LEN];
        } nameVariable;
        struct Operator {
            char value[MAX_LEN];
        } OperatorVariable;
        struct InsideVariable {
            char value[MAX_LEN];
            char type[MAX_LEN];
        } insideVariable;
    } variable;

    // If Statement
    struct IfStatement {
        struct Statement {
            char value[MAX_LEN];
        } statementIfStatement;
        struct InsideIfStatement {
            char value[MAX_LEN];
        } insideIfStatement;
    } ifStatement;
    
    // Error
    struct Error {
            char message[100];
            char codePart[MAX_LEN];
    } error;
};

#endif