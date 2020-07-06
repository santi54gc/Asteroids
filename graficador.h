#ifndef _GRAFICADOR_H_
#define _GRAFICADOR_H_

typedef struct sprite{
	char *nombre;
	uint16_t *n;
	float **coords;
} sprite_t;

bool graficador_inicializar(const char *fn, SDL_Renderer *r);
void graficador_finalizar();
bool graficador_dibujar(const char* nombre, float escala, float x, float y, float angulo);
void graficador_ajustar_variables(double* x, double* y);
void guardar_vector(FILE* f, float **v, size_t n);

/*Este procedimiento recibe un vector dinamico de coordenadas, una posicion inicial en x y una posicion inicial en y, ademas del tamagno del vector de coordenadas; este procedimiento necesita la inclusion de la biblioteca grafica SDL2. */
void dibujar(float ** v, float inicialx,  float inicialy, size_t tam, float escala);

/*Este procedimiento recibe una cadena de caracteres, un entero llamado factor y dos flotantes. Este procedimiento dibuja una palabra en la interfaz grafica de SDL2 multiplicada por el factor en una posicion (inicial_x,inicial_y)*/
void dibujar_cadena(char palabra[],int factor, float inicial_x, float inicial_y);

#endif // _GRAFICADOR_H_
