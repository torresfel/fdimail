//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#include"listaCorreos.h"

bool operator< (tCorreo correoIzq, tCorreo correoDer);
int redondearN1(int numero);
void redimensionarLCorreos(tListaCorreos &listaCorreos, int capacidad);

int redondearN1(int numero){
	int redondeado, aux;
	aux = numero / 10 + 1;
	redondeado = 10 * aux;
	return redondeado;
}

void inicializarLCorreos(tListaCorreos &listaCorreos, int capacidad){
	listaCorreos.cont = 0;
	listaCorreos.elementosCorreo = new tCorreo[capacidad];
	listaCorreos.dimension = capacidad;
}

bool cargarLCorreos(tListaCorreos &listaCorreos, string dominio){
	tCorreo correo;
	bool cargar = true;
	string nombArch;
	ifstream archivo;
	int num, aux; //aux coge el numero de correos que hay
	nombArch = dominio + "_ListaCorreo.txt";
	archivo.open(nombArch);
	if (!archivo.is_open()){
		cargar = false;
		inicializarLCorreos(listaCorreos, MAX_CORREOS);
	}
	else{
		archivo >> aux;
		num = redondearN1(aux);
		inicializarLCorreos(listaCorreos, num);
		for (int i = aux; i >= 0; i--) {
			if (cargarCorreo(correo, archivo)) {
				insertarLCorreos(listaCorreos, correo);
			}
		}
		archivo.close();
	}
	return cargar;
}
void guardarLCorreos(const tListaCorreos &listaCorreos, string dominio){
	ofstream archivo;
	archivo.open(dominio + "_ListaCorreo.txt");
	archivo << listaCorreos.cont << endl;
	for (int i = 0; i < listaCorreos.cont; i++){
		guardarCorreo(listaCorreos.elementosCorreo[i], archivo);
	}
	archivo.close();
}

bool insertarLCorreos(tListaCorreos &listaCorreos, const tCorreo &correo){
	int pos;
	bool ok = false;
	if (listaCorreos.cont >= listaCorreos.dimension){
		int nCapacidad = (listaCorreos.dimension * 3) / 2 + 1;
		redimensionarLCorreos(listaCorreos, nCapacidad);
	}
	if (!buscarLCorreos(listaCorreos, correo.identificador, pos)){
		ok = true;
		if (listaCorreos.cont != 0){
			for (int i = (listaCorreos.cont - 1); i >= pos; i--){ //desplaza todos los correos desde la posicion que le corresponde una casilla hacia la derecha
				listaCorreos.elementosCorreo[i + 1] = listaCorreos.elementosCorreo[i];
			}
		}
		listaCorreos.elementosCorreo[pos] = correo;
		listaCorreos.cont++;
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

void ordenar_AF(tListaCorreos &listaCorreos){
	tCorreo correoAux;                        
	bool inter = true;                        
	int i = 0;
	while ((i < listaCorreos.cont - 1) && inter) {
		inter = false;
		for (int j = listaCorreos.cont - 1; j > i; j--) {
			if (listaCorreos.elementosCorreo[j].asunto < listaCorreos.elementosCorreo[j - 1].asunto) { //Haciendo las pruebas, me dice que "Hola"(72) < "arturo sospecha"(97)
				correoAux = listaCorreos.elementosCorreo[j];
				listaCorreos.elementosCorreo[j] = listaCorreos.elementosCorreo[j - 1];
				listaCorreos.elementosCorreo[j - 1] = correoAux;
				inter = true;
			}
			else if (listaCorreos.elementosCorreo[j].asunto == listaCorreos.elementosCorreo[j - 1].asunto) {
				if (listaCorreos.elementosCorreo[j] < listaCorreos.elementosCorreo[j - 1]) {
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

bool operator< (tCorreo correoIzq, tCorreo correoDer){
	return(correoIzq.fecha < correoDer.fecha);
}

void destruirLCorreos(tListaCorreos &listaCorreos){
	delete [] listaCorreos.elementosCorreo;
	listaCorreos.elementosCorreo = NULL;
	listaCorreos.cont = 0;
	listaCorreos.dimension = 0;
}

void redimensionarLCorreos(tListaCorreos &listaCorreos, int capacidad){
	tCorreoPtr aux = new tCorreo[capacidad];
	for (int i = 0; i < listaCorreos.cont; i++){
		aux[i] = listaCorreos.elementosCorreo[i];
	}
	delete[] listaCorreos.elementosCorreo;
	listaCorreos.elementosCorreo = aux;
	listaCorreos.dimension = capacidad;
}