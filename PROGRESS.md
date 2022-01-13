## progress calender
28 Dec 2021: dsp.h included in main.c compiles, but does not give output. Output
    is just gibbereish. Problem lies in the transfer function. The transfer
    function uses the insertEnd function which takes a head parameter as a
    pointer. The transfer function also takes in a head parameter and uses that in
    the call of the insertEnd function within the function causing the error.

4 January 2022: Code compiles without warning or error, but when running it does
    print anything. I do not think it is a problem with the printList
    (src/dsp.h) function, but instead a problem with creating the linked list
    and calling the insertEnd (src/dsp.h) function within the transfer
    (src/dsp.h) function.

5 January 2022: Transfer function fixed, it was only a problem of giving place
    in memory instead of actual value in the head parameter. Cleaned up
    everything and work on search will begin.

10 January 2022: BIG CHANGES, created new struct that takes two linked lists and
    a link to it's own node type. This will take in a name/definition style
    language ending with semicolons. File types end in .dsp Functions added like
    createNode (src/dsp.h) and printNode (src/dsp.h) and others added. Goal
    right now is to create own data processing language syntax.

12 January 2022: I may be pivoting a little bit. Instead of putting the entire
    file into a linked list, I will be writing a lexer that takes in the entire file
    and defines each character with its own type, place in file, and value. The
    reason I am doing this is so that I could maybe end up writing my own
    programming language.

13 January 2022: The lexer kind of works, but needs some improvment. The lexer
    (src/lexer.h) function needs to be able to return a Token array. The
    printArray method and in general use the enum value in the Token struct
    needs to be able to convert to a string so that it's word value can be read
    and printed although this will not be important for the parser.
