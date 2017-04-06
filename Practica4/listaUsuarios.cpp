//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#include "listaUsuarios.h"

void inicializar(tListaUsuarios &usuarios){
	usuarios.cont = 0;
	for (int i = 0; i < MAX_USUARIOS; i++){
		usuarios.elementos[i].nombre = "";
		usuarios.elementos[i].contra = "";
		inicializarLReg(usuarios.elementos[i].entrada);
		inicializarLReg(usuarios.elementos[i].salida);
	}
}

bool cargarUsuarios(tListaUsuarios &usuarios, string dominio){
	tUsuario usuario;
	ifstream archivo;
	string nombArch = dominio + "_usuarios.txt";
	bool ok = false, aux = false; //aux es un booleano auxiliar que nos dice si el cargar el usuario solicitado ha tenido exito o no
	archivo.open(nombArch);
	if (archivo.is_open()){
		ok = true;
		aux = cargarUser(usuario, archivo);
		while (aux){
			usuarios.elementos[usuarios.cont] = usuario;
			usuarios.cont++;
			aux = cargarUser(usuario, archivo);
		}
	}
	archivo.close();
	return ok;
}

void guardarUsuarios(const tListaUsuarios &usuarios, string dominio){
	ofstream archivo;
	string nombArch = dominio + "_usuarios.txt";
	archivo.open(nombArch);
	for (int i = 0; i < usuarios.cont; i++){
		guardarUser(usuarios.elementos[i], archivo);
	}
	archivo << "XXX";
	archivo.close();
}

bool aniadir(tListaUsuarios &usuarios, const tUsuario &usuario){
	int pos;
	bool ok = false;
	if ((usuarios.cont < MAX_USUARIOS) && (!buscarUsuario(usuarios, usuario.nombre, pos))){
		ok = true;
		if (usuarios.cont != 0){ //esta condicion esta en el caso de que no haya ningun usuario en la lista de usuarios, asi que se inserta en la primera posicion del array
			for (int i = (usuarios.cont - 1); i >= pos; i--){ 
				usuarios.elementos[i + 1] = usuarios.elementos[i];
			}
		}
		usuarios.elementos[pos] = usuario;
		usuarios.cont++;
		inicializarLReg(usuarios.elementos[pos].entrada);
		inicializarLReg(usuarios.elementos[pos].salida);
	}
	return ok;
}

bool buscarUsuario(const tListaUsuarios &usuarios, string id, int &pos){
	int ini = 0, fin = (usuarios.cont - 1), mitad;
	bool encontrado = false;
	if (fin == -1){ // en caso de estar la lista de usuarios vacia, el contador de usuarios es 0, y no hace falta buscar la posicion que le corresponde
		pos = 0;
	}
	else{
		while ((ini <= fin) && !encontrado) {
			mitad = (ini + fin) / 2;
			if (id == usuarios.elementos[mitad].nombre) {
				encontrado = true;
				pos = mitad;
			}
			else if (id < usuarios.elementos[mitad].nombre) {
				fin = mitad - 1;
			}
			else {
				ini = mitad + 1;
			}
			if (!encontrado) pos = ini;
		}
	}
	return encontrado;
}