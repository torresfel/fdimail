//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#include"listaCorreos.h"

bool operator< (tCorreo correoIzq, tCorreo correoDer);

void inicializarLCorreos(tListaCorreos &listaCorreos){
	listaCorreos.cont=0;
	for(int i =0;i<MAX_CORREOS;i++){
		inicializaCorreo(listaCorreos.elementosCorreo[i]);
	}
}

bool cargarLCorreos(tListaCorreos &listaCorreos, string dominio){
	tCorreo correo;
	bool cargar=false;
	string nombArch;
	ifstream archivo;
	inicializarLCorreos(listaCorreos);
	nombArch = dominio + "_ListaCorreo.txt";
	archivo.open(nombArch);

	while (cargarCorreo(listaCorreos.elementosCorreo[listaCorreos.cont], archivo)){ //en el momento que cargue el "XXX" no seguiriamos cargando mas correos.
		listaCorreos.cont++;
		cargar = true; 
	}
	archivo.close();
	return cargar;
}
void guardarLCorreos(const tListaCorreos &listaCorreos, string dominio){
	ofstream archivo;
	archivo.open(dominio + "_ListaCorreo.txt");
	for (int i = 0; i < listaCorreos.cont; i++){
		guardarCorreo(listaCorreos.elementosCorreo[i], archivo);
	}
	archivo << "XXX";
	archivo.close();
}

bool insertarLCorreos(tListaCorreos &listaCorreos, const tCorreo &correo){
	int pos;
	bool ok = false;
	if ((listaCorreos.cont < MAX_CORREOS) && (!buscarLCorreos(listaCorreos, correo.identificador, pos))){
		ok = true;
		for (int i = (listaCorreos.cont - 1); i >= pos; i--){ //desplaza todos los correos desde la posicion que le corresponde una casilla hacia la derecha
			listaCorreos.elementosCorreo[i + 1] = listaCorreos.elementosCorreo[i];
		}
		listaCorreos.cont++;
		listaCorreos.elementosCorreo[pos] = correo;
	}
	return ok;
}

bool buscarLCorreos(const tListaCorreos &listaCorreos, string id, int &pos){ //busqueda binaria
	int ini = 0, fin = (listaCorreos.cont - 1), mitad;
	bool encontrado = false;
	while ((ini <= fin) && !encontrado) {
		mitad = (ini + fin) / 2;
		if (id == listaCorreos.elementosCorreo[mitad].identificador) {
			encontrado = true;
			pos = mitad;
		}
		else if (id < listaCorreos.elementosCorreo[mitad].identificador) {
			fin = mitad - 1;
		}
		else {
			ini = mitad + 1;
		}
	} 
	if (!encontrado) pos = ini;
	return encontrado;
}

void ordenar_AF(tListaCorreos &listaCorreos){ // como en el enunciado no se explica si se ordena primero por asunto o por fecha, y en caso de ser iguales, por el otro dato sobrante,
	tCorreo correoAux;                        // nos ha parecido logico ordenarlo primero por fecha, y en caso de que fueran enviados en la misma fecha, por asunto.
	bool inter = true;                        // En caso de ser al reves, solo hay que cambiar las siguientes condiciones:
	int i = 0;
	while ((i < listaCorreos.cont - 1) && inter) {
		inter = false;
		for (int j = listaCorreos.cont - 1; j > i; j--) {
			if (listaCorreos.elementosCorreo[j].fecha < listaCorreos.elementosCorreo[j - 1].fecha) { // Aqui, en vez de ".fecha", se pondria ".asunto"
				correoAux = listaCorreos.elementosCorreo[j];
				listaCorreos.elementosCorreo[j] = listaCorreos.elementosCorreo[j - 1];
				listaCorreos.elementosCorreo[j - 1] = correoAux;
				inter = true;
			}
			else if (listaCorreos.elementosCorreo[j].fecha == listaCorreos.elementosCorreo[j - 1].fecha) { // Aqui, en vez de ".fecha", se pondria ".asunto"
				if (listaCorreos.elementosCorreo[j] < listaCorreos.elementosCorreo[j]) { // En este caso, ir a la funcion bool operator<
					correoAux = listaCorreos.elementosCorreo[j];
					listaCorreos.elementosCorreo[j] = listaCorreos.elementosCorreo[j - 1];
					listaCorreos.elementosCorreo[j - 1] = correoAux;
					inter = true;
				}
			}
		}
		if (inter) {
			i++;
		}
	}
}

bool operator< (tCorreo correoIzq, tCorreo correoDer){ // Si quieres ordenar por asunto y luego por fecha los correos, solo hace falta cambiar ".asunto" por ".fecha"
	return(correoIzq.asunto < correoDer.asunto);
}