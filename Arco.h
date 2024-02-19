#ifndef ARCO_H
#define ARCO_H
#include <iostream>

using namespace std;
/*
Esta clase representa el arco o la arista de un grafo.
Es la entidad que conecta dos nodos o vértices y que se le asigna un peso o distancia.(peso = cantidad de paquetes que soporta)
*/
class Arco
{
	private:
		int nodo_origen;		
		int nodo_destino;		
		int peso_arco;
	public:		
		Arco(int , int, int);
		~Arco();
		int origen();
		int destino();
		int peso();
		void mod_peso(int);//modifica el valor del peso del Arco.
		void imprimir();
};

#endif // ARCO_H
