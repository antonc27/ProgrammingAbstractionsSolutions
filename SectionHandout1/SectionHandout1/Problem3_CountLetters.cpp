#include <iostream>
#include <fstream>
#include "simpio.h"
#include "vector.h"
#include "strutils.h"
#include <ctype.h>

void InitLettersCount(Vector<int> &hist, int size)
{
	for (int i=0; i < size; i++)
	{
		hist.add(0);
	}
}

void IncreaseLettersCount(int bucketIndex, Vector<int> &hist)
{
	hist.setAt(bucketIndex, hist.getAt(bucketIndex)+1);
}

void FillLettersCount(ifstream &file, Vector<int> &hist)
{
	while (true)
	{
		string line;
		getline(file, line);
		if (file.fail()) break;
		
		line = ConvertToLowerCase(line);
		for (int i=0; i < line.length(); i++)
		{
			if(isalpha(line[i]))
			{
				int bucketIndex = (line[i] - 'a');
				IncreaseLettersCount(bucketIndex, hist);
			}
		}
	}
}

void PrintLettersCount(Vector<int> &hist)
{
	for (int i=0; i < hist.size(); i++)
	{
		cout << char(i + int('a')) << ": " << hist.getAt(i) << endl;
	}
}

void CountLetters(string filename)
{
	ifstream file;
	file.open(filename.c_str());

	if (file.fail())
		Error("Couldnt open file: " + filename);

	Vector<int> alphabetCountList;
	InitLettersCount(alphabetCountList, 26);
	FillLettersCount(file, alphabetCountList);
	PrintLettersCount(alphabetCountList);
}

int Problem3_CountLetters_main()
{
	CountLetters("./SectionHandout1.app/Contents/Resources/textToCountLetters.txt");

	return 0;
}
