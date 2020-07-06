#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <math.h>
#include "nave.h"
#include "graficador.h"
#include "cinetica.h"

nave_t* nave_crear(){

	nave_t* nave = malloc(sizeof(nave_t));
	return nave;
}

void nave_destruir(nave_t* nave){
	
	free(nave);

}

double nave_obtener_x(nave_t* nave){ return nave->x;}
double nave_obtener_y(nave_t* nave){return nave->y;}
double nave_obtener_angulo(nave_t* nave){return nave->angulo;}

void nave_inicializar(nave_t* nave, double x, double y, double vx, double vy, double angulo, int potencia){

	nave->x = x;
	nave->y = y;
	nave->vx = vx;
	nave->vy = vy;
	nave->angulo = angulo;
	nave->potencia = potencia;
}

void nave_impulsar(nave_t* nave, double impulso ){

	nave->potencia += impulso;
}

void nave_rotar(nave_t* nave, double angulo){
	
	nave->angulo += angulo;		

}

void nave_mover(nave_t* nave, float dt){
	
	nave->x = computar_posicion(nave->x, nave->vx, dt);
	nave->y = computar_posicion(nave->y, nave->vy, dt);		
	nave->vx = computar_velocidad(nave->vx, nave->potencia * cos(nave->angulo), dt) * pow(0.99,100*dt);	
	nave->vy = computar_velocidad(nave->vy, nave->potencia * sin(nave->angulo), dt) * pow(0.99,100*dt);
	nave->potencia = nave->potencia * pow(0.90,100*dt);
	graficador_ajustar_variables(&(nave->x), &(nave->y));	

}

bool nave_dibujar(const nave_t *nave){
	
	if(nave->potencia > 1) graficador_dibujar("THURST", 1, nave->x, nave->y, nave->angulo);
	return graficador_dibujar("SHIP", 1, nave->x, nave->y, nave->angulo);
}
