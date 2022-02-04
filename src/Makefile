FILES = main.c charChecks.c lexicalAnalyzer.c calculate.c input.c

OBJS = $(addprefix bin/, $(FILES:.c=.o) )

COMPILER = gcc	
# x86_64-w64-mingw32-gcc

FLAGS = -Wall -Wextra -Werror -pedantic-errors
OPTIMIZATIONS = -Os
LIBS = -lm
EXEC = calculator

default:
	make dev -j4

dev: $(OBJS)
	$(COMPILER) $(OBJS) $(FLAGS) $(LIBS) $(OPTIMIZATIONS) -o $(EXEC)


bin/%.o: %.c
	$(COMPILER) $(FLAGS) $(LIBS) $(OPTIMIZATIONS) -c $<  -o $@

$(OBJS):

.PHONY: clean all
clean:
	rm bin/*.o calculator calculator.exe -f
all:
	touch *.c
	make dev -j4
