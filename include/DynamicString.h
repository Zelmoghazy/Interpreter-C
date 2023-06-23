#ifndef DS_HEADER
#define DS_HEADER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * end : String Length
 * max : String Capacity 
 */

typedef struct DynamicString{
    char  *str;
    size_t end;
    size_t max;
}DynamicString;

extern size_t ds_get_length(DynamicString *string);
extern size_t ds_get_capacity(DynamicString *string);
extern char* ds_get_char_array(DynamicString *string);
extern char ds_get_char_at(DynamicString *string, size_t index);
extern DynamicString* ds_new(size_t initialSize);
extern DynamicString* ds_new_init(char * initialString);
extern void ds_free(DynamicString *string);
extern void ds_print(DynamicString *string);
extern void ds_expand(DynamicString *string);
extern void ds_shrink(DynamicString *string);
extern void ds_append_char(DynamicString *string, char value);
extern void ds_concat(DynamicString *string, char *str2);
extern DynamicString *ds_read_file(char* path,bool(* filter)(char));
extern int ds_compare(DynamicString* s1,DynamicString *s2);
extern DynamicString *ds_substring(DynamicString* string, size_t start, size_t end);
extern void ds_copy(DynamicString* s1 , DynamicString* s2);
extern DynamicString ds_static_string(char * string);
extern DynamicString ds_static_substring(DynamicString* input, int start, int end);

#endif