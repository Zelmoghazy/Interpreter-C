#include "../include/repl.h"

void Start(FILE* in, FILE* out){
    DynamicString *line = ds_new(255);
    while (1) {
        printf(">> ");
        if (fgets(line->str, 255, in) == NULL) {
            return;
        }
        size_t line_length = lineLength(line->str,255);
        if (line->str[line_length - 1] == '\n') {
            line->str[line_length - 1] = '\0';
            line->end = line_length-1;
        }
        Lexer *L = NewLexer(line);
        
        while(1){
            Token tok = NextToken(L);
            if(tok.Type == EOFILE){
                break;
            }
            printf("-----------------\n");
            ds_print(&tok.Literal);
            printf("%s\n",TokenTypeName(tok.Type));
            printf("-----------------\n");    
        }
    }
}