#include <stdio.h>
#include <stdlib.h>

#include "global_data.h"
#include "converters.h"
#include "input.h"

void errorHandling()
{
    if(ERROR_CODE == 1){
        exit(-1);
    }
}

int main()
{
    char *input;
    struct statement *statement;
    puts("\nCurrently this program suffers from floating point inaccuracy.\ntan(90) is not to be trusted\n");
    
    ERROR_CODE = 0;
    ANS = 0;
    DEGREES = 1;
    while(readData(&input) == 0)
    {   
        statement = stringToStatement(input, BUFFER_SIZE);
        if(statement == NULL){
            errorHandling();
        }else{
            printf("\t%lf\n", ANS = calculate(statement) );
        }
        free(input);
    }
    free(input);
//     TODO: something like a readline function but not abysmally slow so that arrow keys can be used
//     TODO: Use a function pointer array instead of a switch statement
//     TODO: Fix multiple decimal points not working properly
    return 0;
}
