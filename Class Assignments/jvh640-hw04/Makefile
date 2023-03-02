# Makefile for programs in directory ch03-ex01-random-h 
# ***************************************************************

PROGRAMS =   driver-array / driver-list

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

setArrayImp.o: setArrayImp.c set.h
	$(CC) $(CFLAGS) -c setArrayImp.c

setLinkedListImp.o: setLinkedListImp.c set.h
	$(CC) $(CFLAGS) -c setLinkedListImp.c
    
driver.o: driver.c set.h
	$(CC) $(CFLAGS) -c driver.c

# ***************************************************************
# Executable programs
    
driver-array: driver.o setArrayImp.o
	$(CC) $(CFLAGS) driver.o setArrayImp.o -o driver-array
    
driver-list: driver.o setLinkedListImp.o
	$(CC) $(CFLAGS) driver.o setLinkedListImp.o -o driver-list