Trabajo Final AyED 
==========
Fecha: Febrero 2024

.

Para compilar

  `$ make`
  
Ejecute el programa:

  `$ \.final_AyED`

`cat Lista.h Cola.h Arco.h Arco.cpp Conexion.h Conexion.cpp Etiqueta.h Etiqueta.cpp Pagina.h Pagina.cpp Computadora.h Computadora.cpp Router.h Router.cpp Administrador.h Administrador.cpp main.cpp > Todo.cpp`

Descripción:

Este proyecto es un simulador de conexiones a una intranet, donde un administrador gestiona las conexiones mediante el algoritmo de Dijkstra. Las páginas se dividen en paquetes que se transmiten por routers hasta llegar a la computadora.

Características:

    Simulación realista: El simulador reproduce el comportamiento de una red.
    Algoritmo de Dijkstra: El simulador utiliza el algoritmo de Dijkstra para encontrar la ruta más eficiente entre dos puntos de la red.
    Potente motor C++: El simulador está diseñado en C++ para aprovechar al máximo la potencia de procesamiento del equipo.
    Compilación con Make: El proyecto se compila fácilmente con el comando make.
    Ejecución en Linux: El simulador se ejecuta en sistemas operativos Linux.
    Semilla aleatoria ambiental: El simulador utiliza la capacidad de Linux de obtener una muestra ambiental aleatoria como semilla para la generación de tráfico.

Beneficios:

    Herramienta educativa: El simulador es una herramienta ideal para aprender sobre el funcionamiento de las redes y el algoritmo de Dijkstra.
    Planificación de redes: El simulador puede utilizarse para planificar y optimizar redes reales.
    Resolución de problemas: El simulador puede utilizarse para identificar y resolver problemas de red.

Requisitos:

    Sistema operativo: Linux
    Compilador C++: GCC o Clang
    CMake

Instalación:

    Clonar el repositorio desde GitHub :

git clone https://github.com/Imanol-RLL/Simulador-Intranet.git

    Compilar el proyecto:

make

    Ejecutar el simulador:

./FinalAyED

Uso:

El simulador cuenta con una interfaz de línea de comandos intuitiva que facilita la gestión de las conexiones. Para más información sobre cómo usar el simulador, consulte la documentación:
![Diagrama simple y consiso, de la estructura del programa](/Diagram 2024-02-20 19-23-06.png "Diagrama UML")
Explicacion:

El simulador inicia en ./main.cpp. que mantiene una tarea activa como interfaz, donde permite iniciar la simulacion. seleccionar la pagina y revisar las conexiones, asi como terminar el simulador.
Un momento antes de entrar en este bucle activo. se carga el archivo ./conf.txt que contiene la configuracion de la red (recuerde que todas las intancias de router deben estar conectadas entre si como un grafo no dirigido).

En un siguiente paso, ya en el archivo `./Administrador.cpp` nos encontramos con las tareas principales de simulacion.
## 1) Crear la pagina web:
   La función `Administrador::crear_pagina()` implementa la lógica para crear una nueva página de forma aleatoria y enviarla a un router también aleatorio dentro de la red simulada. La función se encarga de generar:

   **Origen**: Un par de valores que representan la computadora origen de la página, seleccionando un router y una computadora conectada a este de forma aleatoria.
   
   **Destino**: Un par de valores que representan la computadora destino de la página, seleccionando un router y una computadora conectada a este de forma aleatoria, diferente al origen.
   
   **Tamaño**: Un valor aleatorio dentro del rango definido por TAM_MIN_PAG y TAM_MAX_PAG.

    **Generación de números aleatorios:**

    Se utiliza la función `srand() `para inicializar el generador de números aleatorios con una semilla obtenida del archivo `/dev/urandom.`
## 2) Disjktra:
La funcion Administrador::Dijkstra(int nodo_inicio)

### Algoritmo:

El código implementa el algoritmo de Dijkstra para encontrar la ruta más corta desde un nodo origen (nodo_inicio) a todos los demás nodos en una red. El algoritmo funciona de la siguiente manera:

**Inicialización:**
        Se crean dos listas: S y Q. S almacena los nodos ya procesados y Q almacena los nodos que aún no se han procesado.
        Se crea una lista de etiquetas que contiene información de cada nodo, como la distancia, el peso total del trayecto y el predecesor en la ruta más corta.
        Se inicializa la lista de predecesores (predecesores).
        Se agregan todos los nodos a la lista Q.
        Se inicializan las distancias a todos los nodos como infinito, excepto para el nodo origen que se inicializa como 0.

**Ciclo de procesamiento:**
        Mientras la lista Q no esté vacía:
            Se encuentra el nodo con la distancia mínima en la lista Q.
            Se elimina el nodo de la lista Q y se agrega a la lista S.
            Se actualiza la distancia y el predecesor de los nodos adyacentes al nodo elegido que no están en la lista S.

**Optimización**:
        Se utiliza una lista de adyacencia para acceder directamente a los arcos adyacentes a un nodo, evitando la necesidad de iterar sobre todos los arcos del grafo en cada iteración.

**Cálculo del despacho:**
        Se actualiza el campo de despacho en las etiquetas de acuerdo al predecesor de cada nodo.

**Impresión de resultados:**
        Se imprimen los predecesores y la tabla de enrutamiento para el nodo origen.

### **Estructuras de datos:**

**Lista:** Se utiliza una lista iterable para almacenar los nodos en las listas S, Q y adyacentes.

**Etiqueta:** Se define una estructura Etiqueta que contiene la información de cada nodo:

**id:** Identificador del nodo.
        distancia: Distancia mínima desde el nodo origen.
        peso_total: Peso total del trayecto desde el nodo origen.
        predecesor:Predecesor en la ruta más corta desde el nodo origen.
        despacho: Siguiente salto en la ruta.
**Vector:** Se utiliza un vector para almacenar la lista de predecesores.
    Mapa no ordenado: Se utiliza un mapa no ordenado (std::unordered_map) para almacenar la lista de adyacencia.

**Complejidad:**

La complejidad del algoritmo de Dijkstra es O(E log V), donde E es el número de arcos y V es el número de nodos en la red. La optimización con la lista de adyacencia puede mejorar la eficiencia del algoritmo en algunos casos.

## 3) Empaquetado de paginas:

La función Router::cargar_conexiones() se encarga de cargar los paquetes del organizador de paquetes del router en las conexiones de envío disponibles. La función funciona de la siguiente manera:

1. Inicialización:

   Se crea una lista para almacenar las conexiones saturadas (conexiones_saturadas).
   Se inicializan las variables carga_imposible, cant_rotaciones y despacho_req.

2. Bucle principal:

    Mientras que:
    Hay paquetes en el organizador de paquetes para enviar.
    
    Las conexiones no están saturadas. 
    No es imposible cargar los paquetes.
    
    Se busca el despacho del router para el destino que está en la proa del organizador de paquetes.
    
    Si el despacho está saturado o el destino es el mismo router:
    Se reencolan los destinos en el organizador de paquetes.
    Se incrementa el contador de rotaciones.
    
    Si el despacho no está saturado:
    Se recorren las conexiones de envío del router.
    Si se encuentra una conexión al router de despacho:
    Se carga el paquete en la conexión.
    Se reinicia el contador de rotaciones.
    Si la conexión se satura, se agrega el destino a la lista de conexiones saturadas.

3. Detección de imposibilidad de carga:

   Si el contador de rotaciones es igual al número de destinos en el organizador de paquetes, significa que no hay una ruta posible para enviar los paquetes.
   Si el organizador de paquetes solo tiene un paquete y el destino es el mismo router, también se considera imposible la carga.

4. Salida:

   La función termina cuando se han cargado todos los paquetes posibles o se ha detectado que la carga es imposible.


Este proyecto está licenciado bajo la licencia MIT.

Contacto:

Para cualquier pregunta o comentario, contacte con el autor del proyecto:

    Nombre: Rodriguez Llados Hernan
    Correo electrónico: imanol.rodriguez.llados@mi.unc.edu.ar



