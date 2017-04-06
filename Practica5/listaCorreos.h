//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#ifndef listaCorreos_h
#define listaCorreos_h

#include "Correo.h"

//Estructuras y Constantes
const int MAX_CORREOS = 10;

typedef tCorreo *tCorreoPtr;

typedef struct{
	tCorreoPtr elementosCorreo;
	int cont;
	int dimension; //lleva la cuenta de la nueva dimension del array en caso de que necesitara mas hueco
}tListaCorreos;

//Prototipos

//Funcion que inicializa la lista de correos
void inicializarLCorreos(tListaCorreos &listaCorreos, int capacidad);

/*Funcion que carga los correos en la lista desde el fichero de correos de nombre
<NombreDominio>_correos.txt y devuelve un boolean si se cargo o no*/
bool cargarLCorreos(tListaCorreos &listaCorreos, string dominio);

/*Funcion que implementa el guardado de la lista de correos en el fichero de correos de
nombre <NombreDominio>_ correos.txt . Guarda en fichero la lista de correos.
El nombre del fichero será como en el subprograma anterior*/
void guardarLCorreos(const tListaCorreos &listaCorreos, string dominio);

/*Fucion que dado un correo, si hay espacio en la lista, lo coloca en la posición de la lista que
le corresponda de acuerdo con su identificador y devuelve true. Si no lo ha
podido colocar devuelve false.*/
bool insertarLCorreos(tListaCorreos &listaCorreos, const tCorreo &correo);

/*Funcion que dado un identificador de correo y la lista, devuelve, si dicho identificador existe
en la lista, su posición y el valor true, y si no existe en la lista, la posición que le
correspondería y el valor false.*/
bool buscarLCorreos(const tListaCorreos &listaCorreos, string id, int &pos);

/*Funcion que dada una lista de correos la
devuelve ordenada por asunto y fecha. Como es una clave de ordenación doble,
habrá que redefinir el operador de comparación en el módulo que corresponda.*/
void ordenar_AF(tListaCorreos &listaCorreos);

void destruirLCorreos(tListaCorreos &listaCorreos);

#endif
