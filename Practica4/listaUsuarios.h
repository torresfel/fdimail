//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#ifndef listaUsuarios_h
#define listaUsuarios_h
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#include "Usuario.h"

const int MAX_USUARIOS = 5;

typedef tUsuario tArrayUsers[MAX_USUARIOS];

typedef struct{
	tArrayUsers elementos;
	int cont;
}tListaUsuarios;

/*Inicializa la lista*/
void inicializar(tListaUsuarios &usuarios);

/*Implementa la carga de la lista de usuarios desde el 
fichero de usuarios de nombre <NombreDominio>_usuarios.txt*/
bool cargarUsuarios(tListaUsuarios &usuarios, string dominio);

/*Implementa el guardado de la lista de usuarios desde el 
fichero de usuarios de nombre <NombreDominio>_usuarios.txt*/
void guardarUsuarios(const tListaUsuarios &usuarios, string dominio);

/*Añade un usuario en la posicion de la lista que le corresponde,
si hay sitio para ello. Ademas devuelve un booleano indicando si la
operacion ha tenido exito o no*/
bool aniadir(tListaUsuarios &usuarios, const tUsuario &usuario);

/*Dado un identificador de usuario y la lista, devuelve, si dicho identificador
existe en la lista, su posicion y el valor true, y si no existe en la lista, la 
posicion que le corresponderia y el valor false*/
bool buscarUsuario(const tListaUsuarios &usuarios, string id, int &pos);
#endif