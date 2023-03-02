# Makefile for programs in directory ch03-ex01-random-h 
# ***************************************************************

PROGRAMS =   driver

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

binary.o: binary.c binary.h
	$(CC) $(CFLAGS) -c binary.c
    
driver.o: driver.c binary.h
	$(CC) $(CFLAGS) -c driver.c

# ***************************************************************
# Executable programs
    
driver: driver.o binary.o
	$(CC) $(CFLAGS) driver.o binary.o -o driver