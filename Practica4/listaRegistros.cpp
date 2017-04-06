//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#include "listaRegistros.h"

void inicializarReg(tRegistro &registro);

void inicializarLReg(tListaRegistros &listaReg){
	listaReg.cont = 0;
	for (int i = 0; i < MAX_REG; i++){
		inicializarReg(listaReg.elementosReg[i]);
	}
}

void cargarReg(tListaRegistros &listaReg, ifstream& archivo){
	tRegistro registro;
	int numCorreos;
	inicializarLReg(listaReg);
	archivo >> numCorreos;
	for (int i = numCorreos; i > 0; i--){
		archivo >> registro.id;
		archivo >> registro.leido; //1-> Leido\\0-> No leido
		listaReg.elementosReg[listaReg.cont] = registro;
		listaReg.cont++;
	}
}

void guardarReg(const tListaRegistros &listaReg, ofstream& archivo){
	archivo << listaReg.cont << endl;
	for (int i = 0; i < listaReg.cont; i++){
		archivo << listaReg.elementosReg[i].id << " " << listaReg.elementosReg[i].leido << endl;
	}
}

bool insertar(tListaRegistros &listaReg, tRegistro registro){
	bool ok = false;
	if (listaReg.cont >= MAX_REG){
		ok = false;
	}
	else{
		ok = true;
		listaReg.elementosReg[listaReg.cont] = registro;
		listaReg.cont++;
	}
	return ok;
}

bool borrar(tListaRegistros &listaReg, string id){
	bool ok = false;
	int pos = buscar(listaReg,id);
	if (pos != -1){
		ok = true;
		for (int i = pos; i < listaReg.cont; i++){
			listaReg.elementosReg[pos] = listaReg.elementosReg[pos + 1];
		}
		listaReg.cont--;
	}
	return ok;
}

bool correoLeido(tListaRegistros &listaReg, string id){
	bool ok = false;
	int pos = buscar(listaReg, id);
	if (pos != -1) {
		ok = true;
		listaReg.elementosReg[pos].leido = true;
	}
	return ok;
}

int buscar(const tListaRegistros &listaReg, string id){
	int ini = 0, fin = (listaReg.cont - 1), mitad, pos;
	bool encontrado = false;
	while ((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2;
		if (id == listaReg.elementosReg[mitad].id) {
			encontrado = true;
			pos = mitad;
		}
		else if (id < listaReg.elementosReg[mitad].id) {
			fin = mitad - 1;
		}
		else {
			ini = mitad + 1;
		}
		if (!encontrado) pos = -1;
	}
	return pos;
}

void inicializarReg(tRegistro &registro){
	registro.id = "";
	registro.leido = false;
}