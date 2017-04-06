//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#include "Gestor.h"

tCorreo devolverCorreo(const tListaCorreos &listaCorreos, const string id);
void dibujarCabecera(bool entrada);
int menuCorreoE();
int menuCorreoS();

bool arrancar(tGestor &gestor, string dominio){
	bool ok = false;
	gestor.numUsuarios = -1;
	inicializar(gestor.usuarios);
	if (cargarUsuarios(gestor.usuarios, dominio)){
		ok = true;
		if (cargarLCorreos(gestor.listaCorreos, dominio)){
			ok = true;
		}
	}
	else{
		cout << "No hay ningun usuario en la lista de texto" << endl;
		system("pause");
	}
	return ok;
}

void apagar(const tGestor &gestor){
	guardarUsuarios(gestor.usuarios, gestor.dominio);
	guardarLCorreos(gestor.listaCorreos, gestor.dominio);
}

bool crearCuenta(tGestor &gestor){
	tUsuario usuarioAux;
	bool ok = false;
	int pos;
	cout << "Introduzca email: ";
	cin >> usuarioAux.nombre;
	cout << "Contraseña: ";
	cin >> usuarioAux.contra;
	if (aniadir(gestor.usuarios, usuarioAux)){
		cout << "Usuario creado con exito!" << endl;
		if (buscarUsuario(gestor.usuarios, usuarioAux.nombre, pos)){
			gestor.numUsuarios = pos;
			ok = true;
		}
	}
	else{
		cout << "Usuario ya existente o lista llena" << endl;
	}
	return ok;
}

bool iniciarSesion(tGestor &gestor){
	tUsuario usuarioAux;
	string email, contra;
	bool ok = false;
	int pos;
	cout << "Introduzca email: ";
	cin >> usuarioAux.nombre;
	cin.sync();
	if (buscarUsuario(gestor.usuarios, usuarioAux.nombre, pos)){
		cout << "Introduzca contrasenia: ";
		cin >> contra;
		if (validarContra(gestor.usuarios.elementos[pos], contra)){
			ok = true;
			gestor.numUsuarios = pos;
		}
		else{
			cout << "Contraseña incorrecta" << endl;
		}
	}
	else{
		cout << "Usuario incorrecto" << endl;
	}
	return ok;
}

void enviarCorreo(tGestor &gestor, const tCorreo &correo){
	tRegistro registro;
	int pos;
	if (insertarLCorreos(gestor.listaCorreos, correo)){
		registro.id = correo.identificador;
		registro.leido = true;// como el mensaje ,al escribirlo, ya esta siendo leido, el booleano de leido se pone en true
		insertar(gestor.usuarios.elementos[gestor.numUsuarios].salida, registro);
		registro.leido = false;
		if (buscarUsuario(gestor.usuarios, correo.destinatario, pos)){
			if (!insertar(gestor.usuarios.elementos[pos].entrada, registro)) {
				cout << "Bandeja de " << correo.destinatario << " llena" << endl;
				system("pause");
			}
		}
	}
	else{
		cout << "Lista llena o correo ya existente" << endl;
	}
	system("cls");
}

void leerCorreo(tGestor &gestor, tListaRegistros &listaReg){
	tCorreo correo;
	tRegistro registro;
	int pos1, pos2, op; //pos 1 -> posicion que hace referencia al correo que se quiere leer\\ pos2 -> posicion en la que se encuentra el correo a buscar y leer
	cout << "Que correo quieres leer?: ";
	cin >> pos1; 
	if ((pos1 < listaReg.cont) && (pos1 > 0)){
		correo.identificador = listaReg.elementosReg[listaReg.cont - pos1].id;
		if (buscarLCorreos(gestor.listaCorreos, correo.identificador, pos2)){
			system("cls");
			cout << aCadena(gestor.listaCorreos.elementosCorreo[pos2]) << endl;
			listaReg.elementosReg[listaReg.cont - pos1].leido = true;
		}
		else{
			cout << "No se ha encontrado el correo a encontrar" << endl;
		}
		for (int i = 0; i < 80; i++){
			cout << "-";
		}
		cout << endl << "1- Contestar" << endl;
		cout << "0- Salir" << endl;
		cout << "Opcion: ";
		cin >> op;
		if (op == 1){
			correoContestacion(gestor.listaCorreos.elementosCorreo[pos2], correo, gestor.usuarios.elementos[gestor.numUsuarios].nombre);
			if (insertarLCorreos(gestor.listaCorreos, correo)){
				if (buscarUsuario(gestor.usuarios, correo.destinatario, pos2)){
					registro.id = correo.identificador;
					registro.leido = false;
					if (insertar(gestor.usuarios.elementos[pos2].entrada, registro)){
						registro.leido = true; // como el mensaje ,al escribirlo, ya esta siendo leido, el booleano de leido se pone en true
						if (insertar(gestor.usuarios.elementos[gestor.numUsuarios].salida, registro)) cout << "Exito al enviar!" << endl;
					}
				}
			}
		}
	}
	else{
		cout << "Correo inexistente. Vuelva a intentarlo." << endl;
		system("pause");
	}
}

void listaMensajes(const tGestor &gestor,bool entrada){ // si el booleano entrada esta en true, quiere decir que hemos solicitado la bandeja de ENTRADA. Si esta en falso, seria la bandeja de SALIDA
	tCorreo correo;
	string id;
	int pos, i = 1;
	bool leido = false;
	system("cls");
	cout << "Correo de " << gestor.usuarios.elementos[gestor.numUsuarios].nombre << endl;
	dibujarCabecera(entrada);
	if (!entrada){
		pos = gestor.usuarios.elementos[gestor.numUsuarios].salida.cont - 1;
	}else{
		pos = gestor.usuarios.elementos[gestor.numUsuarios].entrada.cont - 1;
	}
	while (pos >=0){
		if (!entrada) leido = gestor.usuarios.elementos[gestor.numUsuarios].salida.elementosReg[pos].leido;
		else leido = gestor.usuarios.elementos[gestor.numUsuarios].entrada.elementosReg[pos].leido;
		if (!leido){
			cout << "  ";
		}
		else{
			cout << "* ";
		}
		if (!entrada) id = gestor.usuarios.elementos[gestor.numUsuarios].salida.elementosReg[pos].id;
		else id = gestor.usuarios.elementos[gestor.numUsuarios].entrada.elementosReg[pos].id;
		cout << i << " - " << obtenerCabecera(devolverCorreo(gestor.listaCorreos, id));
		pos--;
		i++;
	}
	for (int i = 0; i < 80; i++){
		cout << "-";
	}
	cout << endl;
}

tCorreo devolverCorreo(const tListaCorreos &listaCorreos, const string id){ 
	tCorreo correo;
	int pos; 
	if (buscarLCorreos(listaCorreos, id, pos)){
		correo = listaCorreos.elementosCorreo[pos];
	}
	return correo;
}

void borrarCorreo(tGestor &gestor, tListaRegistros &listaReg){
	tCorreo correo;
	string id;
	int pos;
	cout << "Que correo desea borrar? (0 para no borrar ninguno): ";
	cin >> pos;
	if ((pos < listaReg.cont) && (pos > 0)){
		id = listaReg.elementosReg[listaReg.cont - pos].id;
		if (buscar(listaReg, id) != -1){
			if (borrar(listaReg, listaReg.elementosReg[listaReg.cont - pos].id)){
				cout << "Exito al borrar!" << endl;
			}
			else cout << "No se ha podido borrar" << endl;
			system("pause");
		}
		else{
				cout << "No se ha encontrado el correo a borrar" << endl;
				system("pause");
		}
	}else{
		if (pos != 0){
			cout << "Correo inexistente. Vuelva a intentarlo." << endl;
			system("pause");
		}
	}
}

bool arranqueMenu(tGestor &gestor){
	tCorreo correo;
	bool salir = false, entrada = true;
	int op;
	listaMensajes(gestor, entrada);
	op = menuCorreoE();
	switch (op){
	case 1:
		leerCorreo(gestor, gestor.usuarios.elementos[gestor.numUsuarios].entrada);
		break;
	case 2:
		if (gestor.usuarios.elementos[gestor.numUsuarios].salida.cont < MAX_REG){
			correoNuevo(correo, gestor.usuarios.elementos[gestor.numUsuarios].nombre);
			enviarCorreo(gestor, correo);
		}else{
			cout << "Bandeja de salida llena" << endl;
			system("pause");
		}
		break;
	case 3:
		borrarCorreo(gestor, gestor.usuarios.elementos[gestor.numUsuarios].entrada);
		break;
	case 4:
		entrada = false;
		listaMensajes(gestor, entrada);
		switch (menuCorreoS()){
		case 1:
			leerCorreo(gestor, gestor.usuarios.elementos[gestor.numUsuarios].salida);
			break;
		case 2:
			borrarCorreo(gestor, gestor.usuarios.elementos[gestor.numUsuarios].salida);
			break;
		}
		break;
	case 5:
		lecturaRapida(gestor, gestor.usuarios.elementos[gestor.numUsuarios].entrada);
		break;
	case 0:
		salir = true;
		break;
	}
	return salir;
}

void lecturaRapida(tGestor &gestor, tListaRegistros &listaReg){
	tCorreo correo;
	int pos;
	system("cls");
	for (int i = 0; i < listaReg.cont; i++){
		if (listaReg.elementosReg[i].leido == false){
			listaReg.elementosReg[i].leido = true;
			correo = devolverCorreo(gestor.listaCorreos, listaReg.elementosReg[i].id);
			do{
				pos = correo.asunto.find("RE: ");
				if (pos != -1) correo.asunto.erase(0, (pos + 4));
			} while (pos != -1);
			cout << aCadena(correo) << endl;
		}
	}
	system("pause");
}

void dibujarCabecera(bool entrada){
	for (int i = 0; i < 30; i++){
		cout << "-";
	}
	if (!entrada) cout << " Bandeja de salida ";
	else cout << " Bandeja de entrada";
	for (int i = 0; i < 31; i++){
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < 80; i++){
		cout << "-";
	}
	cout << "L N   " << left << setw(25) << "EMISOR" << left <<setw(35) << "ASUNTO" << right << setw(12) << "FECHA" << endl << endl;
	cout << endl;
	for (int i = 0; i < 80; i++){
		cout << "-";
	}
}

int menuCorreoE(){
	int op;
	cout << "Elija una opcion: " << endl;
	cout << "  1- Leer Correo" << endl;
	cout << "  2- Enviar Correo" << endl;
	cout << "  3- Borrar correo" << endl;
	cout << "  4- Ver bandeja de salida" << endl;
	cout << "  5- Lectura rapida de correos sin leer" << endl;
	cout << "  0- Cerrar sesion" << endl;
	for (int i = 0; i < 80; i++)cout << "-";
	cout << endl << "Introduzca una opcion: ";
	cin >> op;
	while ((op < 0) && (op > 6)){
		cout << "Introduzca de nuevo una opcion valida: ";
		cin >> op;
	}
	return op;
}

int menuCorreoS(){
	int op;
	cout << "Elija una opcion: " << endl;
	cout << "  1- Leer Correo" << endl;
	cout << "  2- Borrar correo" << endl;
	cout << "  0- Volver a la bandeja de entrada" << endl;
	for (int i = 0; i < 80; i++)cout << "-";
	cout << endl << "Introduzca una opcion: ";
	cin >> op;
	while ((op < 0) && (op > 3)){
		cout << "Introduzca de nuevo una opcion valida: ";
		cin >> op;
	}
	return op;
}
