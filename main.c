#include <SDL2/SDL.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "config.h"
#include "vectores.h"
#include "graficador.h"
#include "nave.h"
#include "listas.h"
#include "asteroide.h"
#include "disparo.h"

int main() {
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	SDL_CreateWindowAndRenderer(VENTANA_ANCHO, VENTANA_ALTO, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Asteroids");

	int dormir = 0;

	// BEGIN código del alumno
	srand(time(NULL));
	graficador_inicializar("sprites.bin", renderer);
	
	bool partida = false;
	bool nave_existe = true;
	float contador;

	nave_t* nave = nave_crear();
	if(nave == NULL) return EXIT_FAILURE;
	nave_inicializar(nave, NAVE_X_INICIAL, NAVE_Y_INICIAL, NAVE_VX_INICIAL, NAVE_VY_INICIAL, NAVE_ANGULO_INICIAL, NAVE_POTENCIA_INICIAL);	
	

	int vidas = CANT_VID_INICIAL, score = 0, high_score = 0, cant_asteroides = CANT_AST_INICIAL;
		
	lista_t* asteroides_lista = lista_crear();
	if(asteroides_lista == NULL) return EXIT_FAILURE;
	lista_t* disparos_lista = lista_crear();
	if(asteroides_lista == NULL) return EXIT_FAILURE;

	for(size_t i = 0; i < cant_asteroides; i++)
		lista_insertar_final(asteroides_lista, asteroide_crear(2 % rand() * VENTANA_ANCHO, 2 % rand() * VENTANA_ALTO, 32));

	const float estrella[11][2] = {{0,1},{-0.25,0},{-1,0},{-0.25,-0.5},{-1,-1.5},{0,-1},{1,-1.5},{0.25,-0.5},{1,0},{0.25,0},{0,1}};
	float **estrellas = matriz_a_vector(estrella, 11);
	if(estrellas == NULL) return EXIT_FAILURE;

	
	float **ubicacion_estrellas = coordenadas_aleatorias(CANT_ESTRELLAS,VENTANA_ANCHO,VENTANA_ALTO,0,0);
	if(ubicacion_estrellas==NULL) return EXIT_FAILURE;
	
	// END código del alumno

	unsigned int ticks = SDL_GetTicks();
	while(1) {
		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				break;
	    		if (event.type == SDL_KEYDOWN) {
				// BEGIN código del alumno
				switch(event.key.keysym.sym) {
					case SDLK_UP:

						if(nave_existe && partida)
							nave_impulsar(nave, NAVE_IMPULSO_PASO);
						
						break;

					case SDLK_SPACE:
						
						partida = true;
						if(nave_existe && partida)
							lista_insertar_comienzo(disparos_lista, disparo_generar(nave_obtener_x(nave), nave_obtener_y(nave), nave_obtener_angulo(nave)));


						break;

					case SDLK_RIGHT:

						if(nave_existe && partida)
							nave_rotar(nave, -NAVE_ROTACION_PASO);
						break;

					case SDLK_LEFT:

						if(nave_existe && partida)
							nave_rotar(nave, NAVE_ROTACION_PASO);
						break;
				}
				// END código del alumno


			}
			continue;
		}
        	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        	SDL_RenderClear(renderer);
        	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x00);


		// BEGIN código del alumno
		if(partida){


			lista_iterador_t *iterador;

			//Elimina los disparos a los que se le acabo el tiempo de vida
			lista_t* disparos_muertos = lista_filtrar_disparo(disparos_lista, disparo_vivo);
			lista_destruir_disparo(disparos_muertos);

			//Saca a los asteroides que chocaron con la nave
			if(nave_existe){

				lista_t * ast_colision = lista_filtrar_asteroide(asteroides_lista, asteroide_colision, nave_obtener_x(nave), nave_obtener_y(nave));

		        	iterador = lista_iterador_crear(ast_colision);
				if(iterador==NULL) return EXIT_FAILURE;

				for(; !lista_iterador_termino(iterador); lista_iterador_siguiente(iterador)){
	
					if(asteroide_obtener_radio(lista_iterador_actual(iterador)) > 8){

						lista_insertar_final(asteroides_lista, asteroide_dividido(lista_iterador_actual(iterador)));
						lista_insertar_final(asteroides_lista, asteroide_dividido(lista_iterador_actual(iterador)));
			
					}
					vidas -= 1;
					nave_existe = false;
					contador = 0;	
				} 

				lista_iterador_destruir(iterador);

				lista_destruir_asteroide(ast_colision);
			}

			iterador = lista_iterador_crear(disparos_lista);
			if(iterador==NULL) return EXIT_FAILURE;

			for(; !lista_iterador_termino(iterador); lista_iterador_siguiente(iterador)){
		
				
				lista_t * ast_colision = lista_filtrar_asteroide(asteroides_lista, asteroide_colision, disparo_obtener_x(lista_iterador_actual(iterador)), disparo_obtener_y(lista_iterador_actual(iterador)));

				
				lista_iterador_t* iterador2 = lista_iterador_crear(ast_colision);
				if(iterador2==NULL) return EXIT_FAILURE;
				
				for(; !lista_iterador_termino(iterador2); lista_iterador_siguiente(iterador2)){


					if(asteroide_obtener_radio(lista_iterador_actual(iterador2)) == 32) score += 20;
					if(asteroide_obtener_radio(lista_iterador_actual(iterador2)) == 16) score += 50;
					if(asteroide_obtener_radio(lista_iterador_actual(iterador2)) == 8) score += 100;

					if(asteroide_obtener_radio(lista_iterador_actual(iterador2)) > 8){

						lista_insertar_final(asteroides_lista, asteroide_dividido(lista_iterador_actual(iterador2)));
						lista_insertar_final(asteroides_lista, asteroide_dividido(lista_iterador_actual(iterador2)));

					}
				} 
				lista_destruir_asteroide(ast_colision);
				lista_iterador_destruir(iterador2);
			}
			
			lista_iterador_destruir(iterador);
		
			iterador = lista_iterador_crear(disparos_lista);
			if(iterador==NULL) return EXIT_FAILURE;

			for(; !lista_iterador_termino(iterador); lista_iterador_siguiente(iterador)){

				disparo_mover(lista_iterador_actual(iterador), DT);
				disparo_dibujar(lista_iterador_actual(iterador));

			} 

			lista_iterador_destruir(iterador);


			iterador = lista_iterador_crear(asteroides_lista);
			if(iterador==NULL) return EXIT_FAILURE;

			for(; !lista_iterador_termino(iterador); lista_iterador_siguiente(iterador)){

				asteroide_mover(lista_iterador_actual(iterador), DT);
				asteroide_dibujar(lista_iterador_actual(iterador));
			} 

			lista_iterador_destruir(iterador);


			if(nave_existe){
				nave_mover(nave, DT);
				nave_dibujar(nave);
			}

			else{

				lista_t * check = lista_filtrar_asteroide(asteroides_lista, asteroide_colision, NAVE_X_INICIAL, NAVE_Y_INICIAL);

				if(contador >= 1 && lista_es_vacia(check)){
					nave_existe = true;
					nave_inicializar(nave, NAVE_X_INICIAL, NAVE_Y_INICIAL, NAVE_VX_INICIAL, NAVE_VY_INICIAL, NAVE_ANGULO_INICIAL, NAVE_POTENCIA_INICIAL);
				}
				lista_extender(asteroides_lista, check);
				lista_destruir_asteroide(check);
			}

			contador += DT;

			if(lista_es_vacia(asteroides_lista)){

				cant_asteroides += 2;
				for(size_t i = 0; i < cant_asteroides; i++)
					lista_insertar_final(asteroides_lista, asteroide_crear(randf()*VENTANA_ANCHO, 0, 32));
			}
		
			for(size_t i = 0; i < CANT_ESTRELLAS; i++){
				dibujar(estrellas,ubicacion_estrellas[i][0], ubicacion_estrellas[i][1], 11, 1);
			}	

		}

		char cadena[8];
		sprintf(cadena,"%4i", high_score);
		dibujar_cadena(cadena, 2, 450, 750);
		sprintf(cadena,"%4i", score);
		dibujar_cadena(cadena, 3, 100, 750);
		
		for(int i = 0; i < vidas; i++)
			graficador_dibujar("SHIP", 1, 105 + 20 * i, 725, PI / 2);
		

		if(vidas <= 0){

			if(high_score < score) high_score = score;
			dibujar_cadena("GAME OVER", 4, 390, 500);
			dibujar_cadena(cadena, 4, 440, 450);

			lista_destruir_asteroide(asteroides_lista);
			lista_destruir_disparo(disparos_lista);
			
			dormir = 2000;
			vidas = CANT_VID_INICIAL;
			score = 0;
			partida = false;
			cant_asteroides = CANT_AST_INICIAL;
			nave_inicializar(nave, NAVE_X_INICIAL, NAVE_Y_INICIAL, NAVE_VX_INICIAL, NAVE_VY_INICIAL, NAVE_ANGULO_INICIAL, NAVE_POTENCIA_INICIAL);	

			asteroides_lista = lista_crear();
			if(asteroides_lista==NULL) return EXIT_FAILURE;
			disparos_lista = lista_crear();
			if(disparos_lista==NULL) return EXIT_FAILURE;
			for(size_t i = 0; i < cant_asteroides; i++)
				lista_insertar_final(asteroides_lista, asteroide_crear(2 % rand() * VENTANA_ANCHO, 2 % rand() * VENTANA_ALTO, 32));
		}
		// END código del alumno


        	SDL_RenderPresent(renderer);
		ticks = SDL_GetTicks() - ticks;
		if(dormir) {
			SDL_Delay(dormir);
			dormir = 0;
		}
		else if(ticks < 1000 / JUEGO_FPS)
			SDL_Delay(1000 / JUEGO_FPS - ticks);
		ticks = SDL_GetTicks();
	}

	// BEGIN código del alumno
	nave_destruir(nave);
	lista_destruir_asteroide(asteroides_lista);
	lista_destruir_disparo(disparos_lista);
	destruir_vector(estrellas,11,2);
	destruir_vector(ubicacion_estrellas,CANT_ESTRELLAS,2);
	graficador_finalizar();
	// END código del alumno

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}

