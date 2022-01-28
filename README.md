# nachtigal
variable based programming language, kind of just an interpreter but not

## installation
currently manual, you can build with make, but you have to copy the lib manually
to /usr/include/

## todo
### general
* [ ] implement test.h to check time(length) to of execution

### lexer
* [ ] fix free memory (somehow free mem after returning)
* [ ] function for switch statments
* [ ] add comparison ops
* [ ] fix all chars for tokens (ie. add all needed)

### parser
* [ ] function(s) to sort when come across " or ( or [

### documentation
* [ ] documentation of each function
* [ ] documentation of how it works

### compile
* [ ] install all header files to system
* [ ] have a default main.c that is compiled and installed to system
* [ ] fix up make file

## notes
* predefined macros in c \
    __DATE__ current date \
    __FILE__ current file name \
    __LINE__ current line number \
    __STDC__ If follows ANSI standard C, then the value is a nonzero integer \
    __TIME__ current time
