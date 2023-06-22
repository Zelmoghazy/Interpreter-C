#include "../include/DynamicString.h"

/** - Numbers -> INT
 *  - Variable names -> IDENTIFIERS
 *  - Language keywords -> FUNCTION, LET
 *  - Special Characters - > {},(),..      
 */

/* Tokens */
typedef enum
{
    ILLEGAL,    // token we dont know about
    EOFILE,     // End of file stop parsing
    
    IDENTIFIER, // x,y
    INT,        // 5,81

    /* Operators */
    ASSIGN,
    PLUS,
    MINUS,
    BANG,
    ASTERISK,
    SLASH,

    LT,
    GT,

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
    TokenType Type;         // Distinguish between different token types, ex: INT
    DynamicString* Literal; // Literal value of the token, ex "5"
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
Token newToken(TokenType type, DynamicString* string);
Token NextToken(Lexer* L);
DynamicString *readIdentifier(Lexer *L);
DynamicString *readNumber(Lexer *L);
bool isLetter(char ch);
bool isDigit(char ch);
const char *TokenTypeName(TokenType type);
void skipWhitespace(Lexer* l);