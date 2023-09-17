CFLAGS = -Wall -std=c99 -g
LDFLAGS =
CC = gcc

# arquivos-objeto
objects = busca.o 

all: busca

busca: $(objects)
	$(CC) -o busca $(objects) $(LDFLAGS)

busca.o: busca.c
	$(CC) -c $(CFLAGS) busca.c

clean:
	rm -f $(objects) busca