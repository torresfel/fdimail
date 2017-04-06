//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#ifndef Correo_h
#define Correo_h
#include <iostream>
#include <sstream>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

//Constantes y Prototipos 
typedef time_t tFecha;

typedef struct {
	string emisor;
	string destinatario;
	string asunto;
	string texto;
	tFecha fecha;
	string identificador;
}tCorreo;


//Prototipos 

//Funcion que inicializa tcorreos
void inicializaCorreo(tCorreo &correo);

//Funcion que recibe un identificador de emisor y devuelve un correo con todos sus datos rellenos
void correoNuevo(tCorreo &correo,string emisor);

/*Funcion que recibe un identificador de emisor y el correo original que se va a contestar,
y devuelve un correo con todos sus datos rellenos*/
void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor);

/*Funcion que devuelve un string con el
contenido completo del correo para poderlo mostrar por consola.*/
string aCadena(const tCorreo &correo);

/*Funcion que devuelve un string que contiene la información que se mostrará en la bandeja de entrada/salida:
emisor, asunto y fecha sin hora*/
string obtenerCabecera(const tCorreo &correo);

/*Funcion lee los datos que corresponden a un correo y lo
devuelve. Devuelve false sólo si el correo cargado no es válido.*/
bool cargarCorreo(tCorreo &correo, ifstream& archivo);

/*Funcion que escribe en el flujo los datos que
corresponden a un correo.*/
void guardarCorreo(const tCorreo &correo, ofstream& archivo);
#endif