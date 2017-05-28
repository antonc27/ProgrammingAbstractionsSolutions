#include "simpio.h"
#include <iostream>
#include <fstream>
#include "map.h"

char MostFrequentCharacter(ifstream &f, int &numOccurrences)
{
	Map<int> charMap;
	
	int c;
	while((c = f.get()) != EOF)
	{
		string key = "";
		key += char(c);

		if (charMap.containsKey(key))
		{
			charMap[key]++;
		}
		else
		{
			charMap[key] = 1;
		}
	}
	
	int localMax = -1;
	string maxKey = "";
	Map<int>::Iterator itr = charMap.iterator();
	while(itr.hasNext())
	{
		string key = itr.next();
		if (charMap[key] > localMax)
		{
			localMax = charMap[key];
			maxKey = key;
		}
	}
	
	numOccurrences = localMax;

	return maxKey[0];
}

int Problem4_Map_main()
{
	string filename = "./SectionHandout2.app/Contents/Resources/textToCountLetters.txt";
	ifstream file;
	file.open(filename.c_str());
	
	if (file.fail())
		Error("Couldnt open file: " + filename);
	
	int i;
	char cm = MostFrequentCharacter(file, i);
	
	cout << cm << " " << i << endl;

	return 0;
}
