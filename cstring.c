#include "cstring.h"

#include "string.h"

#include "FreeRTOS.h"

#define malloc pvPortMalloc
#define free vPortFree

static const char terminal_char = '\0';
static const size_t terminal_char_size = sizeof(terminal_char);

static void string_grow_capacity(string_t *string, size_t size) {
    if (string->capacity < (size + 1)) {
        while (string->capacity < (size + 1)) string->capacity *= 2;
        void *data = malloc(string->capacity);
        memcpy(data, string->cstr, string->size);
        free(string->cstr);
        string->cstr = data;
    }
}

inline static void string_add_terminal_char(string_t *string) {
    string->cstr[string->size] = terminal_char;
}

string_t *string_new() {
    string_t *string = malloc(sizeof(*string));
    
    string->capacity = 0;
    string->size = 0;
    string->cstr = NULL;
    
    return string;
}

string_t *string_new_from_cstr(const char *cstr) {
    
    string_t *string = malloc(sizeof(*string));
    
    string->size = strlen(cstr);
    string->capacity = string->size + terminal_char_size;
    string->cstr = malloc(string->capacity);
    memcpy(string->cstr, cstr, string->capacity);
    
    return string;
}

void string_free(string_t *string) {
    free(string->cstr);
    free(string);
}

int string_index_of_char_from_count(string_t *string, char ch, int start, int count) {
    for (int i = start, found = 0; i < string->size; ++i) {
        if (string->cstr[i] == ch) {
            if (++found == count) return i;
        } else {
            found = 0;
        }
    }
    
    return -1;
}

int string_index_of_chars_from_count(string_t *string, const char * chs, size_t size, int start, int count) {
    for (int i = start, found = 0; i < string->size;) {
        if (!memcmp(chs, string->cstr + i, size)) {
            if (++found == count) return i;
            i += size;
        } else {
             ++i;
            found = 0;
        }
    }
    
    return -1;
}

int string_index_of_cstr_from_count(string_t *string, const char *cstr, int start, int count) {
    return string_index_of_chars_from_count(string, cstr, strlen(cstr), start, count);
}

int string_index_of_from_count(string_t *string, const string_t *other, int start, int count) {
    return string_index_of_cstr_from_count(string, other->cstr, start, count);
}

void string_insert_chars(string_t *string, int index, const char *chars, size_t size) {
    string_grow_capacity(string, string->size + size);
    memmove(string->cstr + index + size, string->cstr + index, string->size - index);
    memcpy(string->cstr + index, chars, size);
    string->size += size;
    string_add_terminal_char(string);
}

void string_insert_char(string_t *string, int index, char ch) {
    string_insert_chars(string, index, &ch, sizeof(ch));
}

void string_insert_cstr(string_t *string, int index, const char *cstr) {
    string_insert_chars(string, index, cstr, strlen(cstr));
}

void string_insert(string_t *string, int index, string_t *other) {
    string_insert_chars(string, index, other->cstr, other->size);
}

void string_clear(string_t *string) {
    string->size = 0;
    string_add_terminal_char(string);
}

void string_push_back_char(string_t *string, char ch) {
    string_insert_char(string, string->size, ch);
}

void string_push_back_chars(string_t *string, const char *chs, size_t size) {
    string_insert_chars(string, string->size, chs, size);
}

void string_push_back(string_t *string, string_t *other) {
    string_insert(string, string->size, other);
}

void string_push_front_char(string_t *string, char ch) {
    string_insert_char(string, 0, ch);
}

void string_push_front_chars(string_t *string, const char *chs, size_t size) {
    string_insert_chars(string, 0, chs, size);
}

void string_push_front(string_t *string, string_t *other) {
    string_insert(string, 0, other);
}

int string_is_empty(string_t *string) {
    return string->size == 0;
}
