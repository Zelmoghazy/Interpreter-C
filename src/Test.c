#include "../include/Test.h"

void TestNextToken1() {
    DynamicString *input = ds_new_init("=+(){},;");
    int numTests = 9;
    const Token tests[] = {
        {ASSIGN,    ds_new_init("=")},
        {PLUS,      ds_new_init("+")},
        {LPAREN,    ds_new_init("(")},
        {RPAREN,    ds_new_init(")")},
        {LBRACE,    ds_new_init("{")},
        {RBRACE,    ds_new_init("}")},
        {COMMA,     ds_new_init(",")},
        {SEMICOLON, ds_new_init(";")},
        {EOFILE,    ds_new_init("")}
    };

    Lexer *L = NewLexer(input);
    for (int i = 0; i < numTests; i++) {
        Token expectedToken = tests[i];
        Token actualToken = NextToken(L);
        if (actualToken.Type != expectedToken.Type ||
            ds_compare(actualToken.Literal, expectedToken.Literal) != 0) 
        {
            printf("Test failed.");
        }else{
            printf("Success");
        }
    }
    ds_free(input);
}

void TestNextToken2(){
    DynamicString *input = ds_new_init(
    "let five = 5;"
    "let ten = 10;"
    "let add = fn(x,y){"
        "x+y;"
    "};"
    "let result = add(five,ten);"
    );
    const Token tests[] = {
        {LET,        ds_new_init("let")},
        {IDENTIFIER, ds_new_init("five")},
        {ASSIGN,     ds_new_init("=")},
        {INT,        ds_new_init("5")},
        {SEMICOLON,  ds_new_init(";")},
        {LET,        ds_new_init("let")},
        {IDENTIFIER, ds_new_init("ten")},
        {ASSIGN,     ds_new_init("=")},
        {INT,        ds_new_init("10")},
        {SEMICOLON,  ds_new_init(";")},
        {LET,        ds_new_init("let")},
        {IDENTIFIER, ds_new_init("add")},
        {ASSIGN,     ds_new_init("=")},
        {FUNCTION,   ds_new_init("fn")},
        {LPAREN,     ds_new_init("(")},
        {IDENTIFIER, ds_new_init("x")},
        {COMMA,      ds_new_init(",")},
        {IDENTIFIER, ds_new_init("y")},
        {RPAREN,     ds_new_init(")")},
        {LBRACE,     ds_new_init("{")},
        {IDENTIFIER, ds_new_init("x")},
        {PLUS,       ds_new_init("+")},
        {IDENTIFIER, ds_new_init("y")},
        {SEMICOLON,  ds_new_init(";")},
        {RBRACE,     ds_new_init("}")},
        {SEMICOLON,  ds_new_init(";")},
        {LET,        ds_new_init("let")},
        {IDENTIFIER, ds_new_init("result")},
        {ASSIGN,     ds_new_init("=")},
        {IDENTIFIER, ds_new_init("add")},
        {LPAREN,     ds_new_init("(")},
        {IDENTIFIER, ds_new_init("five")},
        {COMMA,      ds_new_init(",")},
        {IDENTIFIER, ds_new_init("ten")},
        {RPAREN,     ds_new_init(")")},
        {SEMICOLON,  ds_new_init(";")},
        {EOFILE,     ds_new_init("")}
    };
    Lexer *L = NewLexer(input);
    int numTests = 37;
    for (int i = 0; i < numTests; i++) {
        Token expectedToken = tests[i];
        Token actualToken = NextToken(L);
        if (actualToken.Type != expectedToken.Type ||
            ds_compare(actualToken.Literal, expectedToken.Literal) != 0) 
        {
            printf("fail\n");
        }else{
            printf("Success\n");
        }
    }
    ds_free(input);
}
