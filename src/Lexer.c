#include "../include/Lexer.h"

static const char *name[] =
{
    "ILLEGAL",
    "EOFILE",
    "IDENTIFIER",
    "INT",
    "=",
    "+",
    ",",
    ";",
    "(",
    ")",
    "{",
    "}",
    "FUNCTION",
    "LET",
};

const char *TokenTypeName(TokenType type)
{
    return name[type];
}

/**
 * checks the keywords table to see whether the given identifier is in fact a keyword.
 * If it is, it returns the keyword’s TokenType constant.
 * If it isn’t we just get back IDENTIFIER which is the
 * TokenType for all user-defined identifiers
 */
TokenType IdentifierFromToken(DynamicString* identifier){
    int n = sizeof(name)/sizeof(name[0]);
    for (int i = 0; i <n ; i++)
    {
        if(!strcmp(ds_get_char_array(identifier),name[i])){
            return i;
        }
    }
    return IDENTIFIER;
}

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
    ds_free(L->input);
    free(L);
}

/**
 * Give us next character and advance our position in the input string
 * it first checks whether we have reached the end of input
 * If that’s the case it sets l->ch the "NULL" character = 0
 * if we haven’t reached the end of input yet it sets l.ch to the next character by accessing l.input[l.readPosition].
 */

void readChar(Lexer *L){
    if (L->readPosition >= ds_get_length(L->input)){ // Exceeded the input
        L->ch = 0;
    }else{
        L->ch = ds_get_char_at(L->input,L->readPosition);   // set next character
    }
    L->position = L->readPosition;           // advance position
    L->readPosition++;                       // readposition always points to next position   
}

/**
 * Initialize Tokens  
 */
Token newToken(TokenType type, char ch) {
    Token token;
    token.Type = type;
    token.Literal = ds_new(1);
    ds_append_char(token.Literal,ch);
    return token;
}

void freeToken(Token T){
    ds_free(T.Literal);
}

/**
 *  look at the current character under examination (l.ch) and return a token depending on which character it is.
 *  Before returning the token we advance our pointers into the input so when we call NextToken() again
 *  the l.ch field is already updated.
 */
Token NextToken(Lexer* L) {
    Token tok;
    skipWhitespace(L);
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
            tok.Literal =  ds_new_init("");
            tok.Type = EOFILE;
            break;
        default:{
            if(isLetter(L->ch)){
                tok.Literal = readIdentifier(L);
                tok.Type = IdentifierFromToken(tok.Literal);
                return tok;
            }else{
                tok = newToken(ILLEGAL,L->ch);
            }
        }            
    }
    readChar(L);
    return tok;
}

DynamicString *readIdentifier(Lexer *L){
    int position = L->position;
    while(isLetter(L->ch)){
        readChar(L);
    }
    return ds_substring(L->input,position,L->position);
}

bool isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z') ||
            ch == '_';
}

void skipWhitespace(Lexer* l) {
    while (l->ch == ' ' || l->ch == '\t' || l->ch == '\n' || l->ch == '\r') {
        readChar(l);
    }
}