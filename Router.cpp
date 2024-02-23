#include "Router.h"
#include <iomanip>

using namespace std;


Router::Router(int ip_router):ip(ip_router), // Constructor
        computadoras(),
        tabla_enrutamiento(),
        organizador_paquetes(ip_router),
        conexiones_envio(),
        conexiones_recepcion(){}


Router::~Router(){ // Destructor
}

void Router::recibir_pagina(Pagina pagina_recibida){
	for(int i=0;i<pagina_recibida.obtener_tamanio();i++){
		this->organizador_paquetes.agregar_paquete(Paquete(pagina_recibida.obtener_ip_comp_origen(),
                                                           pagina_recibida.obtener_ip_comp_destino(),
                                                           pagina_recibida.obtener_id(),
                                                           pagina_recibida.obtener_tamanio(),i));
	}
}

void Router::recibir_paquetes(){
	//cout<<"Router::recibir_paquetes()"<<endl;
	this->leer_conexiones();
}

void Router::leer_conexiones(){
	for(int i=0; i<conexiones_recepcion.tamanio(); i++){
		//cout<<"conexion nro:"<<i<<" libre?: "<<conexiones_recepcion.elemento_pos(i)->conexion_libre()<<endl;
		while(!conexiones_recepcion.elemento_pos(i)->conexion_libre()){//Mientras que la conexión en la posición i de la lsita de conexiones no esté libre...
			Paquete paq_leido=conexiones_recepcion.elemento_pos(i)->leer();//esta instruccion terminará por liberar la conexion y finalizar el while.
			bool pag_completa=this->organizador_paquetes.agregar_paquete(paq_leido);
			if(pag_completa){//si estan todos los paquetes de una página para este router
				Pagina pag_construida = this->construir_pagina(paq_leido);//en la realidad la computadora se encarga de generar la pagina
				//cout<<"PAGINA CONTRUIDA ID: "<<pag_construida.obtener_id()<<endl;
				this->enviar_pagina(pag_construida);
			}
		}
	}
}

Pagina Router::construir_pagina(Paquete paq_leido){
	Pagina pag(paq_leido.obtener_id_pagina(),
               paq_leido.obtener_tamanio_pagina(),
               paq_leido.obtener_ip_comp_origen(),
               paq_leido.obtener_ip_comp_destino());
	cout<<"PÁGINA ID: "<<paq_leido.obtener_id_pagina()<<" CONSTRUIDA EN R"<<this->ip<<endl;
	return pag;
}//Devuelve una página con la informaxión del paquete paq_leido.

void Router::enviar_pagina(Pagina pag_cons){
	for(int i=0; i<computadoras.tamanio();i++){//recorre la lista de punteros a computadoras y le envia la página a la maquina apuntada que tiene el mismo ip que el destino de la página.
		if(computadoras.elemento_pos(i).obtener_ip() == pag_cons.obtener_ip_comp_destino())
				computadoras.elemento_pos(i).recibir_pagina(pag_cons);
	}
}

void Router::enviar_paquetes(){
	this->cargar_conexiones();
	
}

void Router::cargar_conexiones(){
	Lista<int> conexiones_saturadas;
	bool carga_imposible=false;
	int cant_rotaciones=0;
	int despacho_req=-1;
	while(organizador_paquetes.cant_destinos()>0 && conexiones_saturadas.tamanio()<conexiones_envio.tamanio() && !carga_imposible){//mientras hayan paquetes en el organizador para envío y las conexiones no esten saturadas
		despacho_req=this->buscar_en_tabla(this->organizador_paquetes.destino_proa());
		//cout<<"ENVIO DESDE R"<<this->ip<<" DESTINO PROA: "<<organizador_paquetes.destino_proa()<<" DESPACHO:"<<despacho_req<<endl;
		//this->tabla_enrutamiento.imprimir();
		//cout<<"CONEXIONES SATURADAS: "<<endl;
		//conexiones_saturadas.mostrar();

		if(conexiones_saturadas.contiene(despacho_req) || this->organizador_paquetes.destino_proa()==this->ip){
			this->organizador_paquetes.reencolar_destino();
			cant_rotaciones++;
		}
		else{
            int i = 0;
			while(i<conexiones_envio.tamanio()){//este ciclo recorre todas las conexiones del router en busca de aquella que lo conecta con el router de despacho para el paquete en la proa del organizador.
			//cout<<"Conexión (destino): "<<conexiones_envio.elemento_pos(i)->destino()<< "--SAT?-- "<<conexiones_envio.elemento_pos(i)->conexion_saturada()<<endl;
                const auto& conexion = conexiones_envio.elemento_pos(i);
				if(conexion->destino() == despacho_req){
					conexion->cargar(organizador_paquetes.obtener_paquete());
					cant_rotaciones=0;
					if(conexion->conexion_saturada()){
						conexiones_saturadas.agregar(conexion->destino());
					}
                    break;
				}
                i++;
			}
		}
		if(cant_rotaciones==organizador_paquetes.cant_destinos())
			carga_imposible=true;
		if(this->organizador_paquetes.tamanio()==1 && this->organizador_paquetes.destino_proa() == this->ip)
			carga_imposible=true;
	}
}

int Router::buscar_en_tabla(int destino){
	//cout<<"Tamanio de tabla: "<<tabla_enrutamiento.tamanio()<<endl;
	//tabla_enrutamiento.imprimir();
	for(int i=0;i<tabla_enrutamiento.tamanio();i++){
		if(tabla_enrutamiento.elemento_pos(i).destino() == destino)
			return tabla_enrutamiento.elemento_pos(i).despacho();
	}
	assert(0 && "Router::buscar_en_tabla -> \"No se encontró la etiqueta para el destino del paquete.\"");
}

void Router::mostrar_paquetes(int id_pag) {
    // Encabezado con colores y linea divisoria
    std::cout << std::endl
              << ANSI_COLOR_BRIGHT << BOLD_CYAN
              << "-----------------------------------------------------------------------------"
              << ANSI_COLOR_RESET << std::endl;
    std::cout << BOLD_MAGENTA << ANSI_COLOR_BRIGHT << "Router " << this->ip << ":"
              << BOLD_BLUE << ANSI_COLOR_BRIGHT << " Cantidad de paquetes: "
              << this->organizador_paquetes.tamanio() << ANSI_COLOR_RESET
              << std::endl;
    std::cout << BOLD_GREEN << "/-\\/_\\/-\\     /-\\/_\\/-\\    /-\\/_\\/-\\"
              << ANSI_COLOR_RESET << std::endl;

    // Mostrar información del router y sus paquetes
    std::cout << std::setw(5) << "--->  R" << this->ip << ":" << std::endl;
    this->organizador_paquetes.imprimir(id_pag);

    // Línea divisoria final
    std::cout << std::endl
              << ANSI_COLOR_BRIGHT << BOLD_GREEN
              << "-----------------------------------------------------------------------------"
              << ANSI_COLOR_RESET << std::endl;
}

void Router::agregar_conexion_envio(Conexion* con){
	this->conexiones_envio.agregar(con);
}

void Router::agregar_conexion_recepcion(Conexion* con){
	this->conexiones_recepcion.agregar(con);
}

int Router::obtener_ip(){
	this->computadoras.tamanio();
	return this->ip;
}

int Router::total_paquetes(){
	return this->organizador_paquetes.tamanio();
}

void Router::actualizar_tabla(Lista<Etiqueta> nva_tabla){
	//Lista<Etiqueta> tabla = nva_tabla;
	//cout<<"000000000000000000000000000000000000000000"<<endl;
	//nva_tabla.imprimir();
	this->tabla_enrutamiento.copiar_contenido(nva_tabla);
	//tabla_enrutamiento.imprimir();
	//cout<<"111111111111111111111111111111111111111111"<<endl;
}

void Router::agregar_computadora(Computadora esta){
	computadoras.agregar(esta);
}
void Router::imprimir(){
	cout<<"ROUTER: "<<this->ip<<endl;
	for(int i=0;i<computadoras.tamanio();i++){
		cout<<"COMPUTADORA: ("<<computadoras.elemento_pos(i).obtener_ip()[0]<<"|"<<computadoras.elemento_pos(i).obtener_ip()[1]<<")"<<endl;
	}
	for(int j=0;j<conexiones_recepcion.tamanio();j++){
		cout<<"CONEXIONES_RECEPCION: "<<endl;
		conexiones_recepcion.elemento_pos(j)->imprimir();
		//cout<<endl<<conexiones_recepcion.elemento_pos(j);
		cout<<endl;
	}
	for(int m=0;m<conexiones_recepcion.tamanio();m++){
		cout<<"CONEXIONES_ENVIO: "<<endl;
		conexiones_envio.elemento_pos(m)->imprimir();
		//cout<<endl<<conexiones_envio.elemento_pos(m);
		cout<<endl;
	}
}
