#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "listas.h"


static nodo_t *nodo_crear(void *d){
	nodo_t *n = malloc(sizeof(nodo_t));
	if(n == NULL)
		return NULL;

	n->sig = NULL;
	n->dato = d;

	return n;
}

lista_t *lista_crear(){
	lista_t *l = malloc(sizeof(lista_t));
	if(l == NULL) return NULL;

	l->prim = NULL;
	return l;
}


void lista_destruir(lista_t *l, void (*destruir_dato)(void *d)){
	nodo_t *n = l->prim;
	while(n != NULL) {
		nodo_t *sig = n->sig;

		if(destruir_dato != NULL)
			destruir_dato(n->dato);

		free(n);

		n = sig;
	}

	free(l);
}

bool lista_es_vacia(const lista_t *l){
	return l->prim == NULL;
}

bool lista_insertar_comienzo(lista_t *l, void *d){
	nodo_t *n = nodo_crear(d);
	if(n == NULL)
		return false;

	n->sig = l->prim;
	l->prim = n;

	return true;
}

bool lista_insertar_final(lista_t *l, void *d){
	nodo_t *n = nodo_crear(d);
	if(n == NULL) return false;

	if(lista_es_vacia(l)){
		l->prim = n;
		return true;
	}

	nodo_t *aux = l->prim;
	while(aux->sig != NULL)
		aux = aux->sig;

	aux->sig = n;

	return true;
}

void *lista_extraer_primero(lista_t *l){

	if(lista_es_vacia(l))
		return NULL;

	nodo_t *n = l->prim;
	void *d = n->dato;

	l->prim = n->sig;
	free(n);

	return d;
}

void *lista_buscar(const lista_t *l, const void *d, int (*cmp)(const void *a, const void *b)){

	nodo_t *n = l->prim;
	while(n != NULL) {
		if(cmp(n->dato, d) == 0)
			return n->dato;

		n = n->sig;
	}

	return NULL;
}

void *lista_borrar(lista_t *l, const void *dato, int (*cmp)(const void *a, const void *b)){
	
	if(cmp(l->prim->dato, dato) == 0){
		void* d = l->prim->dato;
		nodo_t *aux = l->prim->sig;
		free(l->prim);
		l->prim = aux;
		
		return d; 
	}

	if(l->prim == NULL)
		return NULL;

	nodo_t *ant = l->prim;
	while(ant->sig){
		nodo_t *actual = ant->sig;
		if(cmp(actual->dato, dato) == 0){
			void* d = actual->dato;
			ant->sig = actual->sig;
			free(actual);

			return d;
		}else ant = actual;
	}
	return NULL;
}

void lista_mapear(lista_t *l, void *(*f)(void *dato, void *extra), void *extra){
	
	if(lista_es_vacia(l)) return;	
	
	nodo_t *n = l->prim;	
	while(n != NULL) {
		n->dato = f(n->dato, extra);
		n = n->sig;
	}
}

void lista_recorrer(const lista_t *l, bool (*visitar)(void *dato, void *extra), void *extra){

	if(lista_es_vacia(l)) return;

	nodo_t *n = l->prim;	
	while(n != NULL) {
		if(!visitar(n->dato, extra)) break;
		n = n->sig;
	}	
}

lista_t *lista_filtrar(lista_t *l, bool (*f)(void *dato, void *extra), void *extra){

	lista_t* lfiltrada = lista_crear();

	if(lista_es_vacia(l)) return lfiltrada;	

	while(l->prim && f(l->prim->dato, extra)){
		lista_insertar_final(lfiltrada, l->prim->dato);		
		nodo_t *aux = l->prim->sig;
		free(l->prim);
		l->prim = aux;
	}

	if(l->prim == NULL && lfiltrada->prim == NULL) return NULL;
	else if(l->prim == NULL && lfiltrada->prim != NULL) return lfiltrada; 
		
	nodo_t *ant = l->prim;
	while(ant->sig){
		nodo_t *actual = ant->sig;
		if(f(actual->dato, extra)){
			lista_insertar_final(lfiltrada, actual->dato);				
			ant->sig = actual->sig;
			free(actual);
		}else ant = actual;
	}

	return lfiltrada;
}

bool lista_extender(lista_t *a, lista_t *b){
	
	if(lista_es_vacia(a) || lista_es_vacia(b)){
		return false;
	}else{
		nodo_t *n = a->prim;	
		while(n->sig != NULL) {
			n = n->sig;
		}
		n->sig = b->prim;
	}
	b->prim = NULL;
	return true;
}

lista_iterador_t *lista_iterador_crear(lista_t *l){

	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t)); 
	
	iterador->lista = l;
	iterador->actual = l->prim;
	iterador->anterior = NULL; 
	
	return iterador;
}

void lista_iterador_destruir(lista_iterador_t *li){

	free(li);
}

void* lista_iterador_actual(const lista_iterador_t *li){

	return li->actual->dato;
}

bool lista_iterador_siguiente(lista_iterador_t *li){

	li->anterior = li-> actual;
	li->actual = li->actual->sig;

	if(li->actual == NULL)return false;

	return true;
}

bool lista_iterador_termino(const lista_iterador_t* li){
	
	if(li->actual != NULL) return false;

	return true;

}

void* lista_iterador_eliminar(lista_iterador_t* li){
	
	void* d = lista_iterador_actual(li);

	if(li->anterior == NULL){
		nodo_t*aux= li->actual;
		li->actual = li->actual->sig;	
		free(aux);
		li->lista->prim = li->actual ;	
	}else{
		li->anterior->sig = li->actual->sig;
		free(li->actual);
		li->actual = li->anterior->sig;
	}
	return d;
}

bool lista_iterador_insertar(lista_iterador_t *li, void *dato){

	nodo_t *n = nodo_crear(dato);
	if(n == NULL) return false;
	
	n->sig = li->actual->sig; 
	li->actual->sig = n;

	return true;
}


