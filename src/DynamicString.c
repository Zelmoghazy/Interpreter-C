#include "../include/DynamicString.h"

typedef struct DynamicString
{
    char *str;
    int END;
    int MAX;
}DynamicString;

int getEnd(DynamicString *str){
    return str->END;
}

int getCapacity(DynamicString *str){
    return str->MAX;
}

char* getCharArray(DynamicString *string){
    return string->str;
}

char getCharAt(DynamicString *string, int index){
    if(index > string->END){
        exit(EXIT_FAILURE);
    }else{
        return string->str[index];
    }
}

DynamicString* newStringInit(char * initialString){
    DynamicString *string = malloc(sizeof(DynamicString));
    if(string == NULL){
        exit(EXIT_FAILURE);
    }
    string->MAX = strlen(initialString)+1;
    string->END = 1;
    string->str = calloc(string->MAX,sizeof(char));
    if(string->str == NULL){
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < (int)strlen(initialString); i++){
        stringAppendchar(string,initialString[i]);
    }
    return string;
}

DynamicString* newString(int initialSize){
    DynamicString *string = malloc(sizeof(DynamicString));
    if(string == NULL){
        exit(EXIT_FAILURE);
    }
    string->MAX = initialSize+1;
    string->END = 1;
    string->str = calloc(string->MAX,sizeof(char));
    if(string->str == NULL){
        exit(EXIT_FAILURE);
    }
    return string;
}

void freeString(DynamicString *string){
    free(string->str);
    free(string);
}

void printString(DynamicString *string){
    printf("%s \n",string->str);
}

void Expand(DynamicString *string){
    string->MAX *= 1.5;
    char *Expanded = realloc(string->str,string->MAX*sizeof(char));
    if(Expanded == NULL){
        exit(EXIT_FAILURE);
    }
    string->str = Expanded;
    string->str[string->END]='\0';
}
void Shrink(DynamicString *string){
    string->MAX /= 1.5;
    char *Shrinked = realloc(string->str,string->MAX*sizeof(char));
    if(Shrinked == NULL){
        exit(EXIT_FAILURE);
    }
    string->str = Shrinked;
}

void stringAppendchar(DynamicString *string, char value){
    if(string->END < string->MAX){
        string->str[string->END-1] = value;
        string->str[string->END] = '\0';
        string->END++;
    }else{
        Expand(string);
        stringAppendchar(string,value);
    }
}

void stringConcat(DynamicString *string, char *str2)
{
    for (int i = 0; i < strlen(str2); i++){
        if (string->END < string->MAX){
            string->str[string->END - 1] = str2[i];
            string->str[string->END] = '\0';
            string->END++;
        }else{
            Expand(string);
            i--;
        }
    }
}

DynamicString *readFile(char* path){
    FILE *file = fopen(path, "r");
    DynamicString *str = newString(5);
    if (!file){
        fprintf(stderr, "Couldnt load file");
        exit(EXIT_FAILURE);
    }
    while (file){
        int ch = fgetc(file);
        if (ch == EOF)
            break;
        else
            stringAppendchar(str, (char)ch);
    }
    fclose(file);
    return str;
}

int CompareDS(DynamicString* s1, DynamicString* s2) {
    char* str1 = s1->str;
    char* str2 = s2->str;

    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

DynamicString *Substring(DynamicString* string, int start, int end){
    if(start>end){
        exit(EXIT_FAILURE);
    }
    DynamicString *newStr = newString(end-start+1);
    for (int i = start; i < end; i++)
    {
        stringAppendchar(newStr,getCharAt(string,i));
    }
    return newStr;
}