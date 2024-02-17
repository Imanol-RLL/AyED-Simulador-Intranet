#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H
//#include <iostream>
//#include <string>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Lista.h"
#include "Etiqueta.h"
#include "Paquete.h"
#include "Conexion.h"
#include "Pagina.h"
#include "Router.h"
#include "Computadora.h"

using namespace std;
/*
 * La clase Administrador se encarga de la simulacion, maneja los parametros de la red y gestiona
 * las computadoras, conexiones y routers.
 * por medio de Dijkstra (implementacion funcional.) calcula los caminos optimos de los paquetes
 * Tiene capacidad de dibujado en Dot.
*/

class Administrador
{
	private:
		Lista<Router> routers;
		Lista<Arco> arcos;
		Lista<Conexion*> conexiones;
		int cant_comp_por_router;
		int cant_routers;
		int total_pag;
		int cant_pasos;
		int pag_sel;
	public:
		Administrador();
		~Administrador();
		void simular_cant_pasos(int);
		void simular_un_paso(bool);
		Lista<Etiqueta> Dijkstra(int);
		void calcular_tablas();
		void leer_archivo();
		//void crear_conexiones();
		int dibujar_grafo();
		void crear_pagina();
		void probar_conf();
        void sel_pagina(int);
};
#endif // Paquete_H

