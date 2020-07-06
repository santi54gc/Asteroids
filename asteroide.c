#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <time.h>
#include "config.h"
#include "graficador.h"
#include "cinetica.h"
#include "listas.h"
#include "asteroide.h"
#include "vectores.h"

asteroide_t* asteroide_crear(double x, double y, size_t radio){

	asteroide_t* a= malloc(sizeof(asteroide_t));
		if(a == NULL) return NULL;
	a->x = x;
	a->y = y;
	a->radio = radio;
	a->v = generar_aleat(200, 1000.0/a->radio - 30);
	a->angulo = randf() * 2 * PI;
	a->clase = rand()%4 + 1;
	return a;

}

bool asteroide_colision(asteroide_t* a, double x, double y){

	return sqrt(pow((a->x-x),2)+pow((a->y-y),2)) < a->radio;
}

void asteroide_destruir(asteroide_t* a){
	
	free(a);

}

double asteroide_obtener_radio(asteroide_t*a){

	return a->radio;
}

asteroide_t* asteroide_dividido(asteroide_t* a){

	return asteroide_crear(a->x, a->y, a->radio/2);
}	

void asteroide_mover(asteroide_t* a, float dt){
	
	double vx = a->v * sin(a->angulo);	
	double vy = a->v * cos(a->angulo);
	a->x = computar_posicion(a->x, vx, dt);
	a->y = computar_posicion(a->y, vy, dt);
	graficador_ajustar_variables(&(a->x), &(a->y));	
}


bool asteroide_dibujar(const asteroide_t *a){

	if(a->clase == 1) return graficador_dibujar("ROCK1", a->radio, a->x, a->y, a->angulo);
	if(a->clase == 2) return graficador_dibujar("ROCK2", a->radio, a->x, a->y, a->angulo);
	if(a->clase == 3) return graficador_dibujar("ROCK3", a->radio, a->x, a->y, a->angulo);
	if(a->clase == 4) return graficador_dibujar("ROCK4", a->radio, a->x, a->y, a->angulo);

return false;
}

lista_t *lista_filtrar_asteroide(lista_t *l, bool (*f)(asteroide_t *dato, double extra, double extra2), double extra, double extra2){
	
	lista_t* lfiltrada = lista_crear();
	if(lista_es_vacia(l)) return lfiltrada;
	while(l->prim && f(l->prim->dato, extra, extra2)){
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
		if(f(actual->dato, extra, extra2)){
			lista_insertar_final(lfiltrada, actual->dato);				
			ant->sig = actual->sig;
			free(actual);
		}else ant = actual;
	}

	return lfiltrada;
}

void lista_destruir_asteroide(lista_t *l){
	nodo_t *n = l->prim;
	
	while(n != NULL) {
		nodo_t *sig = n->sig;

			asteroide_destruir(n->dato);

		free(n);

		n = sig;
	}

	free(l);
}
