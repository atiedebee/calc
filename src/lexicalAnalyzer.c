#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <string.h>

#include "global_data.h"
#include "charChecks.h"
#include "converters.h"

struct statement* stringToStatement(char* input, int MALLOC_SIZE);

static double str_to_num(char* str, int* curChar)
{
    double number;
    int hasDecimal = 0;
    sscanf(&str[*curChar], "%lf", &number);
//     possibly change sscanf into a safer option if needed
//     move curChar to the right while there is a number
    while( isNumber(str[*curChar]) == 1  ||  str[*curChar] == '.' )
    {
        if(str[*curChar] == '.' ){
            hasDecimal += 1;
        }
        *curChar += 1;
    }
    if(hasDecimal > 1){
        puts("Too many decimal points");
		return NAN;
    }
    
    return number;
}


static struct statement* movePastBrackets(char* input, int* curChar)
{
    int startFunc = *curChar + 1; //Makes sure the first opening bracket won't be read when parsing the new string
    int size, bracketCount = 1;
    struct statement* statement;
    
    *curChar += 1;
    while(bracketCount > 0 && input[*curChar] != '\0')
    {
        switch( input[*curChar] )
        {
            case ')':
                bracketCount--;
                break;
                
            case '(':
                bracketCount++;
                break;                
        }
        *curChar += 1;
        //This could be a for loop but this is more readable imo
    }
    
    if( input[*curChar] == '\0' )
    {
        puts("Syntax error: No ending bracket\n");
        return NULL;
    }
    
    size = 2 + (*curChar-startFunc)/2;
    statement = stringToStatement(input + startFunc , size);
//     TODO: Get proper approximation of malloc size
    
    return statement;
}


#define FUNCTION_AMOUNT 13
static int checkFunction(char* input, struct statement* statement, int* curChar)
{
    int i = 0;
    char function[8];

    const char FUNCS[FUNCTION_AMOUNT][8] = {
        "ans",
        "pi",
        "sin",
        "cos",
        "tan",
        "asin",
        "acos",
        "atan",
        "sqrt",
        "log",
        "ceil",
        "floor",
        "abs"
    };
    
	sscanf(&input[*curChar], "%8[a-z]", function);
    
	for(i = 0; i < FUNCTION_AMOUNT; i++)
    {
        if( strncmp(function, FUNCS[i], 8) == 0 )
        {
            while( isLetter(input[*curChar]) )
            { *curChar += 1; }//Skip past the letters
            
            switch(i){
                case 0:
                    statement->number = ANS;
                    statement->statement = NULL;
                break;
                case 1:
                    statement->number = M_PI;
                    statement->statement = NULL;
                break;
                default:
                    statement->statement = movePastBrackets(input, curChar);
                    if(statement->statement == NULL){
                        return -1;
                    }
                    statement->type = i-2;
                break;
            }
            i = FUNCTION_AMOUNT;//Prevent from reading into other strings
        }
    }
    if(i == FUNCTION_AMOUNT+1){
        return 0;
    }
    else{
        printf("Unknown function '%s'\n", function);
        return -1;
    }
}



struct statement* stringToStatement(char* input, int MALLOC_SIZE)
{
    int curChar = 0, placeinBuffer = 0;
    int expectsValue = 1;
    struct statement* statement = calloc(MALLOC_SIZE, sizeof(struct statement) * MALLOC_SIZE);
    
    if(statement == NULL){ 
        puts("MEMORY ALLOCATION FAILED\n");
		exit(ENOMEM);
	}
	
	
    while( input[curChar] != '\0' && input[curChar] != ')')
    {
        if( isNumber(input[curChar]) )
        {   
            if(statement[placeinBuffer].number != 0 || expectsValue == 0)
            {
                puts("Syntax error: too many values\n");
                free(statement);
                return NULL;
            }
            statement[placeinBuffer].number = str_to_num(input, &curChar);
            if( isnan( statement[placeinBuffer].number ) != 0 ){
				puts("NAN");
				free(statement);
				return NULL;
			}

            expectsValue = 0;
        }
        
        
        if( input[curChar] == '(' )
        {
            if(expectsValue == 0)
            {
                statement[placeinBuffer].operator = '*';
                placeinBuffer++;
            }
            
            statement[placeinBuffer].statement = movePastBrackets(input, &curChar);
            statement[placeinBuffer].type = -1;
            expectsValue = 0;
            
            if( statement[placeinBuffer].statement == NULL ){
                return NULL;
            }
        }
        
        
        if( isOperation(input[curChar]) )
        {
            if( expectsValue == 2 || (expectsValue == 1 && getPriority(input[curChar]) != 1) ){
                puts("Syntax error: too many operators\n");
                free(statement);
                return NULL;
            }
            
            if(expectsValue == 0){
                statement[placeinBuffer].operator = input[curChar];
                expectsValue = 1;
                placeinBuffer++;
            }
            else if(expectsValue == 1 && getPriority(input[curChar]) == 1 ){
                
                if(input[curChar] == '-'){
                    statement[placeinBuffer].isNegative = 1;
                }
                expectsValue = 2;
            }
            
            curChar++;
        }// if( isOperation )
        
        if( isLetter(input[curChar]) == 1 )
        {
            if(checkFunction(input, &statement[placeinBuffer], &curChar) != 0){
                free(statement);
                return NULL;    
            }
            expectsValue = 0;
        }
        
        curChar += moveCurChar( input[curChar] );
//         moveCurChar returns 1 if there is no number, letter, bracket etc.
    }
    
    if(expectsValue > 0){
		puts("Found operator without number behind it");
		return NULL;
	}
    
    statement[ placeinBuffer+1 ].operator = '\n';
    return statement;
}

