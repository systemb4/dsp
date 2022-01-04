# Data Sorting and Processing Library in C
currently in development

## installation
currently manual, you can build with make, but you have to copy the lib manually
to /usr/include/

## issues
* transferring file to linked list

## todo
* sort by increaseing/decreasing number if number list
* sort by alphabetical order
* search and replace within file
* be able to choose a data structure based on the pattern of the input file
* add tree structure that links linked lists
* change to a lib and be able to make as many ll's as user wants with different
  head names
* search should take in word; check for value with spaces or : or , on either side
    if value is word return what it is : to or the opposite
* Number of elements
* number of definitions
* documentation of each function
* documentation of how it works
* Makefile to install lib to system


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
