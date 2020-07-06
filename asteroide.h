#ifndef _ASTEROIDE_H_
#define _ASTEROIDE_H_

typedef struct asteroide{
	double x,y,v,angulo;
	size_t radio,clase;
} asteroide_t;

//Esta funcion recibe una posicion y un radio. Pide memoria para un asteroide, le asigna esa posicion y radio, y le genera una velocidad, angulo y clase aleatoreos
asteroide_t* asteroide_crear(double x, double y, size_t radio);

//Esta funcion recibe un asteroide y una posicion. Deveulve true si la distancia de esa posicion a la del asteroide es menor a su radio
bool asteroide_colision(asteroide_t* a,double x, double y);

//Esta funcion recibe un asteroide y libera su memoria
void asteroide_destruir(asteroide_t* a);

//Esta funcion recibe un asteroide y devuelve su radio
double asteroide_obtener_radio(asteroide_t*a);

//ESta funcion recibe un asteroide y crea uno nuevo en la misma posicion con la mitad del radio
asteroide_t* asteroide_dividido(asteroide_t* a);

//Esta funcion recibe un asteroide y un intervalo de tiempo. Utiliza funciones de "cinetica" para modificar su posicion (y llama a una funcion de chequeo) y realiza la orientacion de la velocidad segun el angulo 
void asteroide_mover(asteroide_t* a, float dt);

//Esta funcion recibe un asteroide. Llama a otra de "graficador" y grafica el disparo segun su posicion, rotacion, radio y tipo.
bool asteroide_dibujar(const asteroide_t *a);

//Esta funcion recibe una lista de asteroides, una funcion booleana capaz de comparar los datos de la lista y dos datos para comparar. Crea una nueva lista con los nodos para los cuales "f" devuelve true. Estos nodos se eliminan de la lista original
lista_t *lista_filtrar_asteroide(lista_t *l, bool (*f)(asteroide_t *dato, double extra, double extra2), double extra, double extra2);

//Esta funcion recibe una lista de asteroides. Destruye el dato de cada nodo, libera su memoria y libera la memoria de la lista
void lista_destruir_asteroide(lista_t *l);

#endif // _ASTEROIDE_H_
