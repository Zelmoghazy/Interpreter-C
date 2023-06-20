#include "../include/DynamicString.h"

/**
 * END : String Length
 * MAX : String Capacity 
 */
typedef struct DynamicString{
    char *str;
    int END;
    int MAX;
}DynamicString;

/**
 *  Access Internal string data through those only  
 */
int ds_get_capacity(DynamicString *string){
    return string->END;
}

int ds_get_capacity(DynamicString *string){
    return string->MAX;
}

char* ds_get_char_array(DynamicString *string){
    return string->str;
}

char ds_get_char_at(DynamicString *string, int index){
    if(index > string->END){
        printf("getCharAt: Index Exceeded string length\n");
        return string->str[string->END-2];
    }else{
        return string->str[index];
    }
}

/**
 *  Constructor that takes an initial size 
 */
DynamicString* ds_new(int initialSize){
    DynamicString *string = malloc(sizeof(DynamicString));
    if(string == NULL){
        printf("newString: Allocation failed\n");
        exit(EXIT_FAILURE);
    }
    string->MAX = initialSize+1;
    string->END = 1;
    string->str = calloc(string->MAX,sizeof(char));
    if(string->str == NULL){
        printf("newString: str allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return string;
}

/**
 *  Constructor that takes an initial string 
 */
DynamicString* ds_new_init(char * initialString){
    int size = strlen(initialString);
    DynamicString *string = ds_new(size);
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
    free(string);
}

/**
 *  Print String 
 */
void ds_print(DynamicString *string){
    printf("%s \n",string->str);
}

/**
 *  Expand String when capacity is exceeded.
 */
void ds_expand(DynamicString *string){
    string->MAX *= 2;
    char *Expanded = realloc(string->str,string->MAX*sizeof(char));
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
    string->MAX /= 2;
    char *Shrinked = realloc(string->str,string->MAX*sizeof(char));
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
    if(string->END < string->MAX){
        string->str[string->END-1] = value;
        string->str[string->END] = '\0';
        string->END++;
    }else{
        ds_expand(string);
        ds_append_char(string,value);
    }
}

/**
 *  Concatenate a char array to the string.
 */
void ds_concat(DynamicString *string, char *str2){
    int size = strlen(str2);
    for (int i = 0; i < size; i++){
        if (string->END < string->MAX){
            string->str[string->END - 1] = str2[i];
            string->str[string->END] = '\0';
            string->END++;
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
    char* str1 = s1->str;
    char* str2 = s2->str;

    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

/**
 *  returns a substring as a new string.
 */
DynamicString *ds_substring(DynamicString* string, int start, int end){
    if(start > end){
        printf("Substring: start exceeds end");
        int temp = start;
        start = end;
        end = temp;
    }
    if(end > string->END){
        printf("Substring: end exceeds string length");
        end = string->END;
    }
    DynamicString *newStr = ds_new(end-start+1);
    for (int i = start; i < end; i++){
        ds_append_char(newStr,ds_get_char_at(string,i));
    }
    return newStr;
}

void ds_copy(DynamicString* s1, DynamicString* s2){
    if(s2->MAX > s1->MAX){
        printf("StringCopy: cant copy a larger string to a smaller one.");
        exit(EXIT_FAILURE);
    }        
    for (int i = 0; i < s2->END; i++){
        ds_append_char(s1,s2->str[i]);
    }
}