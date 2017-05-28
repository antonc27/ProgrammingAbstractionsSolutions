/*
 * File: mazelib.h
 * ---------------
 * This interface provides a library of primitive operations
 * to simplify the solution to the maze problem.
 */

#ifndef _mazelib_h
#define _mazelib_h

#include "genlib.h"

/*
 * Type: directionT
 * ----------------
 * This type is used to represent the four compass directions.
 */

enum directionT { North, East, South, West };

/*
 * Type: pointT
 * ------------
 * The type pointT is used to encapsulate a pair of integer
 * coordinates into a single value with x and y components.
 */

struct pointT {
    int x, y;
};

void PrintMaze();

/*
 * Function: ReadMazeMap
 * Usage: ReadMazeMap(filename);
 * -----------------------------
 * This function reads in a map of the maze from the specified
 * file and stores it in private data structures maintained by
 * this module. In the data file, the characters '+', '-', and
 * '|' represent corners, horizontal walls, and vertical walls,
 * respectively; spaces represent open passageway squares. The
 * starting position is indicated by the character 'S'. For
 * example, the following data file defines a simple maze:
 *
 * +-+-+-+-+-+
 * |     |
 * + +-+ + +-+
 * |S  |     |
 * +-+-+-+-+-+
 *
 * Coordinates in the maze are numbered starting at (0,0) in
 * the lower left corner. The goal is to find a path from
 * the (0,0) square to the exit east of the (4,1) square.
 */

void ReadMazeMap(string filename);

/*
 * Function: GetStartPosition
 * Usage: pt = GetStartPosition();
 * -------------------------------
 * This function returns a pointT indicating the coordinates of
 * the start square.
 */

pointT GetStartPosition();

/*
 * Function: OutsideMaze
 * Usage: if (OutsideMaze(pt)) . . .
 * ---------------------------------
 * This function returns true if the specified point is outside
 * the boundary of the maze.
 */

bool OutsideMaze(pointT pt);

/*
 * Function: WallExists
 * Usage: if (WallExists(pt, dir)) . . .
 * -------------------------------------
 * This function returns true if there is a wall in the indicated
 * direction from the square at position pt.
 */

bool WallExists(pointT pt, directionT dir);

/*
 * Functions: MarkSquare, UnmarkSquare, IsMarked
 * Usage: MarkSquare(pt);
 * UnmarkSquare(pt);
 * if (IsMarked(pt)) . . .
 * ------------------------------
 * These functions mark, unmark, and test the status of the
 * square specified by the coordinates pt.
 */

void MarkSquare(pointT pt);
void UnmarkSquare(pointT pt);
bool IsMarked(pointT pt);

int MarkedPathLength();

#endif
