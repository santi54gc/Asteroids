#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "vectores.h"
#include "config.h"


float randf(){

	return rand()/(float) RAND_MAX;
}

float generar_aleat(float rango, float inicio){

		return randf()*rango+inicio;

}

bool esta_arriba(float **v, size_t n, float x, float y){

	return y> y_correspondiente(v,x,n);

}

void trasladar(float** v, size_t n, float dx, float dy){

	for(size_t i=0;i<=n-1;i++){
		v[i][0]+=dx;
		v[i][1]+=dy;
	}
	
}

void rotar(float** v, size_t n, double rad){
	
	double c=cos(rad); 
	double s=sin(rad);

	for(size_t i=0;i<=n-1;i++){
		float x=v[i][0]*c-v[i][1]*s;
		float y=v[i][0]*s+v[i][1]*c;
		v[i][0]=x;
		v[i][1]=y;
	}
}


void imprimir_vector(float** v, size_t n, size_t m){

	for(size_t i = 0 ;i <= n - 1;  i++){

		for(size_t j = 0; j < m; j++){

			printf("%f\t",v[i][j]);

		}
		printf("\n");
	}
	printf("\n");
}


float y_correspondiente(float **v, float x, size_t nv){
	
	float m;
	for(size_t i=0;i<nv-1;i++){

			if(x<=v[i+1][0]){

				m=(v[i+1][1]-v[i][1])/(v[i+1][0]-v[i][0]);
				return m*(x-v[i][0])+v[i][1];
			}
	}
	return 0;
}


void destruir_vector(float **v, size_t n, size_t m){
	
	for(int i=0;i<n;i++){
		free(v[i]);
	}
	free(v);
}


float** pedir_memoria(size_t n, size_t m){

	float** v;

	v=malloc(sizeof(float*)*n);
	if(v==NULL)
		return NULL;

	for(size_t j=0;j<n;j++){
		v[j]=(float*)malloc(sizeof(float)*m);
		if(v[j]==NULL){
			for(size_t i = 0; i < j; j++){
				free(v[i]);
			}
			free(v);
			return NULL;
		}
	}
	
	return v;
}


float **matriz_a_vector(const float m[][2], size_t n){
	
	float** v=pedir_memoria(n,2);
		if(v==NULL) return NULL;
	for(size_t j=0;j<n;j++){

		v[j][0]=m[j][0];
		v[j][1]=m[j][1];

	}

	return v;	

}


void copiar_vector(float **v, float **w, size_t n){
	

	for(size_t i=0;i<n;i++){

		w[i][0]=v[i][0];
		w[i][1]=v[i][1];

	}	

}

void agregar_ordenado(float **v,size_t n,float x,float y, size_t j){

	size_t i,k;
	for(i=0;i<j+n;i++){
		if(x<v[i][0])
			break;
	}
	for(k=j+n;k>i;k--){
		v[k][0]=v[k-1][0];
		v[k][1]=v[k-1][1];
	}

	v[i][0]=x;
	v[i][1]=y;

}


float **densificar_vector(float** v, size_t nv, size_t nn, float margen){

	size_t j;
	float x,y;
	float rango=v[nv-1][0]-v[0][0];
	float** v_densificado = pedir_memoria(nn,2);
		if(v_densificado==NULL) return NULL;
	copiar_vector(v,v_densificado,nv);

	for(j = 0;j < nn-nv; j++){

		x=generar_aleat(rango,v[0][0]);
		y=generar_aleat(2*margen,y_correspondiente(v,x,nv)-margen);
		
		agregar_ordenado(v_densificado,nv,x,y,j);
		
	}
	return v_densificado;
}

float ** crear_terreno ( size_t * n ) {
	* n = 0;

	const float terreno_estatico [][2]={
	{0 , 100} ,
	{ -1 , VENTANA_ALTO * 2.0 / 3} ,
	{ VENTANA_ANCHO , 100}
	};


	size_t nt = 3;
	float ** terreno = matriz_a_vector ( terreno_estatico , nt ) ;
	if ( terreno == NULL ) return NULL ;

	terreno [1][0] = rand () %VENTANA_ANCHO ;


	for ( size_t i = 1; i < 30; i ++) {
		float ** aux = densificar_vector ( terreno , nt , 2 * ( i + 5) , 100 / i ) ;
		destruir_vector ( terreno , nt , 2) ;
		if ( aux == NULL ) return NULL ;
		terreno = aux ;
		nt = 2 * ( i + 5) ;
	}

	* n = nt ;

	return terreno ;
}

float **coordenadas_aleatorias(size_t cantidad, float margenx, float margeny, float basex, float basey){
	
	float **coordenadas = pedir_memoria(cantidad, 2);
		if(!coordenadas){
			return NULL;
		}
	
	for(size_t i = 0; i < cantidad; i++){
				coordenadas[i][0] = generar_aleat(margenx, basex);
				coordenadas[i][1] = generar_aleat(margeny, basey);	
	}

	return coordenadas;
}