#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DynamicString DynamicString;

int ds_get_capacity(DynamicString *string);
int ds_get_length(DynamicString *string);
char* ds_get_char_array(DynamicString *string);
char ds_get_char_at(DynamicString *string, int index);
DynamicString* ds_new(int initialSize);
DynamicString* ds_new_init(char * initialString);
void ds_free(DynamicString *string);
void ds_print(DynamicString *string);
void ds_expand(DynamicString *string);
void ds_shrink(DynamicString *string);
void ds_append_char(DynamicString *string, char value);
void ds_concat(DynamicString *string, char *str2);
DynamicString *ds_read_file(char* path,bool(* filter)(char));
int ds_compare(DynamicString* s1,DynamicString *s2);
DynamicString *ds_substring(DynamicString* string, int start, int end);
void ds_copy(DynamicString* s1 , DynamicString* s2);