#define CHARCHECKS_H
#ifdef CHARCHECKS_H

int isLetter(char c);
int isOperation(char c);
int isNumber(char c);
int isWhitespace(char c);

int getPriority(char c);

int moveCurChar(char c);

#endif