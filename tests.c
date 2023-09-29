#include <stdio.h>
#include "short_string.h"
#include <assert.h>
#include <string.h>


int push_char(void) {
	short_string_t new = short_string_new();
	short_string_push_char(&new, '1');
	short_string_push_char(&new, '2');
	short_string_push_char(&new, '3');
	short_string_push_char(&new, '4');
	assert( strcmp(short_string_ptr(&new), "1234") == 0);
	short_string_push_char(&new, '5');
	short_string_push_char(&new, '6');
	short_string_push_char(&new, '7');
	short_string_push_char(&new, '8');
	short_string_push_char(&new, '9');	
	short_string_push_char(&new, 'A');	
	short_string_push_char(&new, 'B');
	short_string_push_char(&new, 'C');	
	short_string_push_char(&new, 'D');	
	short_string_push_char(&new, 'E');	
	short_string_push_char(&new, 'F');	
	short_string_push_char(&new, '0');
	short_string_push_char(&new, '1');
	assert(strcmp(short_string_ptr(&new), "123456789ABCDEF01") == 0);

	short_string_push_char(&new, '2');
	short_string_push_char(&new, '3');
	short_string_push_char(&new, '4');
	short_string_push_char(&new, '5');
	short_string_push_char(&new, '6');
	short_string_push_char(&new, '7');
	short_string_push_char(&new, '8');
	short_string_push_char(&new, '9');	
	short_string_push_char(&new, 'A');	
	short_string_push_char(&new, 'B');
	short_string_push_char(&new, 'C');	
	short_string_push_char(&new, 'D');	
	short_string_push_char(&new, 'E');	
	short_string_push_char(&new, 'F');	
	short_string_push_char(&new, '0');
	short_string_push_char(&new, '1');
	//short_string_print(&new);
	assert(strcmp(short_string_ptr(&new), "123456789ABCDEF0123456789ABCDEF01") == 0);

	short_string_free(&new);

	for (int i = 0; i < 129; i++) {
		short_string_t sstring = short_string_new();
		for(int j = 0; j < 129; j++) {
			short_string_push_char(&sstring, 'a');
			assert(strlen(short_string_ptr(&sstring)) == j+1);
		}

		short_string_free(&sstring);
	}

	printf("Push char tests succeeded\n");

	return 0;
}

int push_string_raw(void) {
	for(int i = 0; i < 128; i ++) {
		for (int j =0; j < i; j++) {
			char a[130];
			for (int k = 0; k < 130; k++){
				a[k] = 'A';
			}
			a[129] = '\0';

			short_string_t sstring = short_string_new();
			short_string_push_raw_string(&sstring, a, j);
			//short_string_print(&sstring);
		 	assert(strlen(short_string_ptr(&sstring)) == j);
			assert(sstring.capacity > strlen(short_string_ptr(&sstring)));
			short_string_free(&sstring);
		}

	}

	printf("Push string_raw tests succeeded\n");


	return 0;
}

int short_string() {
	for(int i = 0; i < 128; i++){
		short_string_t ssrting = short_string_new();
		short_string_push_char(&ssrting, '1');
		short_string_push_char(&ssrting, '2');
		short_string_push_char(&ssrting, '3');
		short_string_push_char(&ssrting, '4');

		short_string_free(&ssrting);
	}

	return 0;
}


int main() {
	push_char();
	push_string_raw();
	short_string();
}