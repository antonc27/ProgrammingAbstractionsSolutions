#include "simpio.h"
#include <iostream>

string CensorString1(string text, string remove)
{
	string censoredString = "";
	for (int i=0; i < text.length(); i++)
	{
		if (remove.find(text[i]) == string::npos)
		{
			censoredString += text[i];
		}
	}
	return censoredString;
}

void CensorString2(string &text, string remove)
{
	int charPos;
	for (int i=0; i < remove.length(); i++)
	{
		while ((charPos = text.find(remove[i])) != string::npos)
		{
			text.erase(charPos, 1);
		}
	}
}

int Problem1_RemoveAllOccurrence_main()
{
	string text = "Llamas like to laugh";
	string remove = "la";

	string nexText = CensorString1(text, remove);
	cout << nexText << endl;
	
	CensorString2(text, remove);
	cout << text << endl;

	return 0;
}
