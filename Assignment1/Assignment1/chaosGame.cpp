#include <iostream>
#include "simpio.h"

#include "graphics.h"
#include "extgraph.h"

#include "random.h"

//#import <string>

void selectRandomTriangPoint(double &pointX, double &pointY, double xA, double yA, double xB, double yB, double xC, double yC)
{
	int choice = RandomInteger(1, 3);

	switch(choice)
	{
		case 1:
			pointX = xA;
			pointY = yA;
			break;
		
		case 2:
			pointX = xB;
			pointY = yB;
			break;

		case 3:
			pointX = xC;
			pointY = yC;
			break;
	}
}

void getTriangPoint(string Name, double &pointX, double &pointY)
{
	cout << "Please select " << Name << " point of trinagle"<< endl;

	WaitForMouseDown();

	pointX =  GetMouseX();
	pointY =  GetMouseY();

	WaitForMouseUp();
}

void drawTriang(double xA, double yA, double xB, double yB, double xC, double yC)
{
	MovePen(xA, yA);
	DrawLine(xB - xA, yB - yA);

	MovePen(xB, yB);
	DrawLine(xC - xB, yC - yB);

	MovePen(xC, yC);
	DrawLine(xA - xC, yA - yC);
}

int chaos_main()
{	
	Randomize();

	InitGraphics();
	
	double currentPointX = 0;
	double currentPointY = 0;
	
	double currentVertexX = 0;
	double currentVertexY = 0;

	double xA = 0;
	double yA = 0;

	double xB = 0;
	double yB = 0;

	double xC = 0;
	double yC = 0;
	
	getTriangPoint("A", xA, yA);
	getTriangPoint("B", xB, yB);
	getTriangPoint("C", xC, yC);
	
	drawTriang(xA, yA, xB, yB, xC, yC);
	
	SetPenColor("Blue");
	
	selectRandomTriangPoint(currentVertexX, currentVertexY, xA, yA, xB, yB, xC, yC);
	
	currentPointX = currentVertexX;
	currentPointY = currentVertexY;

	while (true)
	{	
		MovePen(currentPointX, currentPointY);

		StartFilledRegion(1.0);
		DrawArc(0.01, 0, 360);
		EndFilledRegion();

		selectRandomTriangPoint(currentVertexX, currentVertexY, xA, yA, xB, yB, xC, yC);
		
		currentPointX += (currentVertexX - currentPointX)/2;
		currentPointY += (currentVertexY - currentPointY)/2;

		Pause(0.0001);
		UpdateDisplay();
	}	


	return 0;
}
