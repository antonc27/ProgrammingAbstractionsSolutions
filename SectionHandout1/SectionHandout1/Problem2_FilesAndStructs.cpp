#include "simpio.h"
#include <iostream>
#include <fstream>
#include "strutils.h"

struct scoreStatsT {
	int minScore;
	int maxScore;
	double averageScore;
};

scoreStatsT GetScoreStatistics(ifstream &file)
{
	int localMinScore = 100;
	int localMaxScore = 0;

	int scoresSum = 0;
	int scoresCount = 0;

	string scoreStr = "";
	int currentScore = -1;
	while (true)
	{
		getline(file, scoreStr);
		currentScore = StringToInteger(scoreStr);
		if (file.fail()) break;

		if (currentScore > localMaxScore)
		{
			localMaxScore = currentScore;
		}

		if (currentScore < localMinScore)
		{
			localMinScore = currentScore;
		}

		scoresSum += currentScore;
		scoresCount++;
	}

	scoreStatsT scoreStats;

	scoreStats.maxScore = localMaxScore;
	scoreStats.minScore = localMinScore;
	scoreStats.averageScore = scoresSum/double(scoresCount);

	return scoreStats;
}

int Problem2_FilesAndStructs_main()
{
	ifstream file;
	file.open("./SectionHandout1.app/Contents/Resources/scores.txt");

	scoreStatsT scoreStats = GetScoreStatistics(file);

	cout << "Max score: " << scoreStats.maxScore << endl;
	cout << "Min score: " << scoreStats.minScore << endl;
	cout << "Avg : " << scoreStats.averageScore << endl;
	
	file.close();

	return 0;
}
