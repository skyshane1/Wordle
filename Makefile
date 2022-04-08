CC = gcc          
CFLAGS = -g 
LDLIBS = -lncurses

default: wordle    	

wordle: main.o game.o stats.o
		$(CC) $(CFLAGS) -o wordle main.o game.o stats.o $(LDLIBS)

main.o: main.c game.h
		$(CC) $(CFLAGS) -c main.c $(LDLIBS)

game.o: game.c game.h
		$(CC) $(CFLAGS) -c game.c $(LDLIBS)

stats.o: stats.c stats.h
		$(CC) $(CFLAGS) -c stats.c $(LDLIBS)

clean:
		rm -f wordle *.o
