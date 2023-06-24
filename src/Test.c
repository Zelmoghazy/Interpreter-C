#include "../include/Test.h"

void TestNextToken1() {
    DynamicString input = ds_static_string("=+(){},;");
    const Token tests[] = {
        {ASSIGN    ,  ds_static_string("=")},   
        {PLUS      ,  ds_static_string("+")},     
        {LPAREN    ,  ds_static_string("(")},   
        {RPAREN    ,  ds_static_string(")")},   
        {LBRACE    ,  ds_static_string("{")},   
        {RBRACE    ,  ds_static_string("}")},   
        {COMMA     ,  ds_static_string(",")},    
        {SEMICOLON ,  ds_static_string(";")},
        {EOFILE    ,  ds_static_string("")}   
    };
    
    size_t numTests = sizeof(tests)/sizeof(tests[0]);
    Lexer *L = NewLexer(&input);

    for (size_t i = 0; i < numTests; i++) {
        Token expectedToken = tests[i];
        Token actualToken = NextToken(L);
        if (actualToken.Type != expectedToken.Type ||
            ds_static_compare(actualToken.Literal, expectedToken.Literal) != 0) 
        {
            printf("Failed.");
        }else{
            printf("Success.\n");
        }
    }
    FreeLexer(L);
}

void TestNextToken2(){
    DynamicString input = ds_static_string(
    "let five = 5;"
    "let ten = 10;"
    "let add = fn(x,y){"
        "x+y;"
    "};"
    "let result = add(five,ten);"
    );
    const Token tests[] = {
        {LET,        ds_static_string("let")},
        {IDENTIFIER, ds_static_string("five")},
        {ASSIGN,     ds_static_string("=")},
        {INT,        ds_static_string("5")},
        {SEMICOLON,  ds_static_string(";")},
        {LET,        ds_static_string("let")},
        {IDENTIFIER, ds_static_string("ten")},
        {ASSIGN,     ds_static_string("=")},
        {INT,        ds_static_string("10")},
        {SEMICOLON,  ds_static_string(";")},
        {LET,        ds_static_string("let")},
        {IDENTIFIER, ds_static_string("add")},
        {ASSIGN,     ds_static_string("=")},
        {FUNCTION,   ds_static_string("fn")},
        {LPAREN,     ds_static_string("(")},
        {IDENTIFIER, ds_static_string("x")},
        {COMMA,      ds_static_string(",")},
        {IDENTIFIER, ds_static_string("y")},
        {RPAREN,     ds_static_string(")")},
        {LBRACE,     ds_static_string("{")},
        {IDENTIFIER, ds_static_string("x")},
        {PLUS,       ds_static_string("+")},
        {IDENTIFIER, ds_static_string("y")},
        {SEMICOLON,  ds_static_string(";")},
        {RBRACE,     ds_static_string("}")},
        {SEMICOLON,  ds_static_string(";")},
        {LET,        ds_static_string("let")},
        {IDENTIFIER, ds_static_string("result")},
        {ASSIGN,     ds_static_string("=")},
        {IDENTIFIER, ds_static_string("add")},
        {LPAREN,     ds_static_string("(")},
        {IDENTIFIER, ds_static_string("five")},
        {COMMA,      ds_static_string(",")},
        {IDENTIFIER, ds_static_string("ten")},
        {RPAREN,     ds_static_string(")")},
        {SEMICOLON,  ds_static_string(";")},
        {EOFILE,     ds_static_string("")}
    };
    Lexer *L = NewLexer(&input);
    size_t numTests = sizeof(tests)/sizeof(tests[0]);
    for (size_t i = 0; i < numTests; i++) {
        Token expectedToken = tests[i];
        Token actualToken = NextToken(L);
        if (actualToken.Type != expectedToken.Type ||
            ds_static_compare(actualToken.Literal, expectedToken.Literal) != 0) 
        {
            printf("fail\n");
        }else{
            printf("Success\n");
        }
    }
    FreeLexer(L);
}

void TestNextToken3(){
    DynamicString input = ds_static_string(
        "let five = 5;"
		"let ten = 10;"
		"let add = fn(x, y) {"
			"x + y;"
		"};"
		"let result = add(five, ten);"
		"!-/*5;"
		"5 < 10 > 5;"
		"if (5 < 10) {"
			"return true;"
		"} else {"
			"return false;"
		"}"
		"10 == 10;"
		"10 != 9;"
		// "\"foobar\""
		// "\"foo bar\""
		// "[1, 2];"
		// "{\"foo\": \"bar\"}"
    );
    const Token tests[] = {
        {LET         ,ds_static_string("let")},
		{IDENTIFIER  ,ds_static_string("five")},
		{ASSIGN      ,ds_static_string("=")},
		{INT         ,ds_static_string("5")},
		{SEMICOLON   ,ds_static_string(";")},
		{LET         ,ds_static_string("let")},
		{IDENTIFIER  ,ds_static_string("ten")},
		{ASSIGN      ,ds_static_string("=")},
		{INT         ,ds_static_string("10")},
		{SEMICOLON   ,ds_static_string(";")},
		{LET         ,ds_static_string("let")},
		{IDENTIFIER  ,ds_static_string("add")},
		{ASSIGN      ,ds_static_string("=")},
		{FUNCTION    ,ds_static_string("fn")},
		{LPAREN      ,ds_static_string("(")},
		{IDENTIFIER  ,ds_static_string("x")},
		{COMMA       ,ds_static_string(",")},
		{IDENTIFIER  ,ds_static_string("y")},
		{RPAREN      ,ds_static_string(")")},
		{LBRACE      ,ds_static_string("{")},
		{IDENTIFIER  ,ds_static_string("x")},
		{PLUS        ,ds_static_string("+")},
		{IDENTIFIER  ,ds_static_string("y")},
		{SEMICOLON   ,ds_static_string(";")},
		{RBRACE      ,ds_static_string("}")},
		{SEMICOLON   ,ds_static_string(";")},
		{LET         ,ds_static_string("let")},
		{IDENTIFIER  ,ds_static_string("result")},
		{ASSIGN      ,ds_static_string("=")},
		{IDENTIFIER  ,ds_static_string("add")},
		{LPAREN      ,ds_static_string("(")},
		{IDENTIFIER  ,ds_static_string("five")},
		{COMMA       ,ds_static_string(",")},
		{IDENTIFIER  ,ds_static_string("ten")},
		{RPAREN      ,ds_static_string(")")},
		{SEMICOLON   ,ds_static_string(";")},
		{BANG        ,ds_static_string("!")},
		{MINUS       ,ds_static_string("-")},
		{SLASH       ,ds_static_string("/")},
		{ASTERISK    ,ds_static_string("*")},
		{INT         ,ds_static_string("5")},
		{SEMICOLON   ,ds_static_string(";")},
		{INT         ,ds_static_string("5")},
		{LT          ,ds_static_string("<")},
		{INT         ,ds_static_string("10")},
		{GT          ,ds_static_string(">")},
		{INT         ,ds_static_string("5")},
		{SEMICOLON   ,ds_static_string(";")},
		{IF          ,ds_static_string("if")},
		{LPAREN      ,ds_static_string("(")},
		{INT         ,ds_static_string("5")},
		{LT          ,ds_static_string("<")},
		{INT         ,ds_static_string("10")},
		{RPAREN      ,ds_static_string(")")},
		{LBRACE      ,ds_static_string("{")},
		{RETURN      ,ds_static_string("return")},
		{T           ,ds_static_string("true")},
		{SEMICOLON   ,ds_static_string(";")},
		{RBRACE      ,ds_static_string("}")},
		{ELSE        ,ds_static_string("else")},
		{LBRACE      ,ds_static_string("{")},
		{RETURN      ,ds_static_string("return")},
		{F           ,ds_static_string("false")},
		{SEMICOLON   ,ds_static_string(";")},
		{RBRACE      ,ds_static_string("}")},
		{INT         ,ds_static_string("10")},
		{EQ          ,ds_static_string("==")},
		{INT         ,ds_static_string("10")},
		{SEMICOLON   ,ds_static_string(";")},
		{INT         ,ds_static_string("10")},
		{NEQ         ,ds_static_string("!=")},
		{INT         ,ds_static_string("9")},
		{SEMICOLON   ,ds_static_string(";")},
		// {STRING      ,ds_static_string("foobar")},
		// {STRING      ,ds_static_string("foo bar")},
		// {LBRACKET    ,ds_static_string("[")},
		// {INT         ,ds_static_string("1")},
		// {COMMA       ,ds_static_string(",")},
		// {INT         ,ds_static_string("2")},
		// {RBRACKET    ,ds_static_string("]")},
		// {SEMICOLON   ,ds_static_string(";")},
		// {LBRACE      ,ds_static_string("{")},
		// {STRING      ,ds_static_string("foo")},
		// {COLON       ,ds_static_string(":")},
		// {STRING      ,ds_static_string("bar")},
		// {RBRACE      ,ds_static_string("}")},
		{EOFILE       ,ds_static_string("")}
    };
    Lexer *L = NewLexer(&input);
    size_t numTests = sizeof(tests)/sizeof(tests[0]);
    for (size_t i = 0; i < numTests; i++) {
        Token expectedToken = tests[i];
        Token actualToken = NextToken(L);
        if (actualToken.Type != expectedToken.Type ||
            ds_static_compare(actualToken.Literal, expectedToken.Literal) != 0) 
        {
            printf("fail\n");
        }else{
            printf("Success\n");
        }
    }
    FreeLexer(L);
}
