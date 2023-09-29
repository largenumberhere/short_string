test:
	clear
	clang -o ./build/tests tests.c -Lshort_string short_string.c 
	./build/tests
