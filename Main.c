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


#include "./include/Test.h"


int main(){
    TestNextToken2();
    system("pause");
}