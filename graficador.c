#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "graficador.h"
#include "vectores.h"
#include "config.h"
#include "caracteres.h"

static SDL_Renderer *renderer;
static FILE *file;
static sprite_t *sprites;
static size_t contador;
static int w, h;

void guardar_vector(FILE* f, float **v, size_t n){
	
	for(size_t i=0;i< n;i++)
		fread(v[i],sizeof(float),2,f);
}

bool graficador_inicializar(const char *fn, SDL_Renderer *r){

	FILE *f=fopen(fn,"rb");
	if(f==NULL) return false;
	sprite_t *s;
	sprite_t *aux;
	aux=malloc(0);
	if(aux==NULL) return false;
	size_t i = 0;
	while(1){
		s=realloc(aux,sizeof(sprite_t)*(i+1));
		if(s==NULL) return false;
		s[i].nombre = malloc(sizeof(char)*10);
		if(s[i].nombre==NULL) return false;
		if(fread(s[i].nombre,sizeof(char),10,f)!=10){ free(s[i].nombre); break;}
		s[i].n=malloc(sizeof(uint16_t));
		if(s[i].n==NULL) return false;
		fread(s[i].n,sizeof(uint16_t),1,f); 
		s[i].coords = pedir_memoria(*(s[i].n), 2);
		if(s[i].coords==NULL) return false;
		guardar_vector(f, s[i].coords, *(s[i].n));
		aux=s;
		i++;
	}
	contador=i;
	sprites=s;
	SDL_GetRendererOutputSize(r,&w,&h);
	renderer=r;
	file=f;
	return true;
}

void graficador_finalizar(){

	for(size_t i = 0; i < contador; i++){
		free(sprites[i].nombre);
		destruir_vector(sprites[i].coords, *(sprites[i].n), 2);
		free(sprites[i].n);
	}

	free(sprites);
	fclose(file);
}

bool graficador_dibujar(const char* nombre, float escala, float x, float y, float angulo){

	size_t i;

	for(i = 0; strcmp(sprites[i].nombre,nombre)!=0;i++);

	float** coords = pedir_memoria(*(sprites[i].n), 2);
	if(coords==NULL) return false;
	copiar_vector(sprites[i].coords, coords, *(sprites[i].n));


	
	rotar(coords,*(sprites[i].n),angulo);

	dibujar(coords, x, y, *(sprites[i].n), escala);
		
	destruir_vector(coords,*(sprites[i].n),2);
	return true;
}

void graficador_ajustar_variables(double* x, double* y){

	if((*x)>w) (*x)=0;
	if((*x)<0) (*x)=w;
	if((*y)>h) (*y)=0;
	if((*y)<0) (*y)=h;
}

void dibujar(float ** v, float inicialx,  float inicialy, size_t tam, float escala){

		for(int i = 0; i < tam - 1; i++)
			SDL_RenderDrawLine(
				renderer,
				v[i][0] * escala + inicialx,
				-v[i][1] * escala + VENTANA_ALTO - inicialy,
				v[i+1][0] * escala + inicialx,
				-v[i+1][1] * escala + VENTANA_ALTO - inicialy
			);
}
void dibujar_cadena(char palabra[],int factor, float inicial_x, float inicial_y){
			
	
	size_t n;
	
	for(size_t i =0; palabra[i]!='\0'; i++){
		n=0;
		const int(*v)[2]=letra_a_vector(palabra[i],&n);
		
		for(size_t j = 0; j < n-1; j++)
			SDL_RenderDrawLine(
			renderer,
			v[j][0]*factor+inicial_x,
			-v[j][1]*factor+ VENTANA_ALTO - inicial_y,
			v[j+1][0]*factor+inicial_x,
			-v[j+1][1]*factor+VENTANA_ALTO-inicial_y				
		);
		inicial_x+=6*factor;
	}
}
