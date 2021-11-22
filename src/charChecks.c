int isNumber(char str)
{
//     Checks if a character is a number
    if(str >= '0' && str <= '9')
        return 1;
    else
        return 0;
}

int isOperation(char str)
{
    //check if char is an operation
    switch (str){
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

int isLetter(char a)
{
    if( a >= 'a' &&  a <= 'z' )
        return 1;
    else
        return 0;
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
// int (*isOperation)(char c) = getPriority;
