#include "../include/Test.h"

void TestNextToken1() {
    DynamicString *input = newStringInit("=+(){},;");
    int numTests = 9;
    const Token tests[] = {
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
        if (actualToken.Type != expectedToken.Type ||
            CompareDS(actualToken.Literal, expectedToken.Literal) != 0) 
        {
            printf("Test failed.");
        }else{
            printf("Success");
        }
    }
    freeString(input);
}

void TestNextToken2(){
    DynamicString *input = newStringInit(
    "let five = 5;"
    "let ten = 10;"
    "let add = fn(x,y){"
        "x+y;"
    "};"
    "let result = add(five,ten);"
    );
    const Token tests[] = {
        {LET,        newStringInit("let")},
        {IDENTIFIER, newStringInit("five")},
        {ASSIGN,     newStringInit("=")},
        {INT,        newStringInit("5")},
        {SEMICOLON,  newStringInit(";")},
        {LET,        newStringInit("let")},
        {IDENTIFIER, newStringInit("ten")},
        {ASSIGN,     newStringInit("=")},
        {INT,        newStringInit("10")},
        {SEMICOLON,  newStringInit(";")},
        {LET,        newStringInit("let")},
        {IDENTIFIER, newStringInit("add")},
        {ASSIGN,     newStringInit("=")},
        {FUNCTION,   newStringInit("fn")},
        {LPAREN,     newStringInit("(")},
        {IDENTIFIER, newStringInit("x")},
        {COMMA,      newStringInit(",")},
        {IDENTIFIER, newStringInit("y")},
        {RPAREN,     newStringInit(")")},
        {LBRACE,     newStringInit("{")},
        {IDENTIFIER, newStringInit("x")},
        {PLUS,       newStringInit("+")},
        {IDENTIFIER, newStringInit("y")},
        {SEMICOLON,  newStringInit(";")},
        {RBRACE,     newStringInit("}")},
        {SEMICOLON,  newStringInit(";")},
        {LET,        newStringInit("let")},
        {IDENTIFIER, newStringInit("result")},
        {ASSIGN,     newStringInit("=")},
        {IDENTIFIER, newStringInit("add")},
        {LPAREN,     newStringInit("(")},
        {IDENTIFIER, newStringInit("five")},
        {COMMA,      newStringInit(",")},
        {IDENTIFIER, newStringInit("ten")},
        {RPAREN,     newStringInit(")")},
        {SEMICOLON,  newStringInit(";")},
        {EOFILE,     newStringInit("")}
    };
    Lexer *L = NewLexer(input);
    int numTests = 37;
    for (int i = 0; i < numTests; i++) {
        Token expectedToken = tests[i];
        Token actualToken = NextToken(L);
        if (actualToken.Type != expectedToken.Type ||
            CompareDS(actualToken.Literal, expectedToken.Literal) != 0) 
        {
            printf("fail\n");
        }else{
            printf("Success\n");
        }
    }

    freeString(input);
}
