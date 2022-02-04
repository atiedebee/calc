#include <stdlib.h>
#include <math.h>

#include "global_data.h"
#include "charChecks.h"
#include "converters.h"

// #define DEBUG
static int getStatementLength( struct statement* statement )
{
    int size = 0;
    while(statement[size].operator != '\n'){
        size++;
    }
    return size;
}

static double absD(double num)
{
    return num < 0.0 ? num * -1 : num;
}


static double functionOnNumber( double number, int type )
{//Applies function to an input number
    double (*funcPtrs[11])(double) = {
        sin, cos, tan, asin, acos, atan, sqrt, log10, ceil, floor, absD
    };
    
    if( DEGREES == 1 && type <= 5 ){
        number *= M_PI/180;
    }
    
    return funcPtrs[type](number);
}
// TODO: Seperate variables from functions to make it more scalable

static double operationOnStatement( double num1, double num2, char operator)
{
    switch( operator )
    {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
        case ':':
            return num1 / num2;
        case '^':
            return pow(num1, num2);
        default:
            return 0;
    }
    return 0;
}


#ifdef DEBUG
static void printStatement(struct statement* statement)
{//Debugging function
    int i;
        printf("place\tnumber\t\toperation\n");
    for(i = 0; statement[i].operator != '\n'; i++)
    {
        printf("%d\t%lf\t'%c'\n", i, statement[i].number, statement[i].operator);
    }
}
#endif

static void removeStatement(struct statement* statement, int statementtoRemove) //placeInBuffer
{
    int i;
    
    for( i = statementtoRemove; statement[i].operator != '\n'; i++)
    {
        statement[i].operator = statement[i+1].operator;
        if( statement[i+1].statement != NULL ){
            statement[i].statement = statement[i+1].statement;            
        }else{
            statement[i].number = statement[i+1].number;
        }
    }
}

double calculate(struct statement* statement)
{
    double result;
    int placeinBuffer;
    
    for(placeinBuffer = 0; statement[placeinBuffer].operator != '\n'; placeinBuffer++)
    {   
        if(statement[placeinBuffer].statement != NULL)
        {// Converts brackets to numbers, then applies a function to the result if there was a function in there
            statement[placeinBuffer].number = calculate(statement[placeinBuffer].statement);
            statement[placeinBuffer].statement = NULL;
            
            if(statement[placeinBuffer].type != -1){
                statement[placeinBuffer].number = functionOnNumber( statement[placeinBuffer].number,
                                                                    statement[placeinBuffer].type );
            }
        }
        if(statement[placeinBuffer].isNegative == 1){
            statement[placeinBuffer].number *= -1;
        }
    }
    placeinBuffer = 0; // "Reusing" placeinBuffer.
    
    while( getStatementLength(statement) > 1 )
    {//Parses through the input statement to calculate everything in order
        if( getPriority(statement[placeinBuffer].operator) >= getPriority(statement[placeinBuffer+1].operator) )
        {
            statement[placeinBuffer+1].number = operationOnStatement( statement[placeinBuffer].number, 
                                                                      statement[placeinBuffer+1].number, 
                                                                      statement[placeinBuffer].operator);
            removeStatement( statement, placeinBuffer );
            placeinBuffer = 0;
        }else{
            placeinBuffer += 1;
        }
        
        if( statement[placeinBuffer].operator == '\n'){
            placeinBuffer = 0;
        }
        
    }///while( getStatementLength > 0 )
    
    result = statement[0].number;
    
    free(statement);
    statement = NULL;
    return result;
}
