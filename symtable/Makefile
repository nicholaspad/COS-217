# Macros
CC = gcc217m

CFLAGS =

# Dependency rules for non-file targets
all: testsymtablelist testsymtablehash
clean:
	rm -f testsymtablelist testsymtablehash *.o
submit:
	submit 3 symtable.h symtablelist.c symtablehash.c \
	Makefile readme feedback

# Dependency rules for file targets
testsymtablelist: testsymtable.o symtablelist.o
	$(CC) $(CFLAGS) testsymtable.o symtablelist.o -o testsymtablelist
testsymtablehash: testsymtable.o symtablehash.o
	$(CC) $(CFLAGS) testsymtable.o symtablehash.o -o testsymtablehash
symtablelist.o: symtablelist.c symtable.h
	$(CC) $(CFLAGS) -c symtablelist.c
symtablehash.o: symtablehash.c symtable.h
	$(CC) $(CFLAGS) -c symtablehash.c
testsymtable.o: testsymtable.c symtable.h
	$(CC) $(CFLAGS) -c testsymtable.c
