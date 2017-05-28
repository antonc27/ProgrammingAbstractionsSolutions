#include <iostream>
#include "simpio.h"
#include "maze.h"
#include "random.h"
#include "set.h"
#include "extgraph.h"
#include "stack.h"
#include "queue.h"

bool equals(pointT p1, pointT p2) {
	return p1.col == p2.col && p1.row == p2.row;
}

bool hasBorder(pointT p1, pointT p2) {
	return p1.col == p2.col || p1.row == p2.row;
}

int comparePoints(pointT p1, pointT p2) {
	if (equals(p1, p2)) {
		return 0;
	} else {
		if (p1.row > p2.row) {
			return 1;
		} else {
			if (p1.row == p2.row && p1.col > p2.col) {
				return 1;
			} else {
				return -1;
			}
		}
		
	}
}

pointT randomNeighbor(pointT p) {
	int row = p.row;
	int col = p.col;
	switch (RandomInteger(0,3)) {
		case 0:
			row--;
			break;
		case 1:
			row++;
			break;
		case 2:
			col--;
			break;
		case 3:
			col++;
			break;
	}
	pointT neighbor = {row, col};
	return neighbor;
}

void PrintPoint(pointT p) {
	cout << p.row << " " << p.col << endl;
}

void PrintSet(Set<pointT> set)
{
	Set<pointT>::Iterator itr = set.iterator();
	while (itr.hasNext()) {
		pointT next = itr.next();
		PrintPoint(next);
	}
}

void generateMaze(Maze &maze) {
	Set<pointT> visitedPoints(comparePoints);
	pointT currentPoint = {RandomInteger(0, maze.numRows() - 1), RandomInteger(0, maze.numCols() - 1)};
	visitedPoints.add(currentPoint);
	while (visitedPoints.size() < maze.numCols() * maze.numRows()) {
		pointT neighbor = randomNeighbor(currentPoint);
		while (!maze.pointInBounds(neighbor)) {
			neighbor = randomNeighbor(currentPoint);
		}
		if (!visitedPoints.contains(neighbor)) {
			maze.setWall(neighbor, currentPoint, false);
			visitedPoints.add(neighbor);
			Pause(0.01);
		}
		currentPoint = neighbor;
	}
}

void printPath(Maze &maze, Stack<pointT> path) {
	maze.draw();
	Stack<pointT> reversed;
	while (!path.isEmpty()) {
		reversed.push(path.pop());
	}
	while (!reversed.isEmpty()) {
		maze.drawMark(reversed.pop(), "Blue");
		Pause(0.05);
	}
}

bool pathContainsPoint(Stack<pointT> path, pointT p) {
	while (!path.isEmpty()) {
		if (equals(path.pop(), p)) {
			return true;
		}
	}
	return false;
}

void solveMaze(Maze &maze) {
	pointT start = {0, 0};
	pointT finish = {maze.numRows() - 1, maze.numCols() - 1};

	Stack<pointT> path;
	path.push(start);

	Queue<Stack<pointT>> paths;
	paths.enqueue(path);

	Stack<pointT> shortestPath;

	while (shortestPath.size() == 0) {
		Stack<pointT> currentPath = paths.dequeue();
		pointT currentEnd = currentPath.peek();
		if (equals(currentEnd, finish)) {
			shortestPath = currentPath;
			break;
		} else {
			for (int i=currentEnd.row-1; i<currentEnd.row+2; i++) {
				for (int j=currentEnd.col-1; j<currentEnd.col+2; j++) {
					pointT neighbor = {i, j};
					if (!equals(neighbor, currentEnd) && hasBorder(neighbor, currentEnd)) {
						if (maze.pointInBounds(neighbor) && !maze.isWall(neighbor, currentEnd)) {
							if (!pathContainsPoint(currentPath, neighbor)) {
								Stack<pointT> copyPath = currentPath;
								copyPath.push(neighbor);
								paths.enqueue(copyPath);
							}
						}
					}
				}
			}
		}
	}

	printPath(maze, shortestPath);
}

void generateAndSolveMaze() {
	Maze maze = Maze(17, 30, true);
	maze.draw();

	cout << "Building maze... " ;
	generateMaze(maze);
	cout << "Done!" << endl;

	cout << "Hit RETURN to solve: ";
	string s = GetLine();
	solveMaze(maze);
}