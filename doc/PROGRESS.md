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

14 January 2022: Token type bug fixed. Only needed add a break function at the
    end of each switch case. Although unnecessary, printTokens function for loop
    has bug for length of struct array. Sizeof will only return the size of the
    pointer and not the actual amount of structs in the array.

19 January 2022: Can now sort between numbers and letters which will allow for
    math and all as well. I plan on trying to make a multithreaded algorithem
    that will shorten the time to process the text file into tokens. I will also
    record times before and after. I also made a union in the struct that allows
    the storage of either a char or long int depending on the var type.

20 January 2022: Three major obsitcles: multithreadeding the lexer, parser,
    interpreter, writing an abstract syntax tree (AST), and comign up with a
    viable syntax for the input language.

20 January 2022: Began implementing multiple threads but have been running into
    bugs and issues as I am not familiar with this type of "parallel
    programming".

27 January 2022: Rename project to nachtigal just because, idk. Moved everything
    to one file and decided to try and multi thread when I have written the
    parser and other elements because trying to multithread the lexer alone was
    just to much of a headache. Did some non coding work and tried to create a
    drawing of the abstract data tree so that I could better understand what
    needed to be done. I was also thinking if it is "cheating" to use just use
    function like printf written in stdio.h in my langauge. I talked to Mr.
    Gorman and he said that it was not and that it was "thinking smart."

3 February 2022: Sort function is working and everything is working so I can put
    full names into char* variable and store that in a structure but one problem
    is that as I loop through tokens and the Name *head; I can not go back. I
    need to find a way to cycle back to the head. I think I may have to change
    something in the sort function so that it goes through the head first but
    the value defined in head in the parser function is still kept in it's
    original state. Maybe like having something like a tmp var that is always
    equal to a nameLink(Name).

8 February 2022: Problem so far is printing the char pointer gotten from the
    sort function. Turns out that the going back through the list did not have
    to be done. Printing normally assigned names to a node works but using the
    sort function and entering a char pointer into the addName function returned
    from the sort function is not printable (only prints blank space). Type is
    correct though. Basically sort works but I can't print out char *name.

16 February 2022: Orginizing and working through some problems so that I can get
    back to full time work.
