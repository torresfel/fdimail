//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#include "listaUsuarios.h"


bool cargarUsuarios(tListaUsuarios &usuarios, string dominio){
	tUsuario usuario;
	ifstream archivo;
	string nombArch = dominio + "_Usuarios.txt";
	bool ok = false, aux = false; //aux es un booleano auxiliar que nos dice si el cargar el usuario solicitado ha tenido exito o no
	int pos;
	usuarios.cont = 0;
	archivo.open(nombArch);
	if (archivo.is_open()){
		aux = cargarUser(usuario, archivo);
		while (aux){
			ok = true;
			aniadir(usuarios, usuario); //lo que nos devuelva nos es indiferente
			aux = cargarUser(usuario, archivo);
		}
	}
	archivo.close();
	return ok;
}

void guardarUsuarios(const tListaUsuarios &usuarios, string dominio){
	ofstream archivo;
	string nombArch = dominio + "_Usuarios.txt";
	archivo.open(nombArch);
	for (int i = 0; i < usuarios.cont; i++){
		guardarUser(*usuarios.elementos[i], archivo);
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
		usuarios.elementos[pos] = new tUsuario(usuario);
		usuarios.cont++;
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
			if (id == usuarios.elementos[mitad]->nombre) {
				encontrado = true;
				pos = mitad;
			}
			else if (id < usuarios.elementos[mitad]->nombre) {
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

void destruirUsuarios(tListaUsuarios &usuarios){
	for (int i = 0; i < usuarios.cont; i++){
		destruirLReg(usuarios.elementos[i]->entrada);
		destruirLReg(usuarios.elementos[i]->salida);
		delete usuarios.elementos[i];
	}
	usuarios.cont = 0;
}