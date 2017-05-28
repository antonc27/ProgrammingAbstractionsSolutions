#include <iostream>
#include "random.h"
#include "simpio.h"
#include "RandomWriter.h"
#include "MazeSolver.h"
#include "graphics.h"

void promptMenu() {
	cout << "Here is the menu:" << endl;
	cout << "        Enter 0 to quit" << endl;
	cout << "        Enter 1 for Random Writer" << endl;
	cout << "        Enter 2 for Maze" << endl;
	cout << "Choice: ";
}

int main()
{
	InitGraphics();
	Randomize();

	while (true)
	{
		promptMenu();
		int choice = GetInteger();
		if (choice == 0) {
			break;
		} else if (choice == 1) {
			randomWriter();
		} else if (choice == 2) {
			generateAndSolveMaze();
		}
	}

	return 0;
}
