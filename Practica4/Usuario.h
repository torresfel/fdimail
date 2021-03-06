//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#ifndef Usuario_h
#define Usuario_h
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "listaRegistros.h"

typedef struct{
	string nombre;
	string contra;
	tListaRegistros entrada;
	tListaRegistros salida;
}tUsuario;

/*Dado un flujo de archivo, se carga un usuario de fichero*/
bool cargarUser(tUsuario &usuario, ifstream& archivo);

/*Dado un flujo de archivo, se guarda un usuario en fichero*/
void guardarUser(const tUsuario &usuario, ofstream& archivo);

/*Recibe un identificador de usuario y una contraseņa y los asigna al usuario*/
void inicializar(tUsuario &usuario, string id, string contra);

/*Recibe una contraseņa y un usuario y devuelve si la contraseņa es correcta o no*/
bool validarContra(const tUsuario &usuario, string contra);

#endif