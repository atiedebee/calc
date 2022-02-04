#include "charChecks.h"
int isNumber(char c)
{
    return c >= '0' && c <= '9';
}

int isOperation(char c)
{
    switch (c){
        case '*':
        case '+':
        case '-':
        case '/':
        case ':':
        case '^':
            return 1;
        default:
            return 0;
    }
}

int isLetter(char c)
{
    return c >= 'a' &&  c <= 'z';
}

int isWhitespace(char c){
	return c == ' ' || c == '\n' || c == '\0' || c == '\t' || c == '\r';
}

int getPriority(char c)
{
    switch(c)
    {
        case '\n':
            return 0;
            
        case '+':
        case '-':
            return 1;
            
        case '*':
        case '/':
        case ':':
            return 2;
            
        case '^':
            return 3;
            
        default:
            return -1;
            break;
    }
}



int moveCurChar(char c)
{
    return ( isLetter(c) + isOperation(c) + isNumber(c) + (c == ')' || c == '(') || c == '\0') == 0;
}// returns 1 if none of these were found
