#include <stdio.h>
#include <stdlib.h>

#include "global_data.h"
#include "converters.h"
#include "input.h"

void calc_input(char* input)
{
	struct statement *statement;
	statement = stringToStatement(input, BUFFER_SIZE);
	if( statement != NULL ){
		printf("\t%lf\n", (ANS = calculate(statement)) );
	}
}


int main(int argc, char **argv)
{
    char *input = NULL;
    
    ANS = 0;
    DEGREES = 1;

    if( argc <= 1 ){
		puts("\nCurrently this program suffers from floating point inaccuracy.\ntan(90) is not to be trusted\n");
		while( (input = readData()) != NULL )
		{
			calc_input(input);
			free(input);
		}
	}else{
		formatString(argv[1]);
		calc_input(argv[1]);
	}
    
    return 0;
}
