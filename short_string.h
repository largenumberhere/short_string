#include <stddef.h>
#include <stdint.h>

typedef struct  {
	size_t length; //Length does not include null-termiator
	size_t capacity; //Must be at least one greater than length for null-terminator
	union
	{
		char* string_as_ptr; //when this overflows, this memory is used for a pointer instead.
		char string_as_val[8]; //The default store of data
	};
	
} short_string_t;

short_string_t short_string_new(void);
void short_string_push_char(short_string_t* short_string, char value);
void short_string_free(short_string_t* short_string);
char* short_string_ptr(short_string_t* sstring);
void short_string_print(short_string_t* sstring);
void short_string_push_raw_string(short_string_t* sstring, char* string, size_t string_len);