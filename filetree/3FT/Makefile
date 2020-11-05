# Macros
CC = gcc217

# Dependency rules for non-file targets
all: ft
clean:
	rm -f ft *.o meminfo*

# Dependency rules for file targets
ft: ft.o ft_client.o dynarray.o node.o
	$(CC) ft.o ft_client.o dynarray.o node.o -o ft
ft.o: ft.c ft.h node.h a4def.h dynarray.h
	$(CC) -c ft.c
ft_client.o: ft_client.c ft.h
	$(CC) -c ft_client.c
dynarray.o: dynarray.c dynarray.h
	$(CC) -c dynarray.c
node.o: node.c node.h a4def.h dynarray.h
	$(CC) -c node.c