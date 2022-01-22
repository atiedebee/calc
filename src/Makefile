FILES = main.c charChecks.c lexicalAnalyzer.c calculate.c input.c

OBJS = $(FILES:.c=.o)

COMPILER = gcc
# x86_64-w64-mingw32-gcc

FLAGS = -Wall -Wextra -Werror -pedantic-errors -Wno-unused-variable -Wno-unused-function -Wno-unused-value
OPTIMIZATIONS = -g
LIBS = -lm -lncurses -lreadline
EXEC = calculator

default:dev

dev: $(OBJS)
	$(COMPILER) $(OBJS) $(FLAGS) $(LIBS) $(OPTIMIZATIONS) -o $(EXEC)


.c.o:
	$(COMPILER) $(FLAGS) $(LIBS) $(OPTIMIZATIONS) -c $<  -o $@

$(OBJS):

.PHONY: clean all
clean:
	rm *.o calculator calculator.exe
all:
	touch *.c
	make dev -j4
