# Data Sorting and Processing Library in C
currently in development

## installation
currently manual, you can build with make, but you have to copy the lib manually
to /usr/include/

## todo
### lexer
* [X] return Token array from lexer function
* [ ] fix free memory (somehow free mem after returning)
* [ ] convert enum to string some how
* [ ] print enum in printTokens function
* [ ] Type defaults only to IDEN for some reason which is defined in the default
      switch

### documentation
* [ ] documentation of each function
* [ ] documentation of how it works

## notes
* predefined macros in c
    __DATE__ current date
    __FILE__ current file name
    __LINE__ current line number
    __STDC__ If follows ANSI standard C, then the value is a nonzero integer
    __TIME__ current time
