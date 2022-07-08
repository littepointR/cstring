#ifndef CSTRING_H
#define CSTRING_H

#include "stdlib.h"

typedef struct {
    char * cstr;
    size_t size;
    size_t capacity;
} string_t;

#define STRING_LITERAL(_cstr) { \
    .cstr = _cstr,              \
    .capacity = 0,              \
    .size = sizeof(_cstr) - 1,  \
}

string_t *string_new();
string_t *string_new_from_cstr(const char *cstr);
void      string_free(string_t *string);
int       string_index_of_char_from_count(string_t *string, char ch, int start, int count);
int       string_index_of_chars_from_count(string_t *string, const char * chs, size_t size, int start, int count); 
int       string_index_of_cstr_from_count(string_t *string, const char *cstr, int start, int count);
int       string_index_of_from_count(string_t *string, const string_t *other, int start, int count);
void      string_insert_chars(string_t *string, int index, const char *chars, size_t size);
void      string_insert_char(string_t *string, int index, char ch);
void      string_insert_cstr(string_t *string, int index, const char *cstr);
void      string_insert(string_t *string, int index, string_t *other);
void      string_clear(string_t *string);
void      string_push_back_char(string_t *string, char ch);
void      string_push_back_chars(string_t *string, const char *chs, size_t size);
void      string_push_back(string_t *string, string_t *other);
void      string_push_front_char(string_t *string, char ch);
void      string_push_front_chars(string_t *string, const char *chs, size_t size);
void      string_push_front(string_t *string, string_t *other);
int       string_is_empty(string_t *string);

#endif //CSTRING_H
