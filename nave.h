#ifndef _NAVE_H_
#define _NAVE_H_

typedef struct nave{
	double x,y,vx,vy,angulo;
	int potencia;
} nave_t;

nave_t* nave_crear();

//Esta funcion recibe una nave y la libera su memoria
void nave_destruir(nave_t* nave);

//Esta funcion recibe una nave y devuelve su posicion "x" 
double nave_obtener_x(nave_t* nave);

//Esta funcion recibe una nave y devuelve su posicion "y" 
double nave_obtener_y(nave_t* nave);

//Esta funcion recibe una nave y devuelve su "angulo" de rotacion
double nave_obtener_angulo(nave_t* nave);

//Esta funcion recibe una nave vacia y su posicion, velocidad, angulo y potencia inicial y le asigna estos valores
void nave_inicializar(nave_t* nave, double x, double y, double vx, double vy, double angulo, int potencia);

//Esta funcion recibe una nave y le suma "impulso" a su potencia
void nave_impulsar(nave_t* nave, double impulso );

//Esta funcion recibe una nave y le suma "angulo" a su angulo
void nave_rotar(nave_t* nave, double angulo);

//Esta funcion recibe una nave y un intervalo de tiempo. Utiliza funciones de "cinetica" para modificar su posicion (y llama a una funcion de chequeo) y velocidad, y realiza un cambio especifico de potencia.
void nave_mover(nave_t* nave, float dt);

//Esta funcion reibe una nave. Llama a otra de "graficador" y dependiendo de su potencia grafica a la nave con o sin el chorro de impulso, segun su posicion y rotacion
bool nave_dibujar(const nave_t *nave);

#endif // _NAVE_H_
