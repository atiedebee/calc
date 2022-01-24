#define CONVERTERS_H
#ifdef CONVERTERS_H
struct statement* stringToStatement(char* input, int MALLOC_SIZE);

double calculate(struct statement* statement);
#endif