REM Run this in a visual studio 2022 dev prompt, in this folder for best results
@echo off
cd build
cl -o tests.exe ../tests.c ../short_string.c -Lshort_string.h
tests.exe
cd ..