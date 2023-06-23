#include "../include/DynamicString.h"



/**
 *  Access Internal string data through those only  
 */
size_t ds_get_length(DynamicString *string){
    return string->end;
}

size_t ds_get_capacity(DynamicString *string){
    return string->max;
}

char* ds_get_char_array(DynamicString *string){
    return string->str;
}

char ds_get_char_at(DynamicString *string, size_t index){
    if(index > string->end){
        printf("getCharAt: Index Exceeded string length\n");
        return string->str[string->end-1];
    }else{
        return string->str[index];
    }
}

/**
 *  Constructor that takes an initial size 
 */
DynamicString* ds_new(size_t initialSize){
    DynamicString *string = malloc(sizeof(DynamicString));
    if(string == NULL){
        printf("newString: Allocation failed\n");
        exit(EXIT_FAILURE);
    }
    string->max = initialSize+1;
    string->end = 0;
    string->str = malloc(string->max*sizeof(char));
    if(string->str == NULL){
        printf("newString: str allocation failed\n");
        exit(EXIT_FAILURE);
    }
    string->str[string->end] = '\0';
    return string;
}

/**
 *  Constructor that takes an initial string 
 */
DynamicString* ds_new_init(char * initialString){
    size_t size = strlen(initialString);
    DynamicString *string = ds_new(size);
    if(size == 0){
        string->str[0] = '\0';
    }
    for (size_t i = 0; i < size; i++){
        ds_append_char(string,initialString[i]);
    }
    return string;
}


/**
 *  Free Allocated memory 
 */
void ds_free(DynamicString *string){
    free(string->str);
    string->str = NULL;
    free(string);
}

/**
 *  Print String 
 */
void ds_print(DynamicString *string){
    for (size_t i =0 ; i < string->end; i++){
        printf("%c",string->str[i]);
    }
    printf("\n");  
}

/**
 *  Expand String when capacity is exceeded.
 */
void ds_expand(DynamicString *string){
    string->max *= 2;
    char *Expanded = realloc(string->str,string->max*sizeof(char));
    if(Expanded == NULL){
        printf("Expand: reallocation failed\n");
        exit(EXIT_FAILURE);
    }
    string->str = Expanded;
}

/**
 *  Shrink String when only quarter of capacity is used.
 */
void ds_shrink(DynamicString *string){
    string->max /= 2;
    char *Shrinked = realloc(string->str,string->max*sizeof(char));
    if(Shrinked == NULL){
        printf("Shrink: reallocation failed\n");
        exit(EXIT_FAILURE);
    }
    string->str = Shrinked;
}

/**
 *  Append a character to end of string 
 *  expand automatically when capacity exceeded.
 */
void ds_append_char(DynamicString *string, char value){
    if(string->end < string->max){
        string->end++;
        string->str[string->end-1] = value;
        string->str[string->end] = '\0';
    }else{
        ds_expand(string);
        ds_append_char(string,value);
    }
}

/**
 *  Concatenate a char array to the string.
 */
void ds_concat(DynamicString *string, char *str2){
    size_t size = strlen(str2);
    for (size_t i = 0; i < size; i++){
        if (string->end < string->max){
            string->str[string->end - 1] = str2[i];
            string->str[string->end] = '\0';
            string->end++;
        }else{
            ds_expand(string);
            i--;
        }
    }
}

/**
 *  Read a file into the string character by character.
 *  Filter is required.
 */
DynamicString *ds_read_file(char* path, bool(* filter)(char)){
    FILE *file = fopen(path, "r");
    DynamicString *str = ds_new(20);
    if (!file){
        fprintf(stderr, "Couldnt load file\n");
        exit(EXIT_FAILURE);
    }
    while (file){
        int ch = fgetc(file);
        if (ch == EOF)
            break;
        else if (filter((char)ch))
            continue;            
        else
            ds_append_char(str, (char)ch);
    }
    fclose(file);
    return str;
}

/**
 *  returns 0 if equal
 */
int ds_compare(DynamicString* s1, DynamicString* s2) {
    if(s1->end != s2->end){
        return -1;
    }else{
        for (size_t i = 0; i < s1->end; i++){
            if(s1->str[i] != s2->str[i]){
                return -1;
            }
        }
        return 0;
    }
}

/**
 *  returns a substring as a new string.
 */
DynamicString *ds_substring(DynamicString* string, size_t start, size_t end){
    if(start > end){
        printf("Substring: start exceeds end");
        int temp = start;
        start = end;
        end = temp;
    }
    if(end > string->end){
        printf("Substring: end exceeds string length");
        end = string->end;
    }
    DynamicString *newStr = ds_new(end-start+1);
    for (size_t i = start; i < end; i++){
        ds_append_char(newStr,ds_get_char_at(string,i));
    }
    return newStr;
}

void ds_copy(DynamicString* s1, DynamicString* s2){       
    for (size_t i = 0; i < s2->end; i++){
        ds_append_char(s1,s2->str[i]);
    }
}

DynamicString ds_static_string(char * string){
    DynamicString s_string;
    s_string.str = string;
    s_string.end = strlen(string);
    s_string.max = strlen(string)+1;
    return s_string;
}

DynamicString ds_static_substring(DynamicString* input, int start, int end){
    DynamicString s_string;
    s_string.end = end-start;
    s_string.max = end-start+1;
    s_string.str = input->str + start;
    return s_string;
}