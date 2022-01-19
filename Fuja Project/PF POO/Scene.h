#ifndef __Escena
#define __Escena

#include <gl\GLU.h>
#include <gl\GL.h>
#include "SkyDome.h"
#include "Terrain.h"
#include "Model.h"
#include "Water.h"
#include "Billboard.h"
#include "Fog.h"
#include "Camera.h"


struct piezas {
	int index;
	int subindex;
	int jug;
	piezas *sig;
	piezas*ant;
};

struct jugador {
	int index;
	int subindex;
	jugador *sig;
	jugador *ant;
};

bool Domino = false;

bool repartir = true, fichaizq=false, fichader=false;
float curs = 0;
int numSecret, FicDispo = 28, cont = 0, izqnum = -1, dernum = -1, turno = 1;
jugador * jugone = NULL, *jugtwo = NULL, *auxjugone = NULL, *auxjugtwo = NULL, *auxcursorAnt=NULL, *auxcursorSig = NULL;
piezas * inicio = NULL;
jugador *drawFichJ1 = NULL, *auxcursor=NULL, *IATURNOK=NULL;

class Scene : public Camera
{
public:
	
	SkyDome *skyDay;
	Terrain *terrain;
	//Water *lago;
	//Billboard *billBoard[100];
	//Niebla niebla;
	float posicion = -1;
	int pieza, subpieza;
	bool compFichaJ1 = true;

	EDXFramework::Model *house, *HP1,*HP2,*HP3,*HP4,*cursor;
	EDXFramework::Model *pie00,*pie03, *pie05, *pie10, *pie11, *pie14, *pie20, *pie21, *pie22, *pie31, *pie32,
		*pie33, *pie36, *pie40, *pie42, *pie43, *pie44, *pie46, *pie51, *pie52, *pie53, *pie54, *pie55, *pie60, *pie61,
		*pie62, *pie65, *pie66;
	bool p00 = false, p03 = false, p05 = false, p10 = false, p11 = false, p14 = false, p20 = false, p21 = false, p22 = false, 
		p31 = false, p32 = false,
		 p33 = false, p36 = false, p40 = false, p42 = false, p43 = false, p44 = false, p46 = false, p51 = false,
		 p52 = false, p53 = false, p54 = false, p55 = false, p60 = false, p61 = false, p62 = false, p65 = false, p66 = false;

	Scene(HWND hWnd)
	{
		GLfloat AmbMat[] = { 1, 1, 1, 1 };
		GLfloat AmbPos[] = { 0, 400, 400, 1 };

		glShadeModel(GL_SMOOTH);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glMaterialfv(GL_FRONT, GL_AMBIENT, AmbMat);
		glEnable(GL_NORMALIZE);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_POSITION, AmbPos);

		pie00 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino00.bmp", 1);
		pie03 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino03.bmp", 1);
		pie05 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino05.bmp", 1);
		pie10 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino10.bmp", 1);
		pie11 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino11.bmp", 1);
		pie14 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino14.bmp", 1);
		pie20 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino20.bmp", 1);
		pie21 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino21.bmp", 1);
		pie22 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino22.bmp", 1);
		pie31 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino31.bmp", 1);
		pie32 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino32.bmp", 1);
		pie33 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino33.bmp", 1);
		pie36 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino36.bmp", 1);
		pie40 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino40.bmp", 1);
		pie42 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino42.bmp", 1);
		pie43 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino43.bmp", 1);
		pie44 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino44.bmp", 1);
		pie46 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino46.bmp", 1);
		pie51 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino51.bmp", 1);
		pie52 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino52.bmp", 1);
		pie53 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino53.bmp", 1);
		pie54 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino54.bmp", 1);
		pie55 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino55.bmp", 1);
		pie60 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino60.bmp", 1);
		pie61 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino61.bmp", 1);
		pie62 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino62.bmp", 1);
		pie65 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino65.bmp", 1);
		pie66 = new EDXFramework::Model("Modelos//Domino//PiezaDomino.obj", "Modelos//Domino//texture_domino66.bmp", 1);
		cursor = new EDXFramework::Model("Modelos//Cursor//Cursor.obj", "Modelos//Cursor//Cursor_texture.bmp", 1);
		
		skyDay = new SkyDome(hWnd, 32, 32, 500, L"Imagenes//SkyMario.jpg");
		terrain = new Terrain(hWnd, L"Imagenes//terrenoplano.bmp", L"Imagenes//test1.jpg", L"Imagenes//texterr.jpg", 512, 512);
		house = new EDXFramework::Model("Modelos//Home//Viking.obj", "Modelos//Home//texture.bmp", 1);
		HP1 = new EDXFramework::Model("Modelos//House//House_Part1.obj", "Modelos//House//miniHouse_Part1.bmp", 1);
		HP2 = new EDXFramework::Model("Modelos//House//House_Part2.obj", "Modelos//House//miniHouse_Part2.bmp", 1);
		HP3 = new EDXFramework::Model("Modelos//House//House_Part3.obj", "Modelos//House//miniHouse_Part3.bmp", 1);
		HP4 = new EDXFramework::Model("Modelos//House//House_Part4.obj", "Modelos//House//miniHouse_Part4.bmp", 1);
		//gun = new EDXFramework::Model("Modelos//Gun//Cyborg_Riffle.obj", "Modelos//Gun//Cyborg_Riffle_D.bmp", 1);
		cameraInitialize();


	}

	void render(HDC hDC)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0, 0, 0, 0);
		glLoadIdentity();

			GLfloat AmbInt[] = { 0.1, 0.1, 0.1, 1 };
			glLightfv(GL_LIGHT0, GL_AMBIENT, AmbInt);
		
			//	py = terrain->Superficie(px, pz) * 4 + 4;
		
		if (pz == -15 && px >= 7 && px <= 15) {
				Domino = true;
				cameradomino();
		}
		cameraUpdate();
		
		//CamaraUpdate();

		//Skydome
		glPushMatrix();
		glTranslatef(0, 8, 0);
		glRotatef(90, 0, 1, 0);
		skyDay->Draw();
		glPopMatrix();
		
		//Terreno
		glPushMatrix();
		glScalef(1, 4, 1);
		terrain->Draw();
		glPopMatrix();

		////House
		glPushMatrix();
		glTranslatef(0, -100, 0);
		house->Draw();
		glPopMatrix();

		//Casa 
		glPushMatrix();
		glTranslatef(0, 37, -30);
		HP1->Draw();
		HP2->Draw();
		HP3->Draw();
		HP4->Draw();
		glPopMatrix();
		

		if (Domino == true) {

			//Comprueba que fichas tiene el jugador 1
			if (compFichaJ1 = true) {

				drawFichJ1 = jugone;
				while (drawFichJ1 != NULL) {
					pieza = drawFichJ1->index;
					subpieza = drawFichJ1->subindex;
					if (pieza == 0 && subpieza == 0) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie00->Draw();
						glPopMatrix();
					}
					else if (pieza == 1 && subpieza == 0) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie10->Draw();
						glPopMatrix();
					}
					else if (pieza == 1 && subpieza == 1) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie11->Draw();
						glPopMatrix();
					}
					else if (pieza == 4 && subpieza == 4) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie44->Draw();
						glPopMatrix();
					}
					else if (pieza == 2 && subpieza == 2) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie22->Draw();
						glPopMatrix();
					}
					else if (pieza == 3 && subpieza == 3) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie33->Draw();
						glPopMatrix();
					}
					else if (pieza == 6 && subpieza == 5) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie65->Draw();
						glPopMatrix();
					}
					else if (pieza == 4 && subpieza == 6) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie46->Draw();
						glPopMatrix();
					}
					else if (pieza == 6 && subpieza == 1) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie61->Draw();
						glPopMatrix();
					}
					else if (pieza == 6 && subpieza == 2) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie62->Draw();
						glPopMatrix();
					}
					else if (pieza == 3 && subpieza == 6) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie36->Draw();
						glPopMatrix();
					}
					else if (pieza == 5 && subpieza == 5) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie55->Draw();
						glPopMatrix();
					}
					else if (pieza == 2 && subpieza == 0) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie20->Draw();
						glPopMatrix();
					}
					else if (pieza == 0 && subpieza == 3) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie03->Draw();
						glPopMatrix();
					}
					else if (pieza == 5 && subpieza == 3) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie53->Draw();
						glPopMatrix();
					}
					else if (pieza == 0 && subpieza == 5) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie05->Draw();
						glPopMatrix();
					}
					else if (pieza == 4 && subpieza == 0) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie40->Draw();
						glPopMatrix();
					}
					else if (pieza == 6 && subpieza == 0) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie60->Draw();
						glPopMatrix();
					}
					else if (pieza == 5 && subpieza == 4) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie54->Draw();
						glPopMatrix();
					}
					else if (pieza == 6 && subpieza == 6) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie66->Draw();
						glPopMatrix();
					}
					else if (pieza == 5 && subpieza == 1) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie51->Draw();
						glPopMatrix();
					}
					else if (pieza == 4 && subpieza == 3) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie43->Draw();
						glPopMatrix();
					}
					else if (pieza == 2 && subpieza == 1) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie21->Draw();
						glPopMatrix();
					}
					else if (pieza == 1 && subpieza == 4) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie14->Draw();
						glPopMatrix();
					}
					else if (pieza == 3 && subpieza == 2) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie32->Draw();
						glPopMatrix();
					}
					else if (pieza == 4 && subpieza == 2) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie42->Draw();
						glPopMatrix();
					}
					else if (pieza == 5 && subpieza == 2) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie52->Draw();
						glPopMatrix();
					}
					else if (pieza == 3 && subpieza == 1) {

						posicion++;
						glPushMatrix();
						glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
						pie31->Draw();
						glPopMatrix();
					}
					drawFichJ1 = drawFichJ1->sig;
				}
			}
			posicion = -1;

			//Bolita de selección
			glPushMatrix();
			glTranslatef(-2.5, -97.3, 10 + curs);
			cursor->Draw();
			glPopMatrix();

			/*Pieza inicial glTranslatef(-2.3, -97.3, 10);
			//.33 por la posición mas 10 [x(.33) +10] ||x es la posición y puede ser negativa
			aumenta .33 por cada pieza puesta*/
			/*
			//Piezas de domino
			glPushMatrix();
				//glTranslatef(-2.3, -97.3, 10);
			glTranslatef(-2.3, -97.3, ((posicion*(.33))+10) );
				glRotatef(90, 0, 1, 0);
				pie00->Draw();
			glPopMatrix();


			glPushMatrix();
			posicion++;
				//glTranslatef(-2.3, -97.3, 10.33);
				glTranslatef(-2.3, -97.3, ((posicion*(.33)) + 10));
				glRotatef(90, 0, 1, 0);
				pie03->Draw();
			glPopMatrix();

			posicion = 0;
			*/

			//Para el centro de la mesa
			if (izqnum == 0 && dernum == 0 || p00 == true) {
				p00 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie00->Draw();
				glPopMatrix();
			}
			else if (izqnum == 1 && dernum == 0 || p10 == true) {
				p10 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie10->Draw();
				glPopMatrix();
			}
			else if (izqnum == 1 && dernum == 1 || p11 == true) {
				p11 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie11->Draw();
				glPopMatrix();
			}
			else if (izqnum == 4 && dernum == 4 || p44 == true) {
				p44 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie44->Draw();
				glPopMatrix();
			}
			else if (izqnum == 2 && dernum == 2 || p22 == true) {
				p22 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie22->Draw();
				glPopMatrix();
			}
			else if (izqnum == 3 && dernum == 3 || p33 == true) {
				p33 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie33->Draw();
				glPopMatrix();
			}
			else if (izqnum == 6 && dernum == 5 || p65 == true) {
				p65 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie65->Draw();
				glPopMatrix();
			}
			else if (izqnum == 4 && dernum == 6 || p46 == true) {
				p46 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie46->Draw();
				glPopMatrix();
			}
			else if (izqnum == 6 && dernum == 1 || p61 == true) {
				p61 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie61->Draw();
				glPopMatrix();
			}
			else if (izqnum == 6 && dernum == 2 || p62 == true) {
				p62 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie62->Draw();
				glPopMatrix();
			}
			else if (izqnum == 3 && dernum == 6 || p36 == true) {
				p36 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie36->Draw();
				glPopMatrix();
			}
			else if (izqnum == 5 && dernum == 5 || p55 == true) {
				p55 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie55->Draw();
				glPopMatrix();
			}
			else if (izqnum == 2 && dernum == 0 || p20 == true) {
				p20 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie20->Draw();
				glPopMatrix();
			}
			else if (izqnum == 0 && dernum == 3 || p03 == true) {
				p03 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie03->Draw();
				glPopMatrix();
			}
			else if (izqnum == 5 && dernum == 3 || p53 == true) {
				p53 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie53->Draw();
				glPopMatrix();
			}
			else if (izqnum == 0 && dernum == 5 || p05 == true) {
				p05 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie05->Draw();
				glPopMatrix();
			}
			else if (izqnum == 4 && dernum == 0 || p40 == true) {
				p40 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie40->Draw();
				glPopMatrix();
			}
			else if (izqnum == 6 && dernum == 0 || p60 == true) {
				p60 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie60->Draw();
				glPopMatrix();
			}
			else if (izqnum == 5 && dernum == 4 || p54 == true) {
				p54 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie54->Draw();
				glPopMatrix();
			}
			else if (izqnum == 6 && dernum == 6 || p66 == true) {
				p66 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie66->Draw();
				glPopMatrix();
			}
			else if (izqnum == 5 && dernum == 1 || p51 == true) {
				p51 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie51->Draw();
				glPopMatrix();
			}
			else if (izqnum == 4 && dernum == 3 || p43 == true) {
				p43 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie43->Draw();
				glPopMatrix();
			}
			else if (izqnum == 2 && dernum == 1 || p21 == true) {
				p21 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie21->Draw();
				glPopMatrix();
			}
			else if (izqnum == 1 && dernum == 4 || p14 == true) {
				p14 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie14->Draw();
				glPopMatrix();
			}
			else if (izqnum == 3 && dernum == 2 || p32 == true) {
				p32 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie32->Draw();
				glPopMatrix();
			}
			else if (izqnum == 4 && dernum == 2 || p42 == true) {
				p42 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie42->Draw();
				glPopMatrix();
			}
			else if (izqnum == 5 && dernum == 2 || p52 == true) {
				p52 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie52->Draw();
				glPopMatrix();
			}
			else if (izqnum == 3 && dernum == 1 || p31 == true) {
				p31 = true;
				posicion++;
				glPushMatrix();
				glTranslatef(-1.5, -97.3, ((posicion*(.33)) + 10));
				pie31->Draw();
				glPopMatrix();
			}
			posicion = -1;

		}





		SwapBuffers(hDC);
	}
};
#endif
