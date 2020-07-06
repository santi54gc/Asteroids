#include <stdio.h>
#include "cinetica.h"

double computar_posicion(double pi, double vi, double dt){

       return vi*dt+pi;
}

double computar_velocidad(double vi, double a, double dt){

       return a*dt+vi;
}
