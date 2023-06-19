/*
 *  Tree-walking Interpreter
 *      - parse source code
 *      - build and abstract syntax tree
 *      - evaluate the tree 
 *  Parts 
 *      - Lexer
 *      - Parser
 *      - Abstract Syntax Tree
 *      - internal object system
 *      - evaluator
 * 
 *  1- Lexing : transforming source code to tokens
 *  2- Parsing : tokens are fed into the parser transforming it to the abstract syntax tree
 * 
 *  Tokens:
 *      - INTEGER -> numbers
 *      - IDENTIFIER -> variable names
 *      - KEYWORDS -> part of the language
 * 
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ILLEGAL "ILLEGAL" // token we dont know about
#define EOF "EOF"         // End of file stop parsing
#define IDENTIFIER "IDENTIFIER"
#define INT "INT"
#define ASSIGN "="
#define PLUS "+"
#define COMMA ","
#define SEMICOLON ";"
#define LPAREN "("
#define RPAREN "("
#define LBRACE "{"
#define RBRACE "}"
#define FUNCTION "FUNCTION"
#define LET "LET"




typedef TokenType char*;

typedef struct Token {
    TokenType Type;
    char* Literal;
} Token;

typedef struct Lexer{
    char* input;
    int position; // current position in input (points to current char)
    int readPosition; // current reading position in input (after current char)
    char ch; // current char under examination
}Lexer;

Lexer* NewLexer(char* input){
    Lexer *L = malloc(sizeof(Lexer));
    L->input = strdup(input);
    L->position = -1;
    L->readPosition = -1;
    L->ch = -1;
    return L;
}

void FreeLexer(Lexer* l){
    free(l->input);
    free(l);
}

/*
 * Give us next character and advance our position in the input string
 * it first checks whether we have reached the end of input
 * If that’s the case it sets l->ch to 0, which is the ASCII code for the "NULL" character
 * if we haven’t reached the end of input yet it sets l.ch to the next character by accessing l.input[l.readPosition].
 */
void readChar(Lexer *l){
    if (l->readPosition >= strlen(l->input))
    {
        l->ch = 0;
    }else{
        l->ch = l->input[l->readPosition];
    }
    l->position = l->readPosition;
    l->readPosition++;
    
}