#ifndef _DISPARO_H_
#define _DISPARO_H_

typedef struct disparo{
	double x,y,angulo,tiempo;
} disparo_t;

//Esta funcion recibe la posicion de la nave y su rotacion. Pide memoria para un disparo, le asigna esa posicion y rotacion y un tiempo de vida de 0.7 segundos 
disparo_t* disparo_generar(double x, double y, double angulo);

//Esta funcion recibe un disparo y retorna su posicion "x"
double disparo_obtener_x(disparo_t* d);

//Esta funcion recibe un disparo y retorna su posicion "y"
double disparo_obtener_y(disparo_t* d);

//Esta funcion recibe un disparo y libera su memoria
void disparo_destruir(disparo_t* d);

//Esta funcion recibe un disparo y devuelve true si su tiempo de vida es menor a 0 
bool disparo_vivo(disparo_t* d);

//Esta funcion recibe un disparo y un intervalo de tiempo. Utiliza funciones de "cinetica" para modificar su posicion (y llama a una funcion de chequeo), realiza un cambio especifico de potencia y velocidad, y le resta "dt" al tiempo de vida 
void disparo_mover(disparo_t* d, float dt);

//Esta funcion recibe un disparo. Llama a otra de "graficador" y grafica el disparo segun su posicion y rotacion.
bool disparo_dibujar(const disparo_t *d);

//Esta funcion recibe una lista de disparos y una funcion booleana capaz de comparar los datos de la lista. Crea una nueva lista con los nodos para los cuales "f" devuelve true. Estos nodos se eliminan de la lista original
lista_t *lista_filtrar_disparo(lista_t *l, bool (*f)(disparo_t *d));

//Esta funcion recibe una lista de disparos. Destruye el dato de cada nodo, libera su memoria y libera la memoria de la lista
void lista_destruir_disparo(lista_t *l);

#endif // _DISPARO_H_
