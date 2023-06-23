#include "../include/Lexer.h"

static const char *name[] =
{
    "ILLEGAL",
    "EOFILE",
    "IDENTIFIER",
    "INT",
    "=",
    "+",
    "-",
    "!",
    "*",
    "/",
    "<",
    ">",
    "==",
    "!=",
    ",",
    ";",
    "(",
    ")",
    "{",
    "}",
    "fn",
    "let",
    "true",
    "false",
    "if",
    "else",
    "return"
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
TokenType IdentifierFromToken(DynamicString* identifier)
{
    int n = sizeof(name)/sizeof(name[0]);
    for (int i = 0; i <n ; i++){
        if(!strcmp(ds_get_char_array(identifier),name[i])){
            return (TokenType)i;
        }
    }
    return IDENTIFIER;
}

/**
 * Returns a new Lexer initialized with sourcecode(Constructor)
 */
Lexer* NewLexer(DynamicString* input)
{
    Lexer *L = malloc(sizeof(Lexer));
    if(L == NULL){
        printf("NewLexer: Allocation Failed");
        exit(EXIT_FAILURE);
    }
    L->input = input;
    L->position = 0;
    L->readPosition = 0;
    L->ch = 0;  
    readChar(L);
    return L;
}

/**
 * Free Allocated Memory
 */
void FreeLexer(Lexer* L)
{
    ds_free(L->input);
    free(L);
}

/**
 * Give us next character and advance our position in the input string
 * it first checks whether we have reached the end of input
 * If that’s the case it sets l->ch the "NULL" character = 0
 * if we haven’t reached the end of input yet it sets l.ch to the next character by accessing l.input[l.readPosition].
 * l.readPosition always points to the next position where we’re going to read from next
 * l.position always points to the position where we last read. 
 */

void readChar(Lexer *L)
{
    if (L->readPosition >= (int)ds_get_length(L->input)){ // Exceeded the input
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
Token newToken(TokenType type, DynamicString* string)
{
    Token token;
    token.Type = type;
    token.Literal = string;
    return token;
}

/**
 *  look at the current character under examination (l.ch) and return a token depending on which character it is.
 *  Before returning the token we advance our pointers into the input so when we call NextToken() again
 *  the l.ch field is already updated.
 */
Token NextToken(Lexer* L) {
    Token tok;
    skipWhitespace(L);
    
    char character[3];
    character[0] = L->ch;
    character[1] = '\0';
    character[2] = '\0';

    DynamicString s_ch;

    switch (L->ch) {
        case '=':
            if(peekChar(L) == '='){
                character[1] = '=';
                readChar(L);
                s_ch = ds_static_string(character);
                tok = newToken(EQ,&s_ch);
            }else{
                s_ch = ds_static_string(character);
                tok = newToken(ASSIGN, &s_ch);
            }
            break;
        case '+':
            s_ch = ds_static_string(character);
            tok = newToken(PLUS, &s_ch);
            break;
        case '-':
            s_ch = ds_static_string(character);
            tok = newToken(MINUS, &s_ch);
            break;
        case '!':
            if(peekChar(L)== '='){
                character[1] = '=';
                readChar(L);
                s_ch = ds_static_string(character);
                tok = newToken(NEQ,&s_ch);
            }else{
                s_ch = ds_static_string(character);
                tok = newToken(BANG, &s_ch);
            }
            break;
        case '/':
            s_ch = ds_static_string(character);
            tok = newToken(SLASH, &s_ch);
            break;
        case '*':
            s_ch = ds_static_string(character);
            tok = newToken(ASTERISK, &s_ch);
            break;
        case '<':
            s_ch = ds_static_string(character);
            tok = newToken(LT, &s_ch);
            break;
        case '>':
            s_ch = ds_static_string(character);
            tok = newToken(GT, &s_ch);
            break;
        case ',':
            s_ch = ds_static_string(character);
            tok = newToken(COMMA, &s_ch);
            break;
        case ';':
            s_ch = ds_static_string(character);
            tok = newToken(SEMICOLON, &s_ch);
            break;
        case '(':
            s_ch = ds_static_string(character);
            tok = newToken(LPAREN, &s_ch);
            break;
        case ')':
            s_ch = ds_static_string(character);
            tok = newToken(RPAREN, &s_ch);
            break;
        case '{':
            s_ch = ds_static_string(character);
            tok = newToken(LBRACE, &s_ch);
            break;
        case '}':
            s_ch = ds_static_string(character);
            tok = newToken(RBRACE, &s_ch);
            break;
        case '\0':
            character[0] = '\0';
            s_ch = ds_static_string(character);
            tok.Literal = &s_ch;
            tok.Type = EOFILE;
            break;
        default:{
            // L->ch is not a recognized character
            if(isLetter(L->ch)){
                tok.Literal = readIdentifier(L);
                tok.Type = IdentifierFromToken(tok.Literal);
                return tok;
            }else if(isDigit(L->ch)){
                tok.Type = INT;
                tok.Literal = readNumber(L);
                return tok;
            }
            else{
                // Dont know how to handle 
                s_ch = ds_static_string(character);
                tok = newToken(ILLEGAL,&s_ch);
            }
        }            
    }
    readChar(L);
    return tok;
}

/**
 *  reads in an identifier and advances our lexer’s positions
 *  until it encounters a non-letter-character. 
 */
DynamicString *readIdentifier(Lexer *L){
    int position = L->position;
    while(isLetter(L->ch)){
        readChar(L);
    }
    return ds_substring(L->input,position,L->position);
}

DynamicString *readNumber(Lexer *L){
    int position = L->position;
    while(isDigit(L->ch)){
        readChar(L);
    }
    return ds_substring(L->input,position,L->position);
}

/**
 *  Checks whether the given argument is a letter. 
 */
bool isLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') ||
           (ch >= 'A' && ch <= 'Z') ||
            ch == '_';
}

bool isDigit(char ch){
    return (ch >= '0' && ch <= '9');
}

void skipWhitespace(Lexer* l) {
    while (l->ch == ' '  ||
           l->ch == '\t' ||
           l->ch == '\n' ||
           l->ch == '\r') 
    {
        readChar(l);
    }
}

/**
 *  “peek” ahead in the input and not move around in it 
 */
char peekChar(Lexer *l){
    if(l->readPosition >= ds_get_length(l->input))
        return 0;
    else
        return l->input->str[l->readPosition];
}