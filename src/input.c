#include <string.h>
#include <stdlib.h>

#include "global_data.h"
#include "converters.h"
#include "input.h"

#define COMMAND_LIST_LENGTH 7

static int test()
{
    int i = 1;
    struct statement *statement;
    FILE* testFile;
    double awnser = 0.0;
    char input[BUFFER_SIZE];
    
    testFile = fopen("testCases.txt", "r");
    if(testFile == NULL){
        puts("Failed opening file");
        return 1;
    }
    
    while( fgetc(testFile) != EOF ){
        fseek(testFile, -1l, SEEK_CUR);
        fgets(input, BUFFER_SIZE, testFile),
        fscanf(testFile, "%lf\n\n", &awnser);
        
        statement = stringToStatement(input, BUFFER_SIZE);
        
        if(statement == NULL){
            printf("Test[%d] failed, error\n", i);
            errorHandling();
        }
        else{
            if( awnser == (ANS = calculate(statement) ) ){
                    printf("Test[%d] succesful\n", i);
            }else{
                printf("Test[%d] failed, expected %lf, got %lf\n", i, awnser, ANS);
            }
        }
        i += 1;
    }
    putchar('\n');//Newline character for the looks
    return 0;
}


static void executeCommand(char* input)
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
static void formatString(char* input)
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


char* readData(void)
{   
    char *input = NULL;
    
    while(input == NULL)
    {
        input = calloc(BUFFER_SIZE, BUFFER_SIZE);
        if(input == NULL){
            puts("Malloc failed, exiting");
            return NULL;
        }
        
        formatString(input);
        
    //     exit command
        if(input[0] == 'q' || input[0] == '\n')
        {
            puts("Quitting\n");
            free(input);
            return NULL;
        }
        if(input[0] == '#')
        {
            executeCommand(input);
            free(input);
            input = NULL;//Sets input to NULL so the loop continues untill a statement is given as input.
        }
    }
    
    return input;
}
