FILES = main.c charChecks.c lexicalAnalyzer.c calculate.c input.c

OBJS = $(FILES:.c=.o)

COMPILER = gcc
FLAGS = -Wall -Wextra -Werror -pedantic-errors 
LIBS = -lm
EXEC = -o ./calculator

default:
	make dev -j4

dev: $(OBJS)
	$(COMPILER) $(OBJS) $(FLAGS) $(LIBS) $(EXEC)


.c.o:
	$(COMPILER) $(FLAGS) $(LIBS) -c $<  -o $@

$(OBJS):

.PHONY: clean all
clean:
	rm *.o
all:
	touch *.c
	make dev -j4
