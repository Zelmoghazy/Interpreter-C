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
#include "./include/DynamicString.h"


typedef enum
{
    /* Tokens */
    ILLEGAL, // token we dont know about
    EOFILE,     // End of file stop parsing
    /* Identifiers */
    IDENTIFIER,
    INT,
    /* Operators */
    ASSIGN,
    PLUS,
    /* Delimiters */
    COMMA,
    SEMICOLON,

    LPAREN,
    RPAREN,
    LBRACE,
    RBRACE,
    /* Keywords */
    FUNCTION,
    LET
} TokenType;

typedef struct Token {
    TokenType Type;
    DynamicString* Literal;
} Token;

/** 
 *  Lexer
 *      - take source code as input and output the tokens that represent the source code. 
 *      - It will go through its input and output the next token it recognizes.
 */
typedef struct Lexer{
    DynamicString* input;
    int position;      // current position in input (points to current char)
    int readPosition;  // current reading position in input (after current char)
    char ch;           // current char under examination
}Lexer;

Lexer* NewLexer(DynamicString *input);
void FreeLexer(Lexer* L);
void readChar(Lexer *L);
void TestNextToken();
Token newToken(TokenType type, char ch);
Token NextToken(Lexer* L);



/**
 * Returns a new Lexer initialized with sourcecode(Constructor)
 * 
 * @param char* input - input sourcecode
 * @return {Lexer*} - new Lexer
 */

Lexer* NewLexer(DynamicString* input){
    Lexer *L = malloc(sizeof(Lexer));
    L->input = input;
    L->position = -1;
    L->readPosition = 0;
    L->ch = 0;
    readChar(L);
    return L;
}

/**
 * Free Allocated Memory
 */
void FreeLexer(Lexer* L){
    freeString(L->input);
    free(L);
}

/**
 * Give us next character and advance our position in the input string
 * it first checks whether we have reached the end of input
 * If that’s the case it sets l->ch the "NULL" character = 0
 * if we haven’t reached the end of input yet it sets l.ch to the next character by accessing l.input[l.readPosition].
 */

void readChar(Lexer *L){
    if (L->readPosition >= getEnd(L->input)){ // Exceeded the input
        L->ch = NULL;
    }else{
        L->ch = getCharAt(L->input,L->readPosition);   // set next character
    }
    L->position = L->readPosition;           // advance position
    L->readPosition++;                       // readposition always points to next position   
}


Token newToken(TokenType type, char ch) {
    Token token;
    token.Type = type;
    token.Literal = newString(1);
    stringAppendchar(token.Literal,ch);
    return token;
}


/**
 *  look at the current character under examination (l.ch) and return a token depending on which character it is.
 *  Before returning the token we advance our pointers into the input so when we call NextToken() again
 *  the l.ch field is already updated.
 */
Token NextToken(Lexer* L) {
    Token tok;

    switch (L->ch) {
        case '=':
            tok = newToken(ASSIGN, L->ch);
            break;
        case ';':
            tok = newToken(SEMICOLON, L->ch);
            break;
        case '(':
            tok = newToken(LPAREN, L->ch);
            break;
        case ')':
            tok = newToken(RPAREN, L->ch);
            break;
        case ',':
            tok = newToken(COMMA, L->ch);
            break;
        case '+':
            tok = newToken(PLUS, L->ch);
            break;
        case '{':
            tok = newToken(LBRACE, L->ch);
            break;
        case '}':
            tok = newToken(RBRACE, L->ch);
            break;
        case '\0':
            tok.Literal =  newStringInit("");
            tok.Type = EOFILE;
            break;
    }

    readChar(L);
    return tok;
}

void TestNextToken() {
    DynamicString *input = newStringInit("=+(){},;");
    int numTests = 9;
    Token tests[] = {
        {ASSIGN,    newStringInit("=")},
        {PLUS,      newStringInit("+")},
        {LPAREN,    newStringInit("(")},
        {RPAREN,    newStringInit(")")},
        {LBRACE,    newStringInit("{")},
        {RBRACE,    newStringInit("}")},
        {COMMA,     newStringInit(",")},
        {SEMICOLON, newStringInit(";")},
        {EOFILE,    newStringInit("")}
    };

    Lexer *L = NewLexer(input);
    for (int i = 0; i < numTests; i++) {
        Token expectedToken = tests[i];
        Token actualToken = NextToken(L);
        if (actualToken.Type != expectedToken.Type || CompareDS(actualToken.Literal, expectedToken.Literal) != 0) {
            printf("Test failed.");
        }else{
            printf("Success");
        }
    }
}

int main(){
    TestNextToken();
    system("pause");
}