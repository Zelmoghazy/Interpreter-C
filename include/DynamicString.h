#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DynamicString DynamicString;
int getEnd(DynamicString *str);
int getCapacity(DynamicString *str);
char* getCharArray(DynamicString *string);
char getCharAt(DynamicString *string, int index);
void stringAppendchar(DynamicString *string, char value);
void stringConcat(DynamicString *string, char *str2);
DynamicString* newStringInit(char * initialString);
DynamicString* newString(int initialSize);
void freeString(DynamicString *string);
void printString(DynamicString *string);
void Expand(DynamicString *string);
void Shrink(DynamicString *string);
DynamicString *readFile(char* path);
int CompareDS(DynamicString* s1,DynamicString *s2);
DynamicString *Substring(DynamicString* string, int start, int end);