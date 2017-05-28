#include <iostream>
#include <fstream>
#include "simpio.h"
#include "vector.h"
#include "strutils.h"

void InitHist(Vector<string> &hist, int size)
{
	for (int i=0; i < size; i++)
	{
		hist.add("");
	}
}

void IncreaseHistScore(int bucketIndex, Vector<string> &hist)
{
	string newStr = hist.getAt(bucketIndex) + "X";
	hist.setAt(bucketIndex, newStr);
}

void FillHist(ifstream &file, Vector<string> &hist)
{
	while (true)
	{
		string line;
		getline(file, line);
		if (file.fail()) break;

		char firstDigit = line[0];
		int bucketIndex = (firstDigit - '0');
		IncreaseHistScore(bucketIndex, hist);
	}
}

void PrintHist(Vector<string> &hist)
{
	for (int i=0; i < hist.size(); i++)
	{
		if (i == 0)
		{
			cout << i << "-9: " << hist.getAt(i) << endl;
			continue;
		}

		cout << i << "0-" << i << "9: " << hist.getAt(i) << endl;
	}
}

int histogram_main()
{
	ifstream file;
	while (true)
	{
		cout << "Enter scores file name: ";
		string s = GetLine();
		file.open(s.c_str());
		if (!file.fail()) break;
		cout << "Bad file name, enter again!" << endl;
		file.clear();
	}

	cout << endl;
	
	Vector<string> hist;
	InitHist(hist, 10);
	FillHist(file, hist);
	PrintHist(hist);

	return 0;
}
