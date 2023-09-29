# Short_string
A proof of concept for a hybrid allocated/stack string, optimized for insertions of 7 or fewer characters.

## Details
The design centres around this single struct.
```c
typedef struct  {
	size_t length; //Length does not include null-termiator
	size_t capacity; //Must be at least one greater than length for null-terminator
	union
	{
		char* string_as_ptr; //when this overflows, this memory is used for a pointer instead.
		char string_as_val[8]; //The default store of data
	};
	
} short_string_t;
```
Allocation on the heap only occurs after this.The memory footprint is low, taking advantage of C's untaged unions.
The design involves 2 important  fields `string_as_ptr` and `string_as_val` that use the same 8 bytes of memory. 
`string_as_val` interprets the memory as 8 `chars`. `string_as_ptr` interprets the memory as a pointer to a heap-allocated
`char*` pointer. Once the limit of 7 characters (+ 1 hidden null terminator) is no longer enough, 
16 bytes is allocated on the heap and the char array is copied there. 
This limits heap allocations and memory footprint for small strings, 
whilst still offering the adaptability of heap allocated strings. 
This particular implementation was chosen to be limited to 64-bit systems to reduce complexity, 
however the underlying principle could be adapted to architectures with larger or smaller pointer sizes.

## Build
All build artifacts including executables are stored in `./build`

#### Linux
On linux systems or Windows subsystem for linux, gnu-make can be used to build the files and run the tests.
Clang among other libraries such as LLVM may be required. Gnu-make in normally installed by default.
To build and run the tests, inside the root folder run `make`

#### Windows
On windows, you must have visual studio 2022 installed with the `Desktop development with C++` Workload installed. 
Open up `Developer Command Prompt for VS 2022Developer Command Prompt for VS 2022` 
(It is required for its environment variables) and `cd` into this project's root folder. 
Inside the command prompt, run the `build-win.bat` script. This compiles the project and runs the tests.