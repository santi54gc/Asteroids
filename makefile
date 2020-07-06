CC := gcc
CFLAGS := -Wall -c -pedantic -std=c99 
LFLAGS := -lSDL2 -g -lm


all: asteroids

main.o: main.c config.h graficador.h nave.h
	$(CC) $(CFLAGS) $(LFLAGS) main.c

nave.o: nave.c nave.h cinetica.h 
	$(CC) $(CFLAGS) $(LFLAGS) nave.c

asteroide.o: asteroide.c asteroide.h cinetica.h 
	$(CC) $(CFLAGS) $(LFLAGS) asteroide.c

disparo.o: disparo.c disparo.h cinetica.h 
	$(CC) $(CFLAGS) $(LFLAGS) disparo.c

graficador.o: graficador.c graficador.h vectores.h
	$(CC) $(CFLAGS) $(LFLAGS) graficador.c

vectores.o: vectores.c vectores.h  config.h
	$(CC) $(CFLAGS) $(LFLAGS) vectores.c

cinetica.o: cinetica.c cinetica.h 
	$(CC) $(CFLAGS) $(LFLAGS) cinetica.c

diccionario.o: diccionario.c caracteres.c caracteres.h
	$(CC) $(CFLAGS) diccionario.c

listas.o: listas.c listas.h 
	$(CC) $(CFLAGS) $(LFLAGS) listas.c

asteroids: main.o graficador.o vectores.o nave.o cinetica.o vectores.o diccionario.o listas.o asteroide.o disparo.o
	$(CC) $(LFLAGS) $^ -o asteroids

run:
	./asteroids
 
clean:
	rm *.o

valgrind: asteroids
	valgrind --leak-check=full ./asteroids
