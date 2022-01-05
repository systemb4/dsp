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
