# DataArt Summer practice 2021 - CaseSwitcher

## Description
Input file contains constant-size (4095B including null-termitation character) lines of letters add digits.
The program swap case for letters and add one to each digit except 9 which turns into 0. Output lines are saved in output file.

## Features
* Removed copy constructors
* Removed line handler
* If-statements replaced by switching map
* Working with virtual memory wrapped in mmap

## Build the project
`g++ -std=c++17 -Wall -Wextra -O3 -I ".\sources" -c ".\sources\main.cpp" ".\sources\mman_lib\mman.cpp" && g++ ".\main.o" ".\mman.o" -o ".\CppPerfomanceTask.exe"`

## Tests
8 Kbyte
```
Total switching time: 0ms
All execution time: 2ms
```
64 Mbyte
```
Total switching time: 133ms
All execution time: 169ms
```
512 Mbyte
```
Total switching time: 911ms
All execution time: 1039ms
```
