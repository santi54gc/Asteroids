#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#include "config.h"
#include "caracteres.h"
#include "caracteres.c"

typedef struct {
	char ascii;
	size_t cantidad;
	const int (*caracter)[2];
} dicc_t;

dicc_t tipo[] ={
{'A',7,caracter_a},
{'B',12,caracter_b},
{'C',4,caracter_c},
{'D',7,caracter_d},
{'E',7,caracter_e},
{'F',6,caracter_f},
{'G',7,caracter_g},
{'H',6,caracter_h},
{'I',6,caracter_i},
{'J',4,caracter_j},
{'K',6,caracter_k},
{'L',3,caracter_l},
{'M',5,caracter_m},
{'N',4,caracter_n},
{'O',5,caracter_o},
{'P',5,caracter_p},
{'Q',9,caracter_q},
{'R',7,caracter_r},
{'S',6,caracter_s},
{'T',4,caracter_t},
{'U',4,caracter_u},
{'V',3,caracter_v},
{'W',5,caracter_w},
{'X',5,caracter_x},
{'Y',5,caracter_y},
{'Z',4,caracter_z},

{'0',5,caracter_0},
{'1',2,caracter_1},
{'2',6,caracter_2},
{'3',7,caracter_3},
{'4',5,caracter_4},
{'5',6,caracter_5},
{'6',5,caracter_6},
{'7',3,caracter_7},
{'8',7,caracter_8},
{'9',5,caracter_9},

{'>',5,caracter_derecha},
{'<',5,caracter_izquierda},
{'^',5,caracter_arriba},
{'~',5,caracter_abajo},
{' ',1,caracter_espacio}

};

//Esta funcion recive un caracter y un puntero a size_t. Devuelve un doble puntero a int que corresponde al dibujo del caracter y la cantidad de coordenadas en "cc"
const int** letra_a_vector(char letra, size_t* cc){
	
	*cc=0;
	size_t i;
		for(i=0;tipo[i].ascii!=letra;i++);
		*cc=tipo[i].cantidad;
		return tipo[i].caracter;		
}


