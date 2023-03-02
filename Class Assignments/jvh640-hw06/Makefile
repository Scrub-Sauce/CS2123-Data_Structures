# Makefile for programs in directory ch03-ex01-random-h 
# ***************************************************************

PROGRAMS =   graph

# ***************************************************************
# Parameters to control Makefile operation
# Note that the gccx command script must be defined

CC = gcc
CFLAGS = 

# ***************************************************************
# Entry to bring the package up to date

all: $(PROGRAMS)

# ***************************************************************
# Standard entries to remove files from the directories
#    tidy    -- eliminate unwanted files
#    scratch -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out graphics.ps

scratch: tidy
	rm -f *.o *.a $(PROGRAMS)

# ***************************************************************
# C compilations

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c
    
graph.o: graph.c queue.h
	$(CC) $(CFLAGS) -c graph.c

# ***************************************************************
# Executable programs
    
graph: graph.o queue.o
	$(CC) $(CFLAGS) graph.o queue.o -o graph