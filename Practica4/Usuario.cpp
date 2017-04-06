//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#include "Usuario.h"
#include "listaRegistros.h"

bool cargarUser(tUsuario &usuario, ifstream& archivo){
	bool ok = false;
	archivo >> usuario.nombre;
	if (usuario.nombre != "XXX"){
		ok = true;
		archivo >> usuario.contra;
		cargarReg(usuario.entrada, archivo);
		cargarReg(usuario.salida, archivo);
	}
	return ok;
}

void guardarUser(const tUsuario &usuario, ofstream& archivo){
	archivo << usuario.nombre << endl;
	archivo << usuario.contra << endl;
	guardarReg(usuario.entrada, archivo);
	guardarReg(usuario.salida, archivo);
}

void inicializar(tUsuario &usuario, string id, string contra){
	usuario.nombre = id;
	usuario.contra = contra;
	inicializarLReg(usuario.entrada);
	inicializarLReg(usuario.salida);
}

bool validarContra(const tUsuario &usuario, string contra){
	bool correcto = false;
	if (usuario.contra == contra) correcto = true;
	return correcto;
}