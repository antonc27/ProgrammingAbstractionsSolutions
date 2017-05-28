#include "simpio.h"
#include <iostream>
#include "Grid.h"

int CountNeighborhoodBombs(int i, int j, Grid<bool> &bombLocations)
{
	int neighborhoodBombsCount = 0;

	for (int row = i-1; row <= i+1; row++)
	{
		for (int col = j-1; col <= j+1; col++)
		{
			bool insideGridVert = (row >= 0 && row < bombLocations.numRows());
			bool insideGridHoriz = (col >= 0 && col < bombLocations.numCols());

			if (insideGridVert && insideGridHoriz)
			{
				if (bombLocations.getAt(row, col))
				{
					neighborhoodBombsCount++;
				}
			}
		}
	}

	return neighborhoodBombsCount;
}

Grid<int> MakeGridOfCounts(Grid<bool> &bombLocations)
{
	Grid<int> gridOfCounts(bombLocations.numRows(), bombLocations.numCols());
	
	for (int row = 0; row < gridOfCounts.numRows(); row++)
	{
		for (int col = 0; col < gridOfCounts.numCols(); col++)
		{
			int bombsCount = CountNeighborhoodBombs(row, col, bombLocations);
			gridOfCounts.setAt(row, col, bombsCount);
		}
	}

	return gridOfCounts;
}

void PrintGridOfCounts(Grid<int> &countsGrid)
{
	for (int row = 0; row < countsGrid.numRows(); row++)
	{
		for (int col = 0; col < countsGrid.numCols(); col++)
		{
			cout << countsGrid.getAt(row, col) << " ";
		}

		cout << endl;
	}
}

int Problem5_Minesweeper_main()
{
	Grid<bool> bombGrid(6, 6);
	
	for (int row = 0; row < bombGrid.numRows(); row++)
	{
		for (int col = 0; col < bombGrid.numCols(); col++)
		{
			bombGrid.setAt(row, col, false);
		}
	}

	bombGrid.setAt(0, 0, true);
	bombGrid.setAt(0, 5, true);
	bombGrid.setAt(1, 5, true);
	bombGrid.setAt(2, 0, true);
	bombGrid.setAt(2, 1, true);
	bombGrid.setAt(2, 3, true);
	bombGrid.setAt(2, 5, true);
	bombGrid.setAt(3, 0, true);
	bombGrid.setAt(4, 2, true);

	Grid<int> countsGrid = MakeGridOfCounts(bombGrid);

	PrintGridOfCounts(countsGrid);

	return 0;
}
