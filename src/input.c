#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "global_data.h"
#include "converters.h"
#include "charChecks.h"
#include "input.h"

#define COMMAND_LIST_LENGTH 7

void formatString(char* input);

static int test(void)
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
		formatString(input);
        
		fscanf(testFile, "%lf\n\n", &awnser);
		
        statement = stringToStatement(input, BUFFER_SIZE);
        
        if(statement == NULL){
            printf("Test[%d] failed, error\n", i);
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
void formatString(char* input)
{
    int i, j = 0;
    char inputCopy[BUFFER_SIZE] = {0};
    
	strncpy(inputCopy, input, BUFFER_SIZE);
	memset(input, 0, sizeof(char) * BUFFER_SIZE);//initialize the string with 0
	
    for(i = 0, j = 0; inputCopy[i] != '\0'; i++)
    {
        if( inputCopy[i] == ',' ){
            inputCopy[i] = '.';
        }
        
        if( inputCopy[i] == '*' && inputCopy[i+1] == '*' ){
			inputCopy[++i] = '^';
		}
        
        
        if( inputCopy[i] >= 'A' && inputCopy[i] <= 'Z' ){
            inputCopy[i] += 32;
        }
        
        if( !isWhitespace(inputCopy[i]) ){
            input[j] = inputCopy[i];
			
			j++;
        }
    }
    input[j] = '\n';
    
    input[BUFFER_SIZE-1] = '\0';
    input[BUFFER_SIZE-2] = '\n';
}



char* readData(void)
{   
    char *input = NULL;

    while( input == NULL )
    {
        input = calloc(BUFFER_SIZE, BUFFER_SIZE);
        if(input == NULL){
            puts("Malloc failed, exiting");
            return NULL;
        }
		fgets(input, BUFFER_SIZE, stdin);
        
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
