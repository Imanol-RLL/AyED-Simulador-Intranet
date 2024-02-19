#include <iostream>
#include <sstream>
#include "Administrador.h"
#include <limits>

using namespace std;
int main(int argc, char **argv)
{
	Administrador admin; // crea el objeto administrador de red
// Imagen
    std::cout << "                                  \\" << std::endl;
    std::cout << "                                  `\,/" << std::endl;
    std::cout << "                                  .-'-." << std::endl;
    std::cout << "                                 '     `" << std::endl;
    std::cout << "                                 `.   .'" << std::endl;
    std::cout << "                          `._  .-~     ~-.   _,'" << std::endl;
    std::cout << "                           ( )'           '.( )" << std::endl;
    std::cout << "             `._    _       /               .'" << std::endl;
    std::cout << "              ( )--' `-.  .'                 ;" << std::endl;
    std::cout << "         .    .'        '.;                  ()" << std::endl;
    std::cout << "          `.-.`           '                 .' " << std::endl;
    std::cout << "----*-----;                                .' " << std::endl;
    std::cout << "          .`-'.           ,                `" << std::endl;
    std::cout << "         '    '.        .';                  ()" << std::endl;
    std::cout << "              (_)-   .-'  `.                 ;" << std::endl;
    std::cout << "             ,'   `-'       \               `" << std::endl;
    std::cout << "                           (_).           .'(_) " << std::endl;
    std::cout << "                          .'   '-._   _.-'    `" << std::endl;
    std::cout << "                                 .'   `" << std::endl;
    std::cout << "                                 '     ;" << std::endl;
    std::cout << "                                  `-,-' " << std::endl;
    std::cout << "                                   /`\\ " << std::endl;
    std::cout << "                                 /`" << std::endl;

    // Título principal
    cout << endl;
    cout << "**Simulación del Tráfico de Paquetes en una Red de Routers**" << endl;
    cout << "------------------------------------------------------" << endl;

    // Descripción del programa
    cout << endl;
    cout << "Este programa simula el tráfico de paquetes en una red de routers." << endl;
    cout << "El programa permite al usuario configurar la red y los paquetes," << endl;
    cout << "y luego simula el envío de los paquetes a través de la red." << endl;

    // Información del programa
    cout << endl;
    cout << "**Trabajo Final - AyED 2024**" << endl;
    cout << "**Autor:** Imanol Rodriguez" << endl;
    cout << "**Repositorio:** https://github.com/Imanol-RLL/AyED-Simulador-Intranet" << endl;

    // Fecha y créditos
    cout << endl;
    cout << "**FEBRERO 2024**" << endl;
    cout << "______________________________________________________" << endl;

    // Línea divisoria
    cout << endl;

	cout<<BOLD_BLUE<<"Configure la RED que desea simular modificando el archivo conf.txt que se encuentra en el mismo directorio que el ejecutable."<<endl;
	cout<<"Cuando termine presione ENTER."<<ANSI_COLOR_RESET<<endl;
	cin.get();
	admin.leer_archivo(); // lee el archivo de configuracion
	admin.probar_conf();  // Prueba la configuracion
	admin.dibujar_grafo(); // genera un png con el grafico
	cout<<BOLD_BLUE<<"Ingrese la cantidad de pasos a simular y presione ENTER. (Si se presiona enter sin especificar la cantidad de pasos se simulará un único paso.)"<<ANSI_COLOR_RESET<<endl;
    int comando;

    while (true) {
        // Mostrar menú de opciones
        cout << "1. Simular un paso" << endl;
        cout << "2. Simular una cantidad de pasos" << endl;
        cout << "3. Seleccione una id de pagina nueva" << endl;
        cout<< "4. Prueba de tabla de conexiones" << endl ;
        cout << "0. Salir" << endl;

        // Leer el comando del usuario
        cin >> comando;
        // Validar la entrada
        if (!cin || comando < 0 || comando > 4) {
            cout << BOLD_RED << ANSI_COLOR_BRIGHT << "ERROR: Comando no válido." << ANSI_COLOR_RESET << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        // Ejecutar la acción seleccionada
        switch (comando) {
            case 1:
                admin.simular_un_paso(true);
                break;
            case 2:
                int cantidad_pasos;
                cout << "Introduzca la cantidad de pasos a simular: ";
                cin >> cantidad_pasos;
                if (!cin || cantidad_pasos < 1) {
                    cout << BOLD_RED << ANSI_COLOR_BRIGHT << "ERROR: Cantidad de pasos inválida." << ANSI_COLOR_RESET << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
                admin.simular_cant_pasos(cantidad_pasos);
                break;
            case 0:
                cout << BOLD_GREEN << ANSI_COLOR_BRIGHT << "SIMULACIÓN TERMINADA" << ANSI_COLOR_RESET << endl;
                return 0;
            case 3:
                cout<<"Elija una página de las creadas para seguir el trayecto de sus paquetes.\nIngrese el id de la página:"<<endl;
                int pag;
                cin>>pag;
                admin.sel_pagina(pag);
                admin.simular_un_paso(true);
                break;
            case 4:
                admin.probar_conf();
                cout<<endl<<BOLD_CYAN<<"-----------------------------------------------PRUEBA CONFIGURACION--------------------------------------------"<<ANSI_COLOR_RESET<<endl;

        }
    }
	return 0;
}
