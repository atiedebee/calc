#include <string.h>
#include <stdlib.h>

#include "global_data.h"
#include "converters.h"

#define COMMAND_LIST_LENGTH 7
#define NUM_TESTS 12

void test()
{
    char *input[NUM_TESTS] = {
        "2+(2+2)(2-2)\n\0",
        "2(2+2)(2-2)\n\0",
        "2(2+2)+(2-2)\n\0",
        "2((2+2)+(2-2))\n\0",
        "2((2+2)+(2-2)+2)\n\0",
        "2+((2+2)+(2-2)+2)\n\0",
        "2+2^(2+2^2)\n\0",
        "2+((2+2)*2)(3-(8+2))\n\0",
        "ans+54+sin(90)*5\n\0",
        "sqrt(2^4)*2\n\0",
        "+1-+2\n\0",
        "2 - - 1\n\0"
    };
    double awnsers[NUM_TESTS] = {
        2.0, 0.0, 8.0, 8.0, 12.0, 8.0, 66.0, -54.0, 5.0, 8.0, -1.0, 3.0
    };
    int i;
    struct statement *statement;
    
    LOGS = fopen(".atieCalcLogs.txt", "w+");
    ANS = 0;
    for( i = 0; i < NUM_TESTS; i++){
        fprintf(LOGS, "\n\n-Now parsing %s", input[i]);
        statement = stringToStatement(input[i], BUFFER_SIZE);
        
        if(statement == NULL){
            printf("Test[%d] failed, error\n", i);
            errorHandling();
        }
        else{
            if( awnsers[i] == (ANS = calculate(statement) ) )
                    printf("Test[%d] succesful\n", i);
            else
                printf("Test[%d] failed, expected %lf, got %lf\n", i, awnsers[i], ANS);                
        }
    }   
}


void executeCommand(char* input)
{
    int i = 0;
    char command[16];
    const char commandList[ COMMAND_LIST_LENGTH ][16] = {
        "radiants",
        "rad",
        "degrees",
        "deg",
        "help",
        "test",
        "\n" //newline character so we can read that memory without a buffer overflow. Yes this is needed
    };
    
    sscanf(input, "#%s", command);
//     sscanf to be possibly replaced with something safer
    while(strncmp(commandList[i], command, 16) != 0  &&  i < COMMAND_LIST_LENGTH)
    { i++; }
    
    switch(i)
    {
        case 0:
        case 1:
            DEGREES = 0;
            puts("\tSwitched to Radians\n");
            break;
        case 2:
        case 3:
            DEGREES = 1;
            puts("\tSwitched to Degrees\n");
            break;
        default:
        case 4:
            for(i = 0; i < COMMAND_LIST_LENGTH; i++){
                printf("\t%s\n", commandList[i]); 
            }
            break;
        case 5:
            test();
            break;
    }
}


//     This code is to remove inconsistensies with the input like capital letters.
void formatString(char* input)
{
    int i, j = 0;
    char inputCopy[512];
    
    fgets(inputCopy, BUFFER_SIZE, stdin);
    fflush(stdin);
    
    
    for(i = 0; inputCopy[i] != '\0'; i++)
    {
        if(inputCopy[i] == ','){
            inputCopy[i] = '.';
        }
        
        if(inputCopy[i] >= 'A' && inputCopy[i] <= 'Z'){
            inputCopy[i] += 32;
        }
        
        if(inputCopy[i] != ' '){
            input[j] = inputCopy[i];
            j++;
        }
    }
    
    input[BUFFER_SIZE-1] = '\0';
    input[BUFFER_SIZE-2] = '\n';
}


int readData(char **input)
{   
REREAD_DATA:
    *input = calloc(BUFFER_SIZE, BUFFER_SIZE);
    
    formatString(*input);
    
//     exit command
    if(*input[0] == 'q' || *input[0] == '\n')
    {
        puts("Quitting\n");
        return 1;
    }
    if(*input[0] == '#')
    {
        executeCommand(*input);
        free(*input);
        *input = NULL;
        goto REREAD_DATA; //Yes I'm using a goto, currently don't have anything better. Calling the function recursively could eventually cause a stackoverflow
    }
    
    return 0;
}
