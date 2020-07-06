#ifndef _CINETICA_H_
#define _CINETICA_H_

/*Esta funcion recibe tres decimales dobles: una posicion inicial, una velocidad y una variacion de tiempo. Esta funcion devuelve un decimal doble que corresponde a la posicion final*/
double computar_posicion(double pi, double vi, double dt);

/*Esta funcion recibe tres decimales dobles: una velocidad inicial, una aceleracion y una variacion de tiempo. Esta funcion devuelve un decimal doble que corresponde a la velocidad final*/
double computar_velocidad(double vi, double a, double dt);

#endif // _CINETICA_H_
