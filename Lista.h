/*!Begin Snippet:filebegin*/
#ifndef _Lista_H_
#define _Lista_H_
#include <assert.h>
#include <iostream>
#include <vector>
#include <algorithm> // Para std::find
#include <iterator> // Para std::distanc

using namespace std;
template <typename T>
//implementacion CLASE LISTA
class Lista {
private:
public:

    Lista(const Lista<T>& src);  // constructor
    ~Lista(void);  // Destructor

    // constructor
    Lista(void) : inicio(NULL), final(NULL), cant_nodos(0) {}


    // Referencia al primer elemento &
    T& primer_elemento(void) {
        assert (inicio != NULL && "Lista vacia"); //abortara la ejecucion dle programa mientras: 1) inicio es un puntero a nulo y 2) mensaje de lista vacia
        return inicio->data; //&& es como una AND, ambas condiciones a la vez
    }

    // Referencia al ultimo elemento &
    T& ultimo_elemento(void) {
        assert (final != NULL); //aborta si final es un puntero nulo
        return final->data;
    }
    // Funcion para obetener el primer elemento, dotando de cualidad funcional
    T& begin() const {
        return inicio->data;
    }
    // Funcion para obetener el ultimo elemento, dotando de cualidad funcional
    T& end() const {
        return final->data;
    }

    // Returns cant_nodos of elements of list
    int tamanio(void) {
        return cant_nodos;
    }
    // Returns whether or not list contains any elements
    bool es_vacia(void) {
        return cant_nodos == 0;
    }
    //implementacion CLASE NODO, cuya clase amiga es LISTA, y puede acceder a elemento y siguiente.
    class Nodo {
        friend class Lista<T>;
    private:
        T data;
        Nodo* next;
    public:
        Nodo(T d, Nodo* n = NULL) : data(d), next(n) {}

        // Sobrecarga del operador de conversión de tipo
        operator T() const {
            return data;
        }
    };
    Nodo* inicio;  // Beginning of list
    Nodo* final;  // End of list
    int cant_nodos;    // Number of Nodos in list

    // Definir la clase interna iterator, cuya clase dota a Lista de la capacidad de ser iterable
    class iterator {
        // Atributo del iterador
        //friend class Nodo<T>;
        Nodo *current; // El puntero al nodo actual
    public:
        // Constructor del iterador
        iterator(Nodo *current = nullptr) : current(current) {}

        // Desreferenciar el iterador
        T &operator*() const {
            return current->data;
        }

        // Incrementar el iterador (prefijo)
        iterator &operator++() {
            current = current->next;
            return *this;
        }

        // Incrementar el iterador (sufijo)
        iterator operator++(int) {
            iterator temp = *this;
            current = current->next;
            return temp;
        }

        // Comparar dos iteradores por igualdad
        bool operator==(const iterator &other) const {
            return current == other.current;
        }

        // Comparar dos iteradores por desigualdad
        bool operator!=(const iterator &other) const {
            return current != other.current;
        }
    };

    // Devolver un iterador al primer elemento de la lista
    iterator begin() {
        return iterator(inicio);
    }

    // Devolver un iterador al final de la lista
    iterator end() {
        return iterator(nullptr);
    }
    /*!End Snippet:simple*/

    void insertar_al_principio(T);  // Insert element at beginning
    void insertar_al_final(T);   // Insert element at end
    void quitar_primer_nodo(void);  // Remove element from beginning
    void quitar_ultimo_nodo(void);  // Remove element from end

    void mostrar(void);  // Output contents of list
    void imprimir(void);
    void agregar(T);
    T& elemento_pos(int);
	
	void insertar_nodo_pos(T, int);
	void quitar_nodo_pos(int);
	void intercambiar_pos_nodos(int, int);
	bool contiene(T);
	void copiar_contenido(Lista<T>);

};

template <typename T>
void Lista<T>::copiar_contenido(const Lista<T> fuente){
	this->inicio=NULL;
	this->final=NULL;
	this->cant_nodos=0;
	Nodo* ptr_nodo_actual = fuente.inicio;
    while (ptr_nodo_actual != NULL) {
        this->insertar_al_final(ptr_nodo_actual->data);
        ptr_nodo_actual = ptr_nodo_actual->next;
    }
}

/*!Begin Snippet:copyconstructor*/
// Copy constructor
template <typename T>
Lista<T>::Lista(const Lista<T>& src) :
        inicio(NULL), final(NULL), cant_nodos(0) {

    Nodo* ptr_nodo_actual = src.inicio;
    while (ptr_nodo_actual != NULL) {
        this->insertar_al_final(ptr_nodo_actual->data);
        ptr_nodo_actual = ptr_nodo_actual->next;
    }

}
/*!End Snippet:copyconstructor*/

/*!Begin Snippet:destructor*/
// Destructor
template <typename T>
Lista<T>::~Lista(void) {

    while (! this->es_vacia()) {
        this->quitar_primer_nodo();
    }
}
/*!End Snippet:destructor*/

/*!Begin Snippet:pushprimer_elemento*/
// Insert an element at the beginning
template <typename T>
void Lista<T>::insertar_al_principio(T elemento) {
    Nodo* nva_inicio = new Nodo(elemento, inicio);
    if (this->es_vacia()) {
        inicio = nva_inicio;
        final = nva_inicio;
    } else {
        inicio = nva_inicio;
    }
    cant_nodos++;
}
/*!End Snippet:pushprimer_elemento*/

/*!Begin Snippet:pushultimo_elemento*/
// Insert an element at the end
template <typename T>
void Lista<T>::insertar_al_final(T elemento) {

    Nodo* nvo_final = new Nodo(elemento, NULL);

    if (this->es_vacia()) {
        inicio = nvo_final;
    } else {
        final->next = nvo_final;
    }

    final = nvo_final;
    cant_nodos++;
}
/*!End Snippet:pushultimo_elemento*/

/*!Begin Snippet:popprimer_elemento*/
// Remove an element from the beginning
template <typename T>
void Lista<T>::quitar_primer_nodo(void) {

    assert(inicio != NULL);

    Nodo* inicio_anterior = inicio;

    if (this->tamanio() == 1) {
        inicio = NULL;
        final = NULL;
    } else {
        inicio = inicio->next;
    }

    delete inicio_anterior;
    cant_nodos--;
}
/*!End Snippet:popprimer_elemento*/

/*!Begin Snippet:popultimo_elemento*/
// Remove an element from the end
template <typename T>
void Lista<T>::quitar_ultimo_nodo(void) {

    assert(final != NULL);

    Nodo* final_anterior = final;

    if (this->tamanio() == 1) {
        inicio = NULL;
        final = NULL;
    } else {

        // Traverse the list to Nodo just before final
        Nodo* ptr_nodo_actual = inicio;
        while (ptr_nodo_actual->next != final) {
            ptr_nodo_actual = ptr_nodo_actual->next;
        }

        // Unlink and reposition
        ptr_nodo_actual->next = NULL;
        final = ptr_nodo_actual;
    }

    delete final_anterior;
    cant_nodos--;
}
/*!End Snippet:popultimo_elemento*/

/*!Begin Snippet:printlist*/
// Display the contents of the list
template <typename T>
void Lista<T>::mostrar(void) {

    cout << "(";

    Nodo* ptr_nodo_actual = inicio;

    if (ptr_nodo_actual != NULL) {

        while (ptr_nodo_actual->next != NULL) {
            cout << ptr_nodo_actual->data << ", ";
            ptr_nodo_actual = ptr_nodo_actual->next;
        }
        cout << ptr_nodo_actual->data;
    }

    cout << ")" << endl;
}
template <typename T>
void Lista<T>::imprimir(void) {

    cout <<endl<< "x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl;

    Nodo* ptr_nodo_actual = inicio;

    if (ptr_nodo_actual != NULL) {

        while (ptr_nodo_actual->next != NULL) {
            ptr_nodo_actual->data.imprimir();
            cout<<endl;
            ptr_nodo_actual = ptr_nodo_actual->next;
        }
        ptr_nodo_actual->data.imprimir();
    }

    cout << endl<< "x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x-x"<<endl;
}
/*!End Snippet:printlist*/
template<typename T>
void Lista<T>::agregar(T elemento){
	this->insertar_al_final(elemento);
}
template <typename T>
T& Lista<T>::elemento_pos(int pos){
    assert (inicio != NULL && "La lista está vacía");
	assert (pos<=cant_nodos-1 && "Se intenta acceder a una nodo inexistente");

	Nodo* ptr_nodo_actual = inicio;
	int pos_actual=0;

       	while (pos_actual!=pos) {
		ptr_nodo_actual = ptr_nodo_actual->next;
		pos_actual++;			
       	}

        return ptr_nodo_actual->data;
}

template <typename T>
void Lista<T>::quitar_nodo_pos(int pos){

	assert((pos>=0) && "Se desea quitar un nodo con posicion inválida. pos > 0");
	assert((pos<=cant_nodos-1) && "Se desea quitar un nodo con posicion inválida. pos <=0");
	
	if(pos==0){
		this->quitar_primer_nodo();
	}
	else{
		if(pos==(this->tamanio()-1)){
			this->quitar_ultimo_nodo();
		}
		else{
			Nodo* ptr_nodo_actual = inicio;
			Nodo* ptr_nodo_anterior = NULL;
			int pos_actual=0;
       			while (pos_actual<pos) {
				ptr_nodo_anterior = ptr_nodo_actual;
				ptr_nodo_actual = ptr_nodo_actual->next;
				pos_actual++;			
       			}
			ptr_nodo_anterior->next=ptr_nodo_actual->next;
			delete ptr_nodo_actual;
			cant_nodos--;
		}
	}

}

template <typename T>
void Lista<T>::insertar_nodo_pos(T elemento, int pos){

	assert(pos>=0 && "Se desea insertar un nodo con posicion inválida.");
	assert(pos<=cant_nodos-1 && "Se desea insertar un nodo con posicion inválida.");
	
	if(pos==0){
		this->insertar_al_principio(elemento);
		return;
	}
	if(pos==cant_nodos-1){
		this->insertar_al_final(elemento);
		return;
	}
	Nodo* ptr_nodo_actual = inicio;
	Nodo* ptr_nodo_anterior = NULL;

	int pos_actual=0;

	while (pos_actual!=pos) {
		ptr_nodo_anterior = ptr_nodo_actual;
		ptr_nodo_actual = ptr_nodo_actual->next;
		pos_actual++;			
	}

	Nodo* nvo_nodo = new Nodo(elemento, ptr_nodo_actual);
	ptr_nodo_anterior->next=nvo_nodo;
	
	cant_nodos++;
}


template <typename T>
void Lista<T>::intercambiar_pos_nodos(int pos_1, int pos_2){
	assert((pos_1>=0 || pos_1<=cant_nodos-1) && "Se desea cambiar de posicion a un nodo con posicion inválida.");//
	assert((pos_2>=0 || pos_2<=cant_nodos-1) && "Se desea cambiar de posicion a un nodo hacia una posicion inválida.");//
	
	if((pos_1==0 && pos_2==cant_nodos-1) || (pos_1==cant_nodos-1 && pos_2==0)){
		Nodo* ptr_nodo_aux1=new Nodo(this->elemento_pos(0), NULL);
		Nodo* ptr_nodo_aux2=new Nodo(this->elemento_pos(cant_nodos-1), NULL);
		this->quitar_nodo_pos(0);
		this->insertar_al_final(ptr_nodo_aux1->data);
		this->quitar_nodo_pos(cant_nodos-2);
		this->insertar_al_principio(ptr_nodo_aux2->data);
	}
	else{
		if(pos_1!=pos_2){
		if(pos_1>pos_2){
			int aux=pos_1;
			pos_1=pos_2;
			pos_2=aux;
		}
		Nodo* ptr_nodo_aux1=new Nodo(this->elemento_pos(pos_1), NULL);
		Nodo* ptr_nodo_aux2=new Nodo(this->elemento_pos(pos_2), NULL);
		this->quitar_nodo_pos(pos_1);
		this->insertar_nodo_pos(ptr_nodo_aux1->data, pos_2);
		this->quitar_nodo_pos(pos_2-1);
		this->insertar_nodo_pos(ptr_nodo_aux2->data, pos_1);
		}
	}
}

template <typename T>
bool Lista<T>::contiene(T elemento){
	bool contenido = false ;
	Nodo* ptr_nodo_actual = inicio;

    while (ptr_nodo_actual != NULL) {
		//cout<<"CONTIENE: "<<ptr_nodo_actual->elemento<<" == "<<elemento<<endl;
		if(ptr_nodo_actual->data == elemento){
			contenido=true;
			//cout<<"CONTIENE_RES: "<<contenido<<endl;
			return contenido;
		}
		ptr_nodo_actual = ptr_nodo_actual->next;
	}
	//cout<<"CONTIENE_RES: "<<contenido<<endl;
	return contenido;
}

#endif
