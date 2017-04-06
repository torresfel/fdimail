//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#ifndef gestor_h
#define gestor_h
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "listaUsuarios.h"
#include "listaCorreos.h"

typedef struct{
	string dominio;
	tListaCorreos listaCorreos;
	tListaUsuarios usuarios;
	int numUsuarios;
}tGestor;

/*Inicializa el gestor e intenta arrancarlo cargando la informacion del dominio que se le pasa como parametro.
Para ello inicializara y cargara la lista de usuarios y de correos de dicho dominio. Si tiene exito en todas
las operaciones devuelve true y si alguna falla, devuelve false*/
bool arrancar(tGestor &gestor, string dominio);

/*Esta operacion apaga el gestor y guarda para ello las listas de usuarios
y de correos del dominio que se encontrase activo en ese momento*/
void apagar(tGestor &gestor);

/*Lee los datos de usuario necesarios para crear una cuenta (id y contraseña) y si el id de usuaio no existe
y hay espacio en la lista de usuarios, crea la cuenta del usuario y registra al nuevo usuario como usuario 
activo en el gestor. Devuelve un booleano indicando si la operacion tuvo exito*/
bool crearCuenta(tGestor &gestor);

/*Lee los datos de usuario necesarios para validar la cuenta (id y contraseña) y si el usuario existe y la contraseña 
coincide, registra al usuario como usuario activo. Devuelve un booleano indicando si la operacion tuvo exito*/
bool iniciarSesion(tGestor &gestor);

/*Solicita el correo que el usuario quiere leer (sera el numero con el que el correo es mostrado por pantalla en la bandeja 
correspondiente), valida que existe y si es asi, lo marca como correo leido. A continuacion, busca el correo en la lista de 
correos y si lo encuentra lo muestra en la pantalla de lectura del correo*/
void leerCorreo(tGestor &gestor, tListaRegistros &listaReg);

/*Este subprograma implementa el envio del correo en nuestra aplicacion. Para ello el correo recibido como parametro es insertado 
en la lista de correo. Si ha habido exito, entonces se inserta el registro correspondiente en la lista de registros enviados al emisor 
y se intenta insertar igualmente un registro de dicho correo en la lista de registros recibidos del destinatario del correo. Si el 
destinatario no existe o si su bandeja de entrada esta llena, entonces se mostrara un mensaje de error*/
void enviarCorreo(tGestor &gestor, const tCorreo &correo);

/*Este subprograma implementa el borrado del correo de una bandeja de un determinado usuario. Para ello, solicita 
el correo que el usuario quiere borrar (sera el numero con el que el correo es mostrado por pantalla en la bandeja 
correspondiente), valida que existe y si es asi, procede a borrarlo*/
void borrarCorreo(tGestor &gestor, tListaRegistros &listaReg);

/*Este subprograma implementa la lectura rapida de correos sin leer. El resultado es que miestra en una pantalla todos los correos sin
leer ordenados por asunto (ignorando todos los Re:) y por fecha. Al finalizar su ejecucion los correos sin leer quedaran marcados como leidos*/
void lecturaRapida(tGestor &gestor, tListaRegistros &listaReg);

/*Funcion que muestra por pantalla la bandeja de entrada/salida*/
void listaMensajes(const tGestor &gestor, bool entrada);

/*Funcion que muestra por pantalla la bandeja de entrada/salida y elige entre las opciones escritas*/
bool arranqueMenu(tGestor &gestor);
#endif