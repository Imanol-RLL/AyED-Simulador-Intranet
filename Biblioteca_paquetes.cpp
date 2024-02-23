#include "Biblioteca_paquetes.h"
//#include "Cola.h"
//#include "Paquete.h"
#include <iostream>
using namespace std;

Biblioteca_paquetes::Biblioteca_paquetes(int mi_rout)
	:clasificador(), mi_router(mi_rout){}
Biblioteca_paquetes::~Biblioteca_paquetes(){
}
int Biblioteca_paquetes::agregar_paquete(Paquete paq_recibido){
	bool hay_cat_router=false;
	bool hay_cat_pagina=false;
	int i,j;
	int router_destino = paq_recibido.obtener_ip_comp_destino()[0];

	if(clasificador.tamanio()>0){//Si el clasificador no está vacío.
		for(i=0 ; i<clasificador.tamanio() ; i++){
			if(clasificador.elemento_pos(i).obtener_duenio()==router_destino){
				hay_cat_router=true;
				break;
			}
		}
			if(hay_cat_router){//Si la categoría del clasificador en la posicion (i) tiene como dueño al router destino del paquete.
//Si el clasificador tiene la categoría para el router_destino del paquete en la posicion (i).
				for(j=0 ; j < clasificador.elemento_pos(i).tamanio() ; j++){
					if(clasificador.elemento_pos(i).elemento_pos(j).obtener_duenio()==paq_recibido.obtener_id_pagina()){
						hay_cat_pagina=true;
						break;
					}
				}
					if(hay_cat_pagina){//Si la categoría de páginas para tal router contiene una para la página del paquete.
            //Si el clasificador tiene la categoría para la página del paquete en la poscion (j) dentro de la categoría del router destino en la posición (i).
						//cout<<"hay paquetes para la pagina"<<paq_recibido.obtener_id_pagina()<<endl;
						clasificador.elemento_pos(i).elemento_pos(j).encolar(paq_recibido);
						if(paq_recibido.obtener_ip_comp_destino()[0]==mi_router && paq_recibido.obtener_tamanio_pagina()==clasificador.elemento_pos(i).elemento_pos(j).tamanio()){//Si el paquete tiene como destino mi_router y además completa una página.
							clasificador.elemento_pos(i).quitar_nodo_pos(j);
							return 1;
						}
						else{//Si el paquete NO venía para mi_router o NO se completo la página.
							return 0;
						}
					}
					else{//Si el clasificador NO tiene la categoría para la página del paquete. 
						//cout<<"agrega cat pag"<<endl;
						Cola<Paquete> paquetes_nva_pag(paq_recibido.obtener_id_pagina());
						paquetes_nva_pag.encolar(paq_recibido);
						clasificador.elemento_pos(i).encolar(paquetes_nva_pag);
						return 0;
					}
			}
			else{//Si el clasificador NO tiene la categoría para el router destino del paquete.
				//cout<<"agrega cat router"<<endl;
				Cola<Cola<Paquete> > paginas_nvo_router(router_destino);
				Cola<Paquete> paquetes_nva_pag(paq_recibido.obtener_id_pagina());
				paquetes_nva_pag.encolar(paq_recibido);
				paginas_nvo_router.encolar(paquetes_nva_pag);
				clasificador.encolar(paginas_nvo_router);
				return 0;
			}
	}
	else{//Si el clasificador ESTÁ VACÍO.
		Cola<Cola<Paquete> > paginas_nvo_router(router_destino);
		Cola<Paquete> paquetes_nva_pag(paq_recibido.obtener_id_pagina());
		paquetes_nva_pag.encolar(paq_recibido);
		paginas_nvo_router.encolar(paquetes_nva_pag);
		clasificador.encolar(paginas_nvo_router);
		return 0;
	}
	return 0;

}
Paquete Biblioteca_paquetes::obtener_paquete(){
	assert (clasificador.tamanio()>0 && "Se intenta obtener paquetes de la coleccion vacia");


    // Si el paquete pertenece a mi router, lo reencolocamos.
    if(clasificador.primer_elemento().obtener_duenio()==mi_router)
		clasificador.reencolar();

    // Obtenemos el paquete a enviar.
	Paquete paquete_envio = clasificador.primer_elemento().primer_elemento().primer_elemento();
	clasificador.primer_elemento().primer_elemento().desencolar();

    // Si la página no tiene más paquetes, la eliminamos.
	if(clasificador.primer_elemento().primer_elemento().es_vacia())//si la página no tiene más paquetes...
		clasificador.primer_elemento().desencolar();//Desencolo la página para ese router.
	else
		clasificador.primer_elemento().reencolar();

    // Si no hay más páginas para el router, lo eliminamos.
	if(clasificador.primer_elemento().es_vacia()){
        clasificador.desencolar();
    }
	else{
        clasificador.reencolar();
    }
	return paquete_envio;
}

void Biblioteca_paquetes::imprimir(int id_pag){
	for(int i=0;i<clasificador.tamanio();i++){
		for(int j=0;j<clasificador.elemento_pos(i).tamanio();j++){
			for(int k=0;k<clasificador.elemento_pos(i).elemento_pos(j).tamanio();k++){
				clasificador.elemento_pos(i).elemento_pos(j).elemento_pos(k).imprimir(id_pag);
				cout<<" ; ";
			}
		}
	}
}
int Biblioteca_paquetes::tamanio(){	
	int tam=0;
	for(int i=0;i<clasificador.tamanio();i++){
		for(int j=0;j<clasificador.elemento_pos(i).tamanio();j++){
			for(int k=0;k<clasificador.elemento_pos(i).elemento_pos(j).tamanio();k++){
				tam++;
			}
		}
	}
	return tam;
}

int Biblioteca_paquetes::destino_proa(){
	return clasificador.primer_elemento().obtener_duenio();
}

void Biblioteca_paquetes::reencolar_destino(){
	this->clasificador.reencolar();
}

int Biblioteca_paquetes::cant_destinos(){
	return this->clasificador.tamanio();
}

