#include "../include/DynamicString.h"

typedef enum
{
    /* Tokens */
    ILLEGAL,    // token we dont know about
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
DynamicString *readIdentifier(Lexer *L);
bool isLetter(char ch);
const char *TokenTypeName(TokenType type);