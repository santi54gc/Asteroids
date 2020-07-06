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
#include "disparo.h"
#include "nave.h"


disparo_t* disparo_generar(double x, double y, double angulo){

	disparo_t* d = malloc(sizeof(disparo_t));
	if(d==NULL) return false;
	d->x = x; 
	d->y = y;
	d->angulo = angulo;
	d->tiempo = 0.7;

	return d;
}

double disparo_obtener_x(disparo_t* d){ return d->x;}

double disparo_obtener_y(disparo_t* d){return d->y;}

void disparo_destruir(disparo_t* d){
	free(d);
}
bool disparo_vivo(disparo_t* d){
	return d->tiempo < 0;
}
void disparo_mover(disparo_t* d, float dt){
	
	double vx = 1000 * cos(d->angulo);	
	double vy = 1000 * sin(d->angulo);
	d->x = computar_posicion(d->x, vx, dt);
	d->y = computar_posicion(d->y, vy, dt);	
	d->tiempo -= dt;	
	graficador_ajustar_variables(&(d->x), &(d->y));			
}

bool disparo_dibujar(const disparo_t *d){

	return graficador_dibujar("SHOT", 5, d->x, d->y, d->angulo);
}

lista_t *lista_filtrar_disparo(lista_t *l, bool (*f)(disparo_t *d)){
	
		

	lista_t* lfiltrada = lista_crear();
	if(lista_es_vacia(l)) return lfiltrada;
	while(l->prim && f(l->prim->dato)){
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
		if(f(actual->dato)){
			lista_insertar_final(lfiltrada, actual->dato);				
			ant->sig = actual->sig;
			free(actual);
		}else ant = actual;
	}

	return lfiltrada;
}
void lista_destruir_disparo(lista_t *l){
	nodo_t *n = l->prim;
	
	while(n != NULL) {
		nodo_t *sig = n->sig;

		//if(destruir_dato != NULL)
			disparo_destruir(n->dato);

		free(n);

		n = sig;
	}

	free(l);
}
