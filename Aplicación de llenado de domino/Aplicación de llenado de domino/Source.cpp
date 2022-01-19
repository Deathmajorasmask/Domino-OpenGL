#include <iostream>
#include <fstream>
using namespace std;

struct piezas{
	int index;
	int subindex;
	int jug;
	piezas *sig;
	piezas*ant;
};
piezas * inicio=NULL;
piezas *aux;
fstream FileClose;
ifstream FileOpen;
static char direccion[] = "archivodomino.bin";

void main() {
	int op = 0;
	bool rep = true;
	
	while ( rep == true) {
		system("cls");
		cout << "1.-agregar" << endl;
		cout << "2.-guardar" << endl;
		cout << "3.-ver" << endl;
		cin >> op;


		if (op == 1) {
			//agregar
			piezas *nodo = new piezas;
			cout << "index" << endl;
			cin >> nodo->index;
			cout << "subindex" << endl;
			cin >> nodo->subindex;
			nodo->jug = 0;

			if (inicio == NULL) {
				inicio = nodo;
				inicio->sig = NULL;
				inicio->ant = NULL;
			}
			else {
				aux = inicio;
				while (aux->sig != NULL) {
					aux = aux->sig;
				}
				nodo->ant = aux;
				aux->sig = nodo;
				nodo->sig = NULL;

			}
		}
		else if (op == 2) {
			//guardar en archivo
			piezas * auxarch;
			FileClose.open(direccion, ios::out | ios::binary | ios::trunc);
			if (FileClose.is_open()) {
				auxarch = inicio;
				while (auxarch != NULL) {
					FileClose.write((char*)auxarch, sizeof(piezas));
					auxarch = auxarch->sig;
				}
				FileClose.close();
			} // Finalizar guardar 
		}
		else if(op==3) {
			piezas *auxarchpie = NULL;
			//recuperar lista ligada
			FileOpen.open(direccion, ios::binary);
			if (FileOpen.is_open()) {
				piezas * auxnuevocon = new piezas;
				FileOpen.read((char *)auxnuevocon, sizeof(piezas));
				while (!FileOpen.eof()) {
					auxnuevocon->sig = NULL;
					auxnuevocon->ant = NULL;
					if (inicio == NULL) {
						inicio = auxnuevocon;
					}
					else {
						auxarchpie = inicio;
						while (auxarchpie->sig != NULL) {
							auxarchpie = auxarchpie->sig;
						}
						auxarchpie->sig = auxnuevocon;
						auxnuevocon->ant = auxarchpie;
					}
					auxnuevocon = new piezas;
					FileOpen.read((char *)auxnuevocon, sizeof(piezas));
				}
				FileOpen.close();
			}
			else {
				cout << "Ocurrio un error la leer" << endl;
			}

		}
		else {
			rep = false;
		}


		system("pause");
	}
}