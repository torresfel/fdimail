//Jose Luis Moreno Varillas y Desiree Vetencourt Rosas G33-1B
#include "gestor.h"

int menuInicio(bool cargar);

int main(){
	tGestor gestor;
	tCorreo correo;
	string dominio = "pepe.com";
	int op;
	bool ok = false, salir = false, cargar = false;
	gestor.dominio = dominio;
	cargar = arrancar(gestor, gestor.dominio);
		do{
			op = menuInicio(cargar);
			switch (op){
			case 1:
				ok = iniciarSesion(gestor);
				if (!ok){
					cout << "Error en el inicio de sesion. Vuelva a intentarlo" << endl;
					system("pause");
				}
				break;
			case 2:
				ok = crearCuenta(gestor);
				if (!ok){
					system("pause");
				}
				break;
			}
		} while ((!ok) && (op != 0));
		if (op != 0){
			while (!salir){
				salir = arranqueMenu(gestor);
			}
		}
		apagar(gestor);
		system("pause");
	return 0;
}

int menuInicio(bool cargar){
	int op;
	system("cls");
	if (cargar){
		cout << "1- Iniciar sesion" << endl;
		cout << "2- Crear nueva cuenta" << endl;
		cout << "0- Salir" << endl;
		cout << "Opcion: ";
		cin >> op;
		while ((op < 0) && (op > 3)){
			system("cls");
			cout << "Opcion no disponible. Vuelve a intentarlo" << endl;
			cout << "1- Iniciar sesion" << endl;
			cout << "2- Crear nueva cuenta" << endl;
			cout << "0- Salir" << endl;
			cout << "Opcion: ";
			cin >> op;
		}
	}
	else{ //establecemos otro menu en caso de que no haya nadie en las listas de usuarios, y no saldria la opcion de iniciar sesion. Solo crear nueva cuenta
		cout << "1- Crear nueva cuenta" << endl;
		cout << "0- Salir" << endl;
		cout << "Opcion: ";
		cin >> op;
		while ((op < 0) && (op > 2)){
			system("cls");
			cout << "Opcion no disponible. Vuelve a intentarlo" << endl;
			cout << "1- Crear nueva cuenta" << endl;
			cout << "0- Salir" << endl;
			cout << "Opcion: ";
			cin >> op;
		}
		if (op == 1) op = 2;
	}
	return op;
}