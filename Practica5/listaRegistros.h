//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#ifndef listaRegistros_h
#define listaRegistros_h
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_REG = 10;

typedef struct{
	string id;
	bool leido;
}tRegistro;

typedef tRegistro *tRegistroPtr;

typedef struct{
	tRegistroPtr elementosReg;
	int cont;
	int dimension; //lleva la cuenta de la nueva dimension del array en caso de que necesitara mas hueco
}tListaRegistros;

/*Inicializa la lista*/
void inicializarLReg(tListaRegistros &listaReg, int capacidad);

/*Dado un flujo de archivo de entrada (ya abierto), lee 
los datos que corresponden a una lista de registros y la devuelve*/
void cargarReg(tListaRegistros &listaReg, ifstream& archivo);

/*Dado un flujo de archivo de salida (ya abierto),
guarda los datos de la lista de registro*/
void guardarReg(const tListaRegistros &listaReg, ofstream& archivo);

/*Dado un registro lo inserta al final de la lista.Si la lista esta 
llena, devuelve false, en otro caso devuelve true*/
bool insertar(tListaRegistros &listaReg, tRegistro registro);

/*Dado un identificador de correo, busca el registro correspondiente
y si lo encuentra, lo elimina de la lista. Si no lo encuentra, devuelve false*/
bool borrar(tListaRegistros &listaReg, string id);

/*Dado un identificador de correo, busca el correspondiente registro y pone
el indicador de leido a true*/
bool correoLeido(tListaRegistros &listaReg, string id);

/*Dado un identificador de correo y la lista, devuelve su posicion si existe.
En caso contrario, devuelve -1*/
int buscar(const tListaRegistros &listaReg, string id);

void destruirLReg(tListaRegistros &listaReg);

#endif