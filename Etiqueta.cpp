#include "Etiqueta.h"

Etiqueta::Etiqueta(int router_destino, int router_despacho, int peso_trayecto){ // Constructor
	this->router_destino=router_destino;

	this->peso_trayecto=peso_trayecto;
}
Etiqueta::~Etiqueta(){
}
int Etiqueta::despacho(){
	return this->router_despacho;
}
int Etiqueta::destino(){
	return this->router_destino;
}
int Etiqueta::peso_total(){
	return this->peso_trayecto;
}
void Etiqueta::mod_peso_trayecto(int nvo_peso){
	this->peso_trayecto = nvo_peso;
}
void Etiqueta::mod_despacho(int nvo_router_despacho){
	this->router_despacho = nvo_router_despacho;
}
void Etiqueta::imprimir(){
	cout<<"                     ["<<this->router_destino<<"|"<<this->router_despacho<<"|"<<this->peso_trayecto<<"]"<< endl;
}

