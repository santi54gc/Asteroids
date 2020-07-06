#ifndef _VECTORES_H_
#define _VECTORES_H_

/*Esta funcion recibe un vector dinamico de coordenadas ordenado de menor a mayor, su cantidad de coordenadas y un par de coordenadas (x,y). Esta funcion devuelve 'true' si el punto se encuentre arriba del vector, y 'false' si se encuentre abajo*/
bool esta_arriba(float **v, size_t n, float x, float y);
void trasladar(float** v, size_t n, float dx, float dy);
void rotar(float** v, size_t n, double rad);

/*Este procedimiento recibe un vector dinamico 'v' y sus dimensiones 'n' 'm'. El procedimiento imprime los elementos del vector dinamico en pantalla*/
void imprimir_vector(float** v, size_t n, size_t m);

/*Esta funcion recibe un vector dinamico ordenado de menor a mayor segun la coordenada x, una coordenada x, el numero de puntos del vector. La funcion devuelve un flotante correspondiente a la coordenada y de x en el vector*/
float y_correspondiente(float **v, float x, size_t nv);

/*Este procedimiento recibe un vector dinamico y sus dimensiones. El procedimiento libera el espacio de memoria asignado al vector dinamico*/
void destruir_vector(float **v, size_t n, size_t m);

/*Esta funcion recibe una matriz de dos coordenadas y el numero de coordenadas. Devuelve un vector dinamico con los mismos elementos de la matriz ingresada*/
float **matriz_a_vector(const float m[][2], size_t n);

/*Este procedimiento recibe dos vectores dinamicos v, w y un entero n. El procedimiento copia los elementos del vector v de dimension nx2 en el vector w, la dimension del vector w tiene que ser igual o mayor a n*/
void copiar_vector(float **v, float **w, size_t n);

/*Precondicion: tiene que haber espacio para agregar un elemento nuevo. Este procedimiento recibe un vector dinamico de dimension nx2 ordenado de menor a mayor segun la coordenada x, dos flotantes x, y; y un entero j.El procedimiento agrega un punto (x,y) al vector de manera que se mantenga el orden previo.*/
void agregar_ordenado(float **v,size_t n,float x,float y, size_t j);

/*Esta funcion recibe un flotante rango y un flotante inicio. La funcion devuelve un flotante que se encuentra entre inicio e inicio+rango.*/
float generar_aleat(float rango, float inicio);

/*Esta funcion recibe un vector dinamico ordenado, su numero de puntos, un nuevo numero de puntos y un flotante llamado margen. La funcion devuelve un vector dinamico nuevo con el nuevo numero de puntos tal que los puntos nuevos se encuentran dentro del rango horizontal del vector inicial y dentro de un rango vertical +/-margen generado en cada punto del vector*/
float **densificar_vector(float** v, size_t nv, size_t nn, float margen);

/*Esta funcion recibe dos enteros n y m. La funcion devuelve un vector dinamico de dimension nxm. Usar esta funcion para asignar una direccion de memoria a un vector dinamico de dimension nxm. La funcion devuelve NULL si hay un problema con la asignacion de memoria.*/
float** pedir_memoria(size_t n, size_t m);

/*Esta funcion devuelve un flotante entre 0.00 y 1.00*/
float randf();

/*Esta funcion recibe un puntero a size_t que apunta al tamagno del vector que devolvera la funcion. La funcion devuelve un vector dinamico de coordenadas ordenado de menor a mayor y devuelve por interfaz la cantidad de coordenadas del mismo*/
float ** crear_terreno ( size_t * n );

//Esta funcion recive una "cantidad" de pares de coordenadas, y los margenes de x e y. Genera un doble puntero a float de "cantidad" de pares de coordenadas en esos margenes 
float **coordenadas_aleatorias(size_t cantidad, float margenx, float margeny, float basex, float basey);

#endif // _VECTORES_H_
