# calc
A calculator that suffers from floating precision.
This calculator suffers from floating point precision and isn't much more than a fun project. I recommend against using it as a calculator. If you have feedback I would love to hear it so I can improve. Makefile uses GCC with a recursive call to itself with the -j4 flag. The calculator is currently 100% terminal based.

# how does it work? (from a user perspective)
Run the executable in the terminal, and give it some things to calculate.

Functions like sine (sin) and square root (sqrt) need their arguments in brackets, otherwise the program will throw an error.
> sin(8+2) is correct.
> 
> sin 8 will throw an error.

There's also some commands
> #deg / #degrees   -   switches to degrees

> #rad / #radiants  -   switches to radiants

> #help             -   shows these commands

> #test             -   runs tests from testCases.txt

# How does it work? (from a code perspective)
Input is first saved as a string, and later formatted to exclude any spaces to make parsing it easier (as seen in input.c).

After that the string is passed to the lexical analyzer, which reads the string and converts it to a structure array to make calculating in the right order easier. The structure is as follows:
```
struct statement{
    double number;
    char operator;
    
    struct statement* statement;
    int type;
    
    unsigned int isNegative : 1;
};
```
This structure is saved as an array.

*number* is used to store... the number.

*operator* is the operation that's used on the number before it (the one in the same struct) and the one after it (which is in the index after the first one).

_*statement_ is a pointer that's used to store brackets. If you have something like 2*(2+1) it will store the (2+1) in a new structure array which this pointer points to.

*type* is used for things like the square root, sine and cosine functions. In the calculator function it will perform that operation on the number that's put in between the brackets.

*isNegative* speaks for itself. It's used to make things like brackets negative.

A _'\n'_ character is stored in the last part of the structure array to indicate that that's where the statement ends.
