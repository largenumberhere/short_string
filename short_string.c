//#include "short_string.h"
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "short_string.h"
#include <ctype.h>

const int INITIAL_CAPACITY = 8;

// Create a short string with the contents stored on the stack. 
// When length goes above 7, it promotes to storing the string on the heap
// For 64-bit systems ONLY
short_string_t short_string_new(void) {
	// if(sizeof(char*)!=INITIAL_CAPACITY) {
	// 	printf("Only supported on 64-bit systems");
	// 	exit(-1);
	// }
	
	short_string_t ssstring;
	ssstring.capacity = INITIAL_CAPACITY;
	ssstring.length = 0;
	ssstring.string_as_val[0] = '\0';

	return ssstring;
}

int nearest_multiple_of_8(int number){
	//printf("input %i\n", number);
	int i = 8;
	while (i < number)
	{
		i*=2;
	}

	//printf("outputting %i\n", i);

	return i;
}

// Reallocate if needed to hold at least this many chars exculding null teminator. Returns a pointer to start of the string. 
char* short_string_realloc(short_string_t* sstring, int min_extra_cap_exc_null){
	// Capacity should be exacty 8 or greater, any other value indicates it has been freed or has been corrupted
	assert(sstring->capacity>= INITIAL_CAPACITY);

	// new characters + null character + current length  
	int bytes_required = min_extra_cap_exc_null + sstring->length;

	// sstring's string is stack allocated	
	if (sstring->capacity == INITIAL_CAPACITY) {
		// we have enough space on stack
		if(bytes_required < INITIAL_CAPACITY) {
			//printf("val '%c'", sstring->string_as_val[0]);
			
			return (char*)& sstring->string_as_val;
		}

		// We need to move to heap

		// Allocate
		int nearest_required = nearest_multiple_of_8(bytes_required+1);
		char* ptr = malloc(nearest_required);
		if (ptr == NULL) {
			printf("Failed to allocate %i for short_string_realloc type1", nearest_required);
			exit(-1);
		}
		

		//printf("Reallocated to %i\n", nearest_required);


		//Copy data to heap
		for(int i = 0; i < INITIAL_CAPACITY; i++) {
			//printf("copying to ptr %c\n", sstring->string_as_val[i]);
			ptr[i] = sstring->string_as_val[i];
		}
		
		//Update short_string
		sstring->capacity = nearest_required;
		sstring->string_as_ptr = ptr;
		
		return sstring->string_as_ptr;

	}

	//sstring's string is heap allocated
	else{
		
		//We have enough space
		if (bytes_required < sstring->capacity ){
			return sstring->string_as_ptr;
		}

		//Reallocation is required
		else{
			int nearest_required = nearest_multiple_of_8(bytes_required+1);
		  	void* ptr = realloc(sstring->string_as_ptr, nearest_required);
			if (ptr == NULL) {
				printf("Failed to allocate %i for short_string_realloc type2", bytes_required);
				exit(-1);
			}

			//Update short_string
			sstring->capacity = nearest_required;
			sstring->string_as_ptr = (char*)ptr;
			return sstring->string_as_ptr;
		}
	}
}

// Get a null_terminated char* pointer to read from. Do not modify it. It may be stack or heap allocated. 
//Never free this manualy, if you are done with the stiring free it with `short_string_free`.
char* short_string_ptr(short_string_t* sstring){
	if (sstring->capacity == INITIAL_CAPACITY){
		return sstring->string_as_val;
	}

	return sstring->string_as_ptr;
}


// Push a single character onto the interal string
void short_string_push_char(short_string_t* sstring, char value) {
	char* sstring_contents = short_string_realloc(sstring,1);
	sstring_contents[sstring->length] = value;
	sstring_contents[sstring->length+1] = '\0';

	sstring->length+=1;
}

// Copy the contents of a char array from 0 until string_len. 
void short_string_push_raw_string(short_string_t* sstring, char* string, size_t string_len) {
	char* contents = short_string_realloc(sstring, string_len);
	for (int offset = 0; offset <= string_len; offset++) {
		contents[sstring->length+offset] = string[offset];
	}
	contents[sstring->length +string_len ] = '\0';
	
	sstring->length += string_len;
}

// Free any allocation held by the string and set all to 0
void short_string_free(short_string_t* sstring){
	if(sstring->capacity == INITIAL_CAPACITY) {
		//Eveyrthing is on the stack, there is nothing to free
		return;	
	}

	free(sstring->string_as_ptr);
	sstring->string_as_ptr = NULL;
	sstring->capacity = 0;
	sstring->length = 0;

}

// Print the contents of a short_string. 
// Assumes ssrtirng is valid in that.
//  - If capacity is over 8, sstring->string_as_ptr points to an allocated char array with at least 0 to sstring->length valid readable characters
//  - If capacity is under 8, sstring->string_as_val is a valid array of characters with at least 0 to `string->length` readable.
//  - Each character is currently expected to be ascii
void short_string_print(short_string_t* sstring){
	printf("short_string_t {\n");
	printf("\tcapacity: %zu\n",sstring->capacity);
	printf("\tlength: %zu\n", sstring->length);
	if (sstring->capacity == INITIAL_CAPACITY) {
		printf("\tstring_as_val: ");
		for (int i =0; i < sstring->length; i++){
			printf("%c",sstring->string_as_val[i]);
		}
		printf("\n");
	}
	else{
		printf("\tstring_as_ptr (deref): ");
		for (int i = 0; i < sstring->length; i++) {
			if(!isprint(sstring->string_as_ptr[i])){
				printf("!");
			}
			else{
				printf("%c", sstring->string_as_ptr[i]);
			}
		}

		printf("\n}\n");
	}
}