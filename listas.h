#ifndef _LISTA_H_
#define _LISTA_H_

typedef struct nodo {
	struct nodo *sig;
	void *dato;
}nodo_t;

typedef struct lista {
	nodo_t *prim;
}lista_t;

typedef struct iterador{
	nodo_t* actual;
	nodo_t* anterior;
	lista_t *lista;
}lista_iterador_t;

//Esta funcion crea una lista vacia y la devuelve
lista_t *lista_crear();

//Esta funcion recibe una lista y una funcion que sepa destruir los datos de esta lista. Destruye cada dato y libera la memoria de cada nodo y la de la lista.
void lista_destruir(lista_t *l, void (*destruir_dato)(void *d));

//Esta funcion recibe una lista y devuelve true si la lista no tiene ningun nodo
bool lista_es_vacia(const lista_t *l);

//Esta funcion recibe una lista y un dato, crea un nuevo nodo con el dato y lo inserta al principio de la lista. Devuelve true si pudo hacerlo
bool lista_insertar_comienzo(lista_t *l, void *d);

//Esta funcion recibe una lista y un dato, crea un nuevo nodo con el dato y lo inserta al final de la lista. Devuelve true si pudo hacerlo
bool lista_insertar_final(lista_t *l, void *d);

//Esta funcion recibe una lista, elimina el primer nodo y devuelve el dato que este contenía
void *lista_extraer_primero(lista_t *l);

//Esta funcion recibe una lista, un dato, y una funcion que sepa comparar los datos de la lista. Recorre la lista y si encuentra el dato que busca, devuelve el dato de ese nodo
void *lista_buscar(const lista_t *l, const void *d, int (*cmp)(const void *a, const void *b));

//Esta funcion recibe una lista, un dato, y una funcion que sepa comparar los datos de la lista. Recorre la lista y si encuentra el dato que busca, devuelve el dato del nodo y borra el nodo 
void *lista_borrar(lista_t *l, const void *dato, int (*cmp)(const void *a, const void *b));

//Esta funcion recibe una lista, una funcion que sepa aplicarle el dato "extra" a los datos de la lista y el dato extra. Recorre la lista y a los datos de cada nodo le aplica esta funcion
void lista_mapear(lista_t *l, void *(*f)(void *dato, void *extra), void *extra);

//Esta funcion recibe una lista, una funcion booleana que sabe leer cada dato y analizarlo con "extra", y el dato extra. Recorre la lista hasta que la funcion visitar devuelve true. Visitar no deberia modificar la lista  
void lista_recorrer(const lista_t *l, bool (*visitar)(void *dato, void *extra), void *extra);

//Esta funcion recibe una lista, una funcion booleana que se aplica sobre los datos y un dato extra para esta funcion. Crea una nueva lista con los nodos en los cuales "f" retorna true, y elimina estos nodos de la lista original.
lista_t *lista_filtrar(lista_t *l, bool (*f)(void *dato, void *extra), void *extra);

//Esta funcion recibe dos listas y agrega todos los nodos de "b" a "a". La lista "b" queda vacia. 
bool lista_extender(lista_t *a, lista_t *b);

//Esta funcion recibe una lista y crea un iterador que apunta a la lista y a su primer nodo.
lista_iterador_t *lista_iterador_crear(lista_t *l);

//Esta funcion recibe un iterador y libera su memoria
void lista_iterador_destruir(lista_iterador_t *li);

//Esta funcion recibe un iterador y devuelve el dato del nodo que apunta
void* lista_iterador_actual(const lista_iterador_t *li);

//Esta funcion recibe un iterador y devuelve true si logra apuntar en "anterior" al nodo actual y en "actual" al nodo siguiente (si no termino la lista)
bool lista_iterador_siguiente(lista_iterador_t *li);

//Esta funcion recibe un iterador y devuelve true si la lista se termino
bool lista_iterador_termino(const lista_iterador_t* li);

//Esta funcionrecibe un iterador, elimina el nodo al que apunta "actual" y devuelve el dato que contiene
void* lista_iterador_eliminar(lista_iterador_t* li);

//Esta funcion recibe un iterador y un dato. Agrega un nuevo nodo que contiene "dato" en la posicion siguiente a la que se encuentra "actual" del iterador
bool lista_iterador_insertar(lista_iterador_t *li, void *dato);

#endif
