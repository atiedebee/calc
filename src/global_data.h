#include <stdio.h> //Yes, this include is needed because the header contains the FILE type.

#define     BUFFER_SIZE 256
#define     VERSION     "0.1"


extern double ANS;
extern unsigned int DEGREES;

struct statement{
    double number;
    char operator;
    
    struct statement* statement;
    int type;
    
    unsigned int isNegative : 1;
//     a \n character in char operator has been chosen to show the end of a statement array.
//     It doesn't have any real reason other than that it shouldn't be there under normal circumstances.
//     Type is the type of function
};

