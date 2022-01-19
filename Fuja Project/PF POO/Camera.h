#ifndef __Camera
#define __Camera

#include "VectorRR.h"


class Camera : public VectorRR
{
public:
	VectorRR posc, dirc;
	GLdouble px, py, pz, dx, dy, dz, ux, uy, uz;
	int camind = 0;

	Camera()
	{
	}

	/*void CamaraUpdate()
	{
		gluLookAt(posc.X, posc.Y + 10, posc.Z - 10,
			dirc.X, dirc.Y + 10, dirc.Z,
			0, 1, 0);
	}*/

	void cameraInitialize()
	{
		px = 0, py = 45, pz = 0, dx = 0, dy = 45, dz = -25;
		ux = 0, uy = 1, uz = 0;
		/*px = -5, py = -95, pz = 10, dx = 10, dy = -103, dz = 11;
		ux = 0, uy = 1, uz = 0;*/

		gluLookAt(px, py, pz, dx, dy, dz, ux, uy, uz);
	}

	void cameraUpdate()
	{
		gluLookAt(px, py, pz, dx, dy, dz, ux, uy, uz);
		//7 45 -15 hasta 15 45 -15
	}

	void cameradomino() {
		px = -5, py = -95, pz = 10, dx = 10, dy = -103, dz = 11;
		ux = 0, uy = 1, uz = 0;
	}


	//-5 -95 10 ||10 -103 11 ||0 1 0
	//-5 -96 10
	void moveUp() {
		py += 1;
		dy += 1;

	}
	void moveDown() {
		py -= 1;
		dy -= 1;
	}

	void moveLeft()
	{

			px -= 1;
			dx -= 1;


	}

	void moveRight()
	{

			px += 1;
			dx += 1;
		
	}

	void moveForward()
	{

			pz += 1;
			dz += 1;
		
	}

	void moveBackward()
	{

			pz -= 1;
			dz -= 1;
		
	}

	void turnRight()
	{
		//debe empezar viendo a z negativa, si no gira al reves
		if (dx < 15 + px && camind == 0)
			dx += 1;
		if (dx == 15 + px && camind == 0)
			camind = 1;
		if (dz < 15 + pz && camind == 1)
			dz += 1;
		if (dz == 15 + pz && camind == 1)
			camind = 2;
		if (dx > -15 + px && camind == 2)
			dx -= 1;
		if (dx == -15 + px && camind == 2)
			camind = 3;
		if (dz > -15 + pz && camind == 3)
			dz -= 1;
		if (dz == -15 + pz && camind == 3)
			camind = 0;
	}

	void turnLeft()
	{
		//debe empezar viendo a z negativa, si no gira al reves
		if (dx > -15 + px && camind == 0)
			dx -= 1;
		if (dx == -15 + px && camind == 0)
			camind = 1;
		if (dz < 15 + pz && camind == 1)
			dz += 1;
		if (dz == 15 + pz && camind == 1)
			camind = 2;
		if (dx < 15 + px && camind == 2)
			dx += 1;
		if (dx == 15 + px && camind == 2)
			camind = 3;
		if (dz > -15 + pz && camind == 3)
			dz -= 1;
		if (dz == -15 + pz && camind == 3)
			camind = 0;
	}

	void turnUp()
	{
		if (dy < 50 + py)
		{
			dy += 1;
		}
	}

	void turnDown()
	{
		if (dy > -50 + py)
		{
			dy -= 1;
		}
	}
};
#endif