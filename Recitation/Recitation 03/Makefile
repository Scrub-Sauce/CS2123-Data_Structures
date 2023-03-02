# Makefile for programs in directory ch03-ex01-random-h 
# ***************************************************************

PROGRAMS =   jvh640-rec06

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

random.o: random.c random.h
	$(CC) $(CFLAGS) -c random.c

jvh640-rec06.o: jvh640-rec06.c random.h
	$(CC) $(CFLAGS) -c jvh640-rec06.c


# ***************************************************************
# Executable programs

jvh640-rec06: jvh640-rec06.o random.o
	$(CC) $(CFLAGS) -o jvh640-rec06  jvh640-rec06.o random.o

