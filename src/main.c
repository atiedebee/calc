#include <stdlib.h>

#include "global_data.h"
#include "converters.h"
#include "input.h"

void errorHandling(void)
{
    if(ERROR_CODE == 1){
        exit(-1);
    }
    ERROR_CODE = 0;
}

int main(void)
{
    char *input;
    struct statement *statement;
    
    
    ERROR_CODE = 0;
    ANS = 0;
    DEGREES = 1;
    while( (input = readData()) != NULL)
    {
        statement = stringToStatement(input, BUFFER_SIZE);
        if(statement == NULL){
            errorHandling();
        }else{
            printf("\t%lf\n", ANS = calculate(statement) );
        }
        free(input);
    }
    
    return 0;
}
