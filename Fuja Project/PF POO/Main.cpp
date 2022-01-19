#include<Windows.h>
//#include <GL/glew.h>
#include <gl\GLU.h>
#include <gl\GL.h>
#include "Scene.h"
#include <time.h>
#include "GamePadRR.h"
#include<fstream>		//Archivos
#include <stdlib.h>     //srand, rand 
//#pragma comment (lib, "glew32.lib") 
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib") 


//Para estadistica
piezas*estaaux = NULL;
jugador *estjug1=NULL, *estjug2 = NULL;
char ora[100] = "Tiene 1 probabilidad sobre:", bufffer[50], contin[]=" equivale a ";
float conta = 1,totprob=0, FilJ1=1, FilJ2 = 1;

piezas *auxarchpie=NULL;
//PAra repartir
piezas *auxrepant,*auxrepsig;

#define Timer1 100

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void DefPixelFormat(HDC hDC);
string obtenerDireccion(string filename);
ifstream FileOpen;
static string direccion = obtenerDireccion("archivodomino.bin");
//static char direccion[] = "archivodomino.bin";

HDC hContextoVentana;
Scene *scene;
GamePadRR *gamPad;
bool renderiza = false;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwndVentana;
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX); //Tamaño en bytes de la estructura.
	wc.style = CS_HREDRAW | CS_VREDRAW; //Entero de 16 bits que codifica el estilo de la clase de ventana.
	wc.lpfnWndProc = WindowProc;//Apunta al procedimiento de ventana.
	wc.hInstance = hInstance;//Identifica la instancia de la ventana a la que esta clase pertenece.
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//Identificador del curso de la clase. Debe ser un manipulador de un recurso de tipo icono. Si es Null, la aplicación mostrará un icono cuando el usuario minice la ventana de la aplicación.
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW; //Identificador del pincel para la clase.
	wc.lpszClassName = "Domino"; //Especifica el nombre de la clase ventana.
	RegisterClassEx(&wc);//Registra una clase de ventana para su uso subsecuente en llamadas a las funciones CreateWindow o CreateWindowEx
	RECT wr = { 0, 0, 1080, 720 };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);//Calcula el tamaño necesario del rectángulo de la ventana.

	//Se crea la ventana definida previamente.
	hwndVentana = CreateWindowEx(NULL,//estilo extendido de ventana
		"Domino",//puntero al nombre de la clase registrada *visto arriba*
		"Domino",//puntero al nombre de la ventana
		WS_OVERLAPPEDWINDOW,//estilo de ventana
		100,//posición horizontal de la ventana
		100,//posición vertical de la ventana
		wr.right - wr.left,//ancho de la ventana
		wr.bottom - wr.top,//alto de la ventana
		NULL,//manejador de la ventana padre o propietaria
		NULL,//manejador del menu o identificador de ventana hija
		hInstance,//manejador de la instancia de la aplicación
		NULL);//puntero a los datos de creación de la ventana

	ShowWindow(hwndVentana, nCmdShow);//Muestra la ventana creada

	//glewInit();//Inicializa glew

	//Instancia de la escena
	scene = new Scene(hwndVentana);

	gamPad = new GamePadRR(1);

	//Crear un timer con el valor especificado de time-out
	SetTimer(hwndVentana,//Manejador de ventana que recibirá los mensajes del timer
		Timer1,//identificador del timer
		30,//valor de time-out
		NULL);//dirección del procedimiento de timer

	MSG msg = { 0 };
	while (TRUE)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
				break;
		}
		else
		{
			if (renderiza)
			{
				scene->render(hContextoVentana);
				renderiza = false;
				/*
				if (gamPad->IsConnected())
				{

				}
				else
				{
					MessageBox(hwndVentana, "Ocurrio un error", "Ocurrio un error", MB_ICONWARNING | MB_CANCELTRYCONTINUE);
				//	//aqui ponemos un messgaebox para decir que se perdio la conexion con el gamepad
				}
				*/
			}
		}
	}

	return msg.wParam;

}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HGLRC hContextoGL;
	static HDC hContextoAux;
	int ancho, alto;
	char epx[6] = "";
	char epz[6] = "";
	char epy[6] = "";
	char edx[6] = "";
	char edz[6] = "";
	char edy[6] = "";
	char ec[80] = "";

	switch (message)
	{
	case WM_CREATE:
		hContextoAux = GetDC(hWnd);
		hContextoVentana = hContextoAux;
		DefPixelFormat(hContextoVentana);
		hContextoGL = wglCreateContext(hContextoVentana);
		wglMakeCurrent(hContextoVentana, hContextoGL);
		srand(time(NULL));

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
			exit(1);
		}

		//Funcion para repartir
		if (repartir == true) {
			//Reparte al jugador 1
			for (int i = 0; i < 7; i++) {
				srand(time(NULL));
				numSecret = rand() % FicDispo; //del 0 al 27
				piezas*auxrepart = inicio;
				while (auxrepart != NULL) {
					if (cont == numSecret) {
						//copiar al jugador 1
						jugador *nodo = new jugador;
						nodo->index = auxrepart->index;
						nodo->subindex = auxrepart->subindex;
						if (jugone == NULL) {
							jugone = nodo;
							jugone->sig = NULL;
							jugone->ant = NULL;

						}
						else {
							auxjugone = jugone;
							while (auxjugone->sig != NULL) {
								auxjugone = auxjugone->sig;
							}
							nodo->ant = auxjugone;
							auxjugone->sig = nodo;
							nodo->sig = NULL;
						}

						//Para eliminar de la lista principal
						//piezas *auxrepant,*auxrepsig;
						auxrepant = auxrepart->ant;
						auxrepsig = auxrepart->sig;

						if ((auxrepant == NULL) && (auxrepsig == NULL)) {
							inicio = NULL;
						}
						else if (auxrepant == NULL) {
							inicio = inicio->sig;
							inicio->ant = NULL;
						}
						else if (auxrepsig == NULL) {
							auxrepant->sig = NULL;
						}
						else {
							auxrepant->sig = auxrepsig;
							auxrepsig->ant = auxrepant;
						}
						delete auxrepart;
						//Hasta aqui elimina el nodo
						cont = 0;
						FicDispo -= 1;
						break;
					}
					cont++;
					auxrepart = auxrepart->sig;
				}
			}
			//termina repartir al jugador 1
			cont = 0;
			//reparte a jugador 2
			for (int j = 0; j < 7; j++) {
				srand(time(NULL));
				numSecret = rand() % FicDispo; //del 0 al 27
				piezas*auxrepartt = inicio;
				while (auxrepartt != NULL) {
					if (cont == numSecret) {
						//copiar al jugador 1
						jugador *nodod = new jugador;
						nodod->index = auxrepartt->index;
						nodod->subindex = auxrepartt->subindex;
						if (jugtwo == NULL) {
							jugtwo = nodod;
							jugtwo->sig = NULL;
							jugtwo->ant = NULL;

						}
						else {
							auxjugtwo = jugtwo;
							while (auxjugtwo->sig != NULL) {
								auxjugtwo = auxjugtwo->sig;
							}
							nodod->ant = auxjugtwo;
							auxjugtwo->sig = nodod;
							nodod->sig = NULL;
						}

						//Para eliminar de la lista principal
						//piezas *auxrepant,*auxrepsig;
						auxrepant = auxrepartt->ant;
						auxrepsig = auxrepartt->sig;

						if ((auxrepant == NULL) && (auxrepsig == NULL)) {
							inicio = NULL;
						}
						else if (auxrepant == NULL) {
							inicio = inicio->sig;
							inicio->ant = NULL;
						}
						else if (auxrepsig == NULL) {
							auxrepant->sig = NULL;
						}
						else {
							auxrepant->sig = auxrepsig;
							auxrepsig->ant = auxrepant;
						}
						delete auxrepartt;
						//Hasta aqui elimina el nodo
						cont = 0;
						FicDispo -= 1;
						break;
					}
					cont++;
					auxrepartt = auxrepartt->sig;
				}

			}
			//termina a la IA
			auxcursor = jugone;
			repartir = false;
		}


		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			MessageBox(hWnd, "Mensaje", "Titulo", MB_OK);
			return 0;
		case VK_UP:
			scene->turnUp();
			renderiza = true;
			return 0;
		case VK_DOWN:
			scene->turnDown();
			renderiza = true;
			return 0;
		case VK_LEFT:
			scene->turnLeft();
			renderiza = true;
			return 0;
		case VK_RIGHT:
			scene->turnRight();
			renderiza = true;
			return 0;
		case 0x44: //D
			scene->moveRight();
			renderiza = true;
			return 0;
		case 0x41: //A
			scene->moveLeft();
			renderiza = true;
			return 0;
		case 0x57: //W
			scene->moveForward();
			renderiza = true;
			return 0;
		case 0x53: //S
			scene->moveBackward();
			renderiza = true;
			return 0;
		case 69: //E
			scene->moveUp();
			return 0;
		case 78://N
			estjug1 = jugone;
			while (estjug1->sig != NULL) {
				FilJ1++;
				estjug1 = estjug1->sig;
			}

			estjug2 = jugtwo;
			while (estjug2->sig != NULL) {
				FilJ2++;
				estjug2 = estjug2->sig;
			}

			if (FilJ1 > FilJ2) {
				MessageBox(hWnd, "Tienes mas de 50% de ganar", "Aviso", MB_ICONINFORMATION | MB_OK);
			}
			else if (FilJ2 < FilJ1) {
				MessageBox(hWnd, "Tienes menos de 49% de ganar", "Aviso", MB_ICONINFORMATION | MB_OK);
			}
			else {
				MessageBox(hWnd, "Se encuentra en empate", "Aviso", MB_ICONINFORMATION | MB_OK);
			}


			return 0;
		case 77://M
			estaaux = inicio;
			while (estaaux->sig != NULL){
				conta++;
				estaaux = estaaux->sig;
			}
			_itoa(conta, bufffer, 10);
			strcat(ora, bufffer);
			totprob = 1 / conta;
			
			
			MessageBox(hWnd, ora, "Titulo", MB_ICONINFORMATION | MB_OK);
			return 0;
		case 81: //Q
			scene->moveDown();
			return 0;
			if (Domino == true) {
		case 76: //L
			if (auxcursor->sig != NULL) {
				auxcursor = auxcursor->sig;
				curs += .33;
			}
			return 0;
		case 75://K
			if (turno == 1) {
				//colorcar el puntero sobre la mesa
				izqnum = auxcursor->index;
				dernum = auxcursor->subindex;

				//Para eliminar de la lista del jugador uno
				//piezas *auxrepant,*auxrepsig;
				auxcursorAnt = auxcursor->ant;
				auxcursorSig = auxcursor->sig;

				if ((auxcursorAnt == NULL) && (auxcursorSig == NULL)) {
					jugone = NULL;
				}
				else if (auxcursorAnt == NULL) {
					jugone = jugone->sig;
					jugone->ant = NULL;
				}
				else if (auxcursorSig == NULL) {
					auxcursorAnt->sig = NULL;
				}
				else {
					auxcursorAnt->sig = auxcursorSig;
					auxcursorSig->ant = auxcursorAnt;
				}
				delete auxcursor;
				//Hasta aqui elimina el nodo
				auxcursor = jugone;
				curs = 0;
				turno++;
			}
			else {

			}
			//Turno de la computadora
			IATURNOK = jugtwo;
			while (IATURNOK->sig != NULL) {
				if (IATURNOK->index == izqnum) {
					fichaizq = true;
				}
				else if (IATURNOK->subindex == izqnum) {
					fichaizq = true;
				}
				else if (IATURNOK->index == dernum) {
					fichader = true;
				}
				else if (IATURNOK->subindex == dernum) {
					fichader = true;
				}
				IATURNOK = IATURNOK->sig;
			}

			return 0;

		case 74: //J
			if (auxcursor->ant != NULL) {
				auxcursor = auxcursor->ant;
				curs -= .33;
			}

			return 0;
			}
		}
	case WM_TIMER:



		renderiza = true;
		break;
	case WM_DESTROY:
	{
		KillTimer(hWnd, Timer1);
		delete scene->skyDay;
		delete scene->terrain;
		wglMakeCurrent(hContextoVentana, NULL);
		wglDeleteContext(hContextoGL);
		PostQuitMessage(0);
		return 0;
	} break;

	

	case WM_SIZE:
	{
		alto = HIWORD(lParam);
		ancho = LOWORD(lParam);
		if (alto == 0)
			alto = 1;
		glViewport(0, 0, ancho, alto);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)ancho / (GLfloat)alto, 1.0f, 10000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}
	break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

void DefPixelFormat(HDC hDC)
{
	int bestmatch;

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), //tamaño de la estructura
		1, //numero de version
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, //soporta la ventana, el opengl y manejara doble buffer
		PFD_TYPE_RGBA, //formato de 32 bits rgba
		32, //tamaño del color en 32 bits
		0, 0, 0, 0, 0, 0, //bits de color, no se usan
		0, //no hay buffer para el alfa
		0, //ignore el bit de corrimiento
		0, //no hay buffer de acumulacion
		0, 0, 0, 0, //no hay bits de acumulacion
		16, //tamaño del flotante para el buffer z
		0, //no hay buffers de stencil
		0, //no hay buffers auxiliares
		PFD_MAIN_PLANE, //plano principal para dibujo
		0, //reservado
		0, 0, 0 //mascaras de capas ignoradas
	};

	bestmatch = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, bestmatch, &pfd);
}

string obtenerDireccion(string filename) {
	WCHAR path[MAX_PATH];
	GetModuleFileNameW(NULL, path, MAX_PATH);
	char ch[260];
	char DefChar = ' ';
	WideCharToMultiByte(CP_ACP, 0, path, -1, ch, 260, &DefChar, NULL);
	string str(ch);
	size_t found = str.find_last_of("/\\");
	string pathoriginal = str.substr(0, found);
	string fileexecutable = str.substr(found + 1);
	string pathfile = pathoriginal + "\\" + filename;
	return pathfile;
}