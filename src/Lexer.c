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
TokenType IdentifierFromToken(DynamicString identifier)
{
    int n = sizeof(name)/sizeof(name[0]);
    char *view = ds_char_array_view(identifier);
    for (int i = 0; i < n ; i++){
        if(!strcmp(view,name[i])){
            free(view);
            return (TokenType)i;
        }
    }
    free(view);
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
 *  look at the current character under examination (l.ch) and return a token depending on which character it is.
 *  Before returning the token we advance our pointers into the input so when we call NextToken() again
 *  the l.ch field is already updated.
 */
Token NextToken(Lexer* L) {
    Token tok;
    skipWhitespace(L);
    
    switch (L->ch) {
        case '=':
            if(peekChar(L) == '='){
                readChar(L);
                tok.Type = EQ;
                tok.Literal = ds_static_string("==");
            }else{
                tok.Type = ASSIGN;
                tok.Literal = ds_static_string("=");
            }
            break;
        case '+':
            tok.Type = PLUS;
            tok.Literal = ds_static_string("+");
            break;
        case '-':
            tok.Type = MINUS;
            tok.Literal = ds_static_string("-");
            break;
        case '!':
            if(peekChar(L)== '='){
                readChar(L);
                tok.Type = NEQ;
                tok.Literal = ds_static_string("!=");
            }else{
                tok.Type = BANG;
                tok.Literal = ds_static_string("!");
            }
            break;
        case '/':
            tok.Type = SLASH;
            tok.Literal = ds_static_string("/");
            break;
        case '*':
            tok.Type = ASTERISK;
            tok.Literal = ds_static_string("*");
            break;
        case '<':
            tok.Type = LT;
            tok.Literal = ds_static_string("<");
            break;
        case '>':
            tok.Type = GT;
            tok.Literal = ds_static_string(">");
            break;
        case ',':
            tok.Type = COMMA;
            tok.Literal = ds_static_string(",");
            break;
        case ';':
            tok.Type = SEMICOLON;
            tok.Literal = ds_static_string(";");
            break;
        case '(':
            tok.Type = LPAREN;
            tok.Literal = ds_static_string("(");
            break;
        case ')':
            tok.Type = RPAREN;
            tok.Literal = ds_static_string(")");
            break;
        case '{':
            tok.Type = LBRACE;
            tok.Literal = ds_static_string("{");
            break;
        case '}':
            tok.Type = RBRACE;
            tok.Literal = ds_static_string("}");
            break;
        case '\0':
            tok.Type = EOFILE;
            tok.Literal = ds_static_string("");
            break;
        default:{
            // L->ch is not a recognized character
            if(isLetter(L->ch)){
                tok.Literal = readIdentifier(L);
                tok.Type = IdentifierFromToken(tok.Literal);
                return tok;
            }else if(isDigit(L->ch)){
                tok.Literal = readNumber(L);
                tok.Type = INT;
                return tok;
            }
            else{
                // Dont know how to handle 
                tok.Type = ILLEGAL;
                tok.Literal = ds_static_substring(L->input,L->position,L->position+1);
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
DynamicString readIdentifier(Lexer *L){
    int position = L->position;
    while(isLetter(L->ch)){
        readChar(L);
    }
    return ds_static_substring(L->input,position,L->position);
}

DynamicString readNumber(Lexer *L){
    int position = L->position;
    while(isDigit(L->ch)){
        readChar(L);
    }
    return ds_static_substring(L->input,position,L->position);
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

size_t lineLength(char *line , int size){
    for (size_t i = 0; i < size; i++){
        if(line[i] == '\n'){
            return i+1;
        }
    }
    return 0;    
}

