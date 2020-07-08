# Asteroids
Asteroids

Ingresar en la terminal:

sudo apt - get install libsdl2 - dev

Al compilar hay que indicarle al enlazador del GCC que enlace contra la biblioteca en
cuestíon, esto se hace mediante el flag -lSDL2.

Se recomienda usar el makefile

Verificar que en el makefile la lista de flags para asteroids sea la siguiente:
$(CFLAGS) S^ -o asteroids.o $(LFLAGS)
Lo importante es que las LFLAGS esten al final, sino no corre
