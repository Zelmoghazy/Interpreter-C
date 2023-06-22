#include "../include/Test.h"

void TestNextToken1() {
    DynamicString *input = ds_new_init("=+(){},;");
    const Token tests[] = {
        {ASSIGN    ,  ds_new_init("=")},   
        {PLUS      ,  ds_new_init("+")},     
        {LPAREN    ,  ds_new_init("(")},   
        {RPAREN    ,  ds_new_init(")")},   
        {LBRACE    ,  ds_new_init("{")},   
        {RBRACE    ,  ds_new_init("}")},   
        {COMMA     ,  ds_new_init(",")},    
        {SEMICOLON ,  ds_new_init(";")},
        {EOFILE    ,  ds_new_init("")}   
    };
    
    size_t numTests = sizeof(tests)/sizeof(tests[0]);
    Lexer *L = NewLexer(input);

    for (size_t i = 0; i < numTests; i++) {
        Token expectedToken = tests[i];
        Token actualToken = NextToken(L);
        if (actualToken.Type != expectedToken.Type ||
            ds_compare(actualToken.Literal, expectedToken.Literal) != 0) 
        {
            printf("Failed.");
        }else{
            printf("Success.\n");
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
    size_t numTests = sizeof(tests)/sizeof(tests[0]);
    for (size_t i = 0; i < numTests; i++) {
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

void TestNextToken3(){
    DynamicString *input = ds_new_init(
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
		"\"foobar\""
		"\"foo bar\""
		"[1, 2];"
		"{\"foo\": \"bar\"}"
    );
    const Token tests[] = {
        {LET         ,ds_new_init("let")},
		{IDENTIFIER  ,ds_new_init("five")},
		{ASSIGN      ,ds_new_init("=")},
		{INT         ,ds_new_init("5")},
		{SEMICOLON   ,ds_new_init(";")},
		{LET         ,ds_new_init("let")},
		{IDENTIFIER  ,ds_new_init("ten")},
		{ASSIGN      ,ds_new_init("=")},
		{INT         ,ds_new_init("10")},
		{SEMICOLON   ,ds_new_init(";")},
		{LET         ,ds_new_init("let")},
		{IDENTIFIER  ,ds_new_init("add")},
		{ASSIGN      ,ds_new_init("=")},
		{FUNCTION    ,ds_new_init("fn")},
		{LPAREN      ,ds_new_init("(")},
		{IDENTIFIER  ,ds_new_init("x")},
		{COMMA       ,ds_new_init(",")},
		{IDENTIFIER  ,ds_new_init("y")},
		{RPAREN      ,ds_new_init(")")},
		{LBRACE      ,ds_new_init("{")},
		{IDENTIFIER  ,ds_new_init("x")},
		{PLUS        ,ds_new_init("+")},
		{IDENTIFIER  ,ds_new_init("y")},
		{SEMICOLON   ,ds_new_init(";")},
		{RBRACE      ,ds_new_init("}")},
		{SEMICOLON   ,ds_new_init(";")},
		{LET         ,ds_new_init("let")},
		{IDENTIFIER  ,ds_new_init("result")},
		{ASSIGN      ,ds_new_init("=")},
		{IDENTIFIER  ,ds_new_init("add")},
		{LPAREN      ,ds_new_init("(")},
		{IDENTIFIER  ,ds_new_init("five")},
		{COMMA       ,ds_new_init(",")},
		{IDENTIFIER  ,ds_new_init("ten")},
		{RPAREN      ,ds_new_init(")")},
		{SEMICOLON   ,ds_new_init(";")},
		{BANG        ,ds_new_init("!")},
		{MINUS       ,ds_new_init("-")},
		{SLASH       ,ds_new_init("/")},
		{ASTERISK    ,ds_new_init("*")},
		{INT         ,ds_new_init("5")},
		{SEMICOLON   ,ds_new_init(";")},
		{INT         ,ds_new_init("5")},
		{LT          ,ds_new_init("<")},
		{INT         ,ds_new_init("10")},
		{GT          ,ds_new_init(">")},
		{INT         ,ds_new_init("5")},
		{SEMICOLON   ,ds_new_init(";")},
		{IF          ,ds_new_init("if")},
		{LPAREN      ,ds_new_init("(")},
		{INT         ,ds_new_init("5")},
		{LT          ,ds_new_init("<")},
		{INT         ,ds_new_init("10")},
		{RPAREN      ,ds_new_init(")")},
		{LBRACE      ,ds_new_init("{")},
		{RETURN      ,ds_new_init("return")},
		{T           ,ds_new_init("true")},
		{SEMICOLON   ,ds_new_init(";")},
		{RBRACE      ,ds_new_init("}")},
		{ELSE        ,ds_new_init("else")},
		{LBRACE      ,ds_new_init("{")},
		{RETURN      ,ds_new_init("return")},
		{F           ,ds_new_init("false")},
		{SEMICOLON   ,ds_new_init(";")},
		{RBRACE      ,ds_new_init("}")},
		{INT         ,ds_new_init("10")},
		{EQUAL       ,ds_new_init("==")},
		{INT         ,ds_new_init("10")},
		{SEMICOLON   ,ds_new_init(";")},
		{INT         ,ds_new_init("10")},
		{NOTEQUAL    ,ds_new_init("!=")},
		{INT         ,ds_new_init("9")},
		{SEMICOLON   ,ds_new_init(";")},
		{STRING      ,ds_new_init("foobar")},
		{STRING      ,ds_new_init("foo bar")},
		{LBRACKET    ,ds_new_init("[")},
		{INT         ,ds_new_init("1")},
		{COMMA       ,ds_new_init(",")},
		{INT         ,ds_new_init("2")},
		{RBRACKET    ,ds_new_init("]")},
		{SEMICOLON   ,ds_new_init(";")},
		{LBRACE      ,ds_new_init("{")},
		{STRING      ,ds_new_init("foo")},
		{COLON       ,ds_new_init(":")},
		{STRING      ,ds_new_init("bar")},
		{RBRACE      ,ds_new_init("}")},
		{EOFILE      ,ds_new_init("")},
    };
    Lexer *L = NewLexer(input);
    size_t numTests = sizeof(tests)/sizeof(tests[0]);
    for (size_t i = 0; i < numTests; i++) {
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
