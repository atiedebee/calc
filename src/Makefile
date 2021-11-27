FILES = main.c charChecks.c lexicalAnalyzer.c calculate.c input.c

OBJS = $(FILES:.c=.o)

COMPILER = gcc	
# x86_64-w64-mingw32-gcc

FLAGS = -Wall -Wextra -Werror -pedantic-errors
OPTIMIZATIONS = -O2
LIBS = -lm
EXEC = calculator

default:
	make dev -j4

dev: $(OBJS)
	$(COMPILER) $(OBJS) $(FLAGS) $(LIBS) $(OPTIMIZATIONS) -o $(EXEC)


.c.o:
	$(COMPILER) $(FLAGS) $(LIBS) $(OPTIMIZATIONS) -c $<  -o $@

$(OBJS):

.PHONY: clean all
clean:
	rm *.o calculator calculator.exe -f
all:
	touch *.c
	make dev -j4
