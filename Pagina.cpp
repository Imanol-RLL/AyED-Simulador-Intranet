#include "Pagina.h"
#include <iomanip>
#define BOLD_RED     "\x1b[31;1m"
#define BOLD_BLUE    "\x1b[34;1m"
#define BOLD_GREEN   "\x1b[32;1m"
#define BOLD_CYAN    "\x1b[36;1m"
#define BOLD_YELLOW  "\x1b[33;1m"
#define BOLD_MAGENTA "\x1b[35;1m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_BRIGHT  "\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

using namespace std;

Pagina::Pagina(int id, int tamanio, vector<int> ip_comp_origen, vector<int> ip_comp_destino):id(id),tamanio(tamanio),ip_comp_origen(ip_comp_origen),ip_comp_destino(ip_comp_destino){}

Pagina::~Pagina()
{}

int Pagina::obtener_id(){
return this->id;
}

int Pagina::obtener_tamanio(){
return this->tamanio;
}

vector<int> Pagina::obtener_ip_comp_origen(){
return this->ip_comp_origen;
}

vector<int>  Pagina::obtener_ip_comp_destino(){
return this->ip_comp_destino;
}

void Pagina::imprimir(void) {
    // Encabezado con colores y linea divisoria
    std::cout << std::endl
              << ANSI_COLOR_BRIGHT << BOLD_GREEN
              << "-----------------------------------------------------------------------------"
              << ANSI_COLOR_RESET << std::endl;
    std::cout << BOLD_MAGENTA << ANSI_COLOR_BRIGHT << "PAGINA: " << this->obtener_id() << ANSI_COLOR_RESET << std::endl;
    std::cout << BOLD_GREEN << "-----------------------------------------------------------------------------"
              << ANSI_COLOR_RESET << std::endl;

    // Mostrar información de la página en forma de tabla
    std::cout << std::setw(10) << "Tamaño:" << std::setw(5) << this->obtener_tamanio() << " bytes " << std::endl;
    std::cout << std::setw(10) << "Origen:" << std::setw(15) << this->obtener_ip_comp_origen()[0] << ".." << this->obtener_ip_comp_origen()[1] << std::endl;
    std::cout << std::setw(10) << "Destino:" << std::setw(15) << this->obtener_ip_comp_destino()[0] << ".." << this->obtener_ip_comp_destino()[1] << std::endl;

    // Línea divisoria final
    std::cout << std::endl
              << ANSI_COLOR_BRIGHT << BOLD_GREEN
              << "-----------------------------------------------------------------------------"
              << ANSI_COLOR_RESET << std::endl;
}

