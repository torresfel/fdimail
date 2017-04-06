//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#include "Correo.h"

string mostrarFecha(tFecha fecha);
string mostrarSoloDia(tFecha fecha);
void vaciartCorreo(tCorreo &correo);

/*Función que pide una fecha y devuelve un string.*/
string mostrarFecha(tFecha fecha){
	stringstream aux;
	string hora_actual;

	tm ltm;
	localtime_s(&ltm, &fecha);

	aux << "<" << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon << "/" << ltm.tm_mday << ", " << ltm.tm_hour << ":" << ltm.tm_min << ":" << ltm.tm_sec << ">";
	hora_actual = aux.str();

	return hora_actual;
}

string mostrarSoloDia(tFecha fecha){
	stringstream resultado;
	tm ltm;
	localtime_s(&ltm, &fecha);
	resultado << 1900 + ltm.tm_year << "/" << 1 + ltm.tm_mon << "/" << ltm.tm_mday;
	return resultado.str();
}

void inicializaCorreo(tCorreo &correo){
	correo.asunto="";
	correo.destinatario="";
	correo.emisor="";
	correo.fecha=0;
	correo.identificador="";
	correo.texto="";
}

bool cargarCorreo(tCorreo &correo, ifstream& archivo){
	string cuerpo;
	bool ok = false;
	char aux;
	vaciartCorreo(correo);
	archivo >> correo.identificador;
	if (correo.identificador != ""){
		ok = true;
		archivo >> correo.fecha;
		archivo >> correo.emisor;
		archivo >> correo.destinatario;
		archivo.get(aux);
		getline(archivo, correo.asunto);
		getline(archivo, cuerpo);
		while (cuerpo != "X"){ //mientras que no se detecte el final del correo, seguimos cargando linea, guardandola en el string y leyendo la siguiente
			correo.texto = correo.texto + cuerpo + "\n";
			getline(archivo, cuerpo);
		}
	}
	else ok = false;
	return ok;
}

void guardarCorreo(const tCorreo &correo, ofstream& archivo){
	string aux1, aux2;
	int pos;
	archivo << correo.identificador << endl;
	archivo << correo.fecha << endl;
	archivo << correo.emisor << endl;
	archivo << correo.destinatario << endl;
	archivo << correo.asunto << endl;
	aux2 = correo.texto;//creamos un string auxiliar para poder trabajar con el correo.texto
	pos = aux2.find("\n");
	while (pos != -1){				
		aux1 = aux2.substr(0, pos); //guarda en un string auxiliar desde el principio hasta el salto de linea (\n)
		aux2.erase(0, (pos + 1));   //despues borra hasta el primer salto de linea que hemos encontrado antes
		archivo << aux1 << endl;    //a continuacion, guardamos el string que tiene el principio de aux2 hasta el primer salto de linea
		pos = aux2.find("\n");      //y por ultimo, buscamos el siguiente salto de linea (\n), y si no encuntra mas, devuelve pos = -1 y no seguimos en el while.
	} 
	archivo << "X" << endl;
}

void correoNuevo(tCorreo &correo, string emisor){
	stringstream stream;
	string cuerpo;
	system("cls");
	correo.emisor = emisor;
	cout << "Introduzca el destinatario: ";
	cin >> correo.destinatario;
	cout << "Asunto: ";
	cin.sync();
	getline(cin, correo.asunto);
	cout << "Texto ('-End-' para terminar):" << endl;
	cin.sync();
	getline(cin, cuerpo);
	while (cuerpo != "-End-"){
		correo.texto = correo.texto + cuerpo + "\n";
		getline(cin, cuerpo);
	}
	correo.fecha = time(0);
	stream << correo.emisor << "_" << correo.fecha;
	correo.identificador = stream.str();
}

void correoContestacion(const tCorreo &correoOriginal, tCorreo &correo, string emisor){
	stringstream stream;
	string cuerpo, aux;
	correo.emisor = emisor;
	correo.destinatario = correoOriginal.emisor;
	correo.asunto = "RE: " + correoOriginal.asunto;
	cout << "Asunto: " << correo.asunto << endl;
	cout << correoOriginal.texto << endl;
	correo.texto = correoOriginal.texto + "\n";
	cout << "Respuesta ('-End-' para terminar): ";
	cin.sync();
	getline(cin, cuerpo);
	while (cuerpo != "-End-"){
		correo.texto = correo.texto + cuerpo + "\n";
		getline(cin, cuerpo);
	}
	correo.fecha = time(0);
	stream << correo.emisor << "_" << correo.fecha;
	correo.identificador = stream.str();
}

string aCadena(const tCorreo &correo){
	stringstream stream;

	stream << "De: " << left << setw(53) << correo.emisor << right << setw(21) << mostrarFecha(correo.fecha) << endl;
	stream << "Para: " << correo.destinatario << endl;
	stream << "Asunto: " << correo.asunto << endl << endl;
	stream << correo.texto << endl;

	return stream.str();
}

string obtenerCabecera(const tCorreo &correo){
	stringstream stream;
	stream << left << setw(25) <<  correo.emisor << left << setw(35) << correo.asunto << right << setw(12) << mostrarSoloDia(correo.fecha) << endl;
	return stream.str();
}

void vaciartCorreo(tCorreo &correo){
	correo.asunto = "";
	correo.destinatario = "";
	correo.emisor = "";
	correo.identificador = "";
	correo.texto = "";
}