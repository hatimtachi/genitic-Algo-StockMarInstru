CC=gcc
SRC=DataFunctions.c main.c
CFLAGS=-Wall 
LDFLAGS = 
PROGRAMS = AlgoGen
platform=$(shell uname -s)
ifeq ($(platform),Darwin)
	OBJ=$(SRC:.c=.o) 
else
	OBJ=$(SRC:.c=.o) -lm
endif
all : $(PROGRAMS)
AlgoGen:    $(OBJ) Structure.h 
	$(CC)  -o $@ $(OBJ)
%.o:	%.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -rf $(PROGRAMS) *.o