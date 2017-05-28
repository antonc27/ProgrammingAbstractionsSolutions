#include <iostream>
#include "simpio.h"

#include "strutils.h"

int letterToDigit(char letter)
{
	switch (letter)
	{
		case 'A':
		case 'E':
		case 'I':
		case 'O':
		case 'U':
		case 'H':
		case 'W':
		case 'Y':
			return 0;

		case 'B':
		case 'F':
		case 'P':
		case 'V':
			return 1;

		case 'C':
		case 'G':
		case 'J':
		case 'K':
		case 'Q':
		case 'S':
		case 'X':
		case 'Z':
			return 2;

		case 'D':
		case 'T':
			return 3;

		case 'M':
		case 'N':
			return 4;

		case 'L':
			return 5;

		case 'R':
			return 6;

		default:
			return -1;
	}
}

string soundexCode(string str)
{
	str = ConvertToUpperCase(str);
	
	string code = "";
	code += str[0];
	
	int prevDig = -1;
	for (int i=1; i < str.length(); i++)
	{
		int dig = letterToDigit(str[i]);
		if (dig != -1 && dig != 0 && dig != prevDig)
		{
			code += IntegerToString(dig);
			prevDig = dig;
		}
	}
	
	int len = code.length();
	if (len < 4)
	{
		for (int i = len; i < 4; i++)
		{
			code += "0";
		}
	}
	else if (len > 4)
	{
		code = code.substr(0, 4);
	}

	return code;
}

int soundex_main()
{
	while(true)
	{
		cout << "Enter surname (RETURN to quit): ";
		string s = GetLine();
		if (s.length() == 0)
		{
			break;
		}
		
		cout << "Soundex code for " << s << " is " << soundexCode(s) << endl;
	}

	return 0;
}
