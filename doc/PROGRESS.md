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

18 February 2022: Two major obsticles. The first one is the abstact syntax tree.
    Currently it is more an abstract syntax "list" rather than tree and that
    needs to be fixed but I don't yet know how. Secondly is the problem of clean
    code and making the project even with only 300 lines more readable and
    quicker to execute. With the AST still in progress and one more big peice to
    code plus trying to multi thread the lexer and parser, the code base will
    get a little muddy and slow and so I need to also focus on optimizing the
    code for both the user and any coder. I need to use a name scheme and split
    up the lexer and pareser and other peices maybe?

22 February 2022: addDefinition works now with the sort function. Will need to
    create a function to convert string to double. What I want to do next is
    rebuild the ast. I think it will still be linear but name and definition are
    basically the same now. Also want a result thing in name so that if I am
    adding numbers or strings, they will be stored in a result variable in a
    name node. There will be only one name node per "idk what" and then alot of
    definitions to each name node. Name nodes will be linear for now.

23 February 2022: One problem is that I want to be able to have infinate
    definition children to each name node, but I don't know if that is possible.
    Maybe I make the def child a linked list that is ordered by order of
    operations. ie. Go through a the list between [] and check for * then / then
    - then + and if none it just sets var equal to name.

8 March 2022: Moving on, will just change numbers when time comes. Need to now
    restructure AST and be able to loop through everything.

9 March 2022: I tried moving everything into multiple files (lexer.h, parser.h,
    parSort.h) but it wasn't working well and I think im just going to stick to
    a sort of suckless/kai hendry method of sticking everything into one file
    even though that is like the #1 rule when first starting a project <use
    multiple files>

28 March 2022: Picking up work again. Things need to do: go through entire file
    and do waht code says, everything done before was just for sorting through
    everything so that this would be easier.

30 March 2022: The difficult part now will be having to deal for every instance
    anything that can happen when going through each defintion. I will also want
    to create a secondary std.c file that will hold basic functions like print()
    and other things.

4 April 2022: The nested for loops are geting very complicated in the run
    function but we will have to make do. Having prooblem getting double values
    into the art structure. This is the last step before having something
    functional but it is proving to be very difficult. I might attempt a quick
    "rewrite" of the function.

5 April 2022: I got the first number that appears in the file into the
    Arithmetic struct but can't seem to get the rest of the numbers in
    'list.nagl' into the next nodes of the struct. What I need to do next is fix
    it so that all the numbers are included and then I need to be able to add
    the operator to it as well.

9 April 2022: The Arithmetic struct is basically just the stack at this point
    for the entire language. I will need to implement a sort of sor stack
    function into the code for order of operations and all. Print statement
    still needs to be made. And a way to read the beginning/names of each statement.

12 April 2022: Need to be able add to sub struct within struct that are both
    esentially linked lists. Maybe I make them doubly linke lists? for extra
    functionality? idk yet but definitely on something there.

13 April 2022: The run function is basically just a glorfied Definition sort function.
    Need to be able to also sort through Name as well.
