#include "simpio.h"
#include <iostream>
#include "scanner.h"
#include "stack.h"

#define TAG_START "<"
#define TAG_CLOSE "/"
#define TAG_END ">"

bool IsCorrectlyNested(string htmlStr)
{
	Scanner s;
	s.setInput(htmlStr);
	//s.setSpaceOption(Scanner::IgnoreSpaces);
	
	Stack<string> tags;

	bool isWaitingForTag = false;
	bool isClosingTag = false;

	while(s.hasMoreTokens())
	{
		string token = s.nextToken();

		if (token == TAG_START)
		{
			isWaitingForTag = true;
		}
		else if (token == TAG_CLOSE)
		{
			isClosingTag = true;
		}
		else if (token == TAG_END)
		{
			//cout << "Tag ended!" << endl;
		}
		else if (isWaitingForTag)
		{
			if (!isClosingTag)
			{
				tags.push(token);
			}
			else
			{
				if (tags.isEmpty())
				{
					return false;
				}

				string closingTag = tags.pop();

				if (closingTag != token)
				{
					return false;
				}
			}

			isWaitingForTag = false;
			isClosingTag = false;
		}
	}

	return tags.isEmpty();
}

int Problem3_Scanner_main()
{
	string htmlStr = "<html><b><i>CS106 rules!</i></b></html>";

	bool correct = IsCorrectlyNested(htmlStr);

	cout << "html string '" << htmlStr << "' correctly nested: " << ((correct) ? "YES" : "NO") << endl;

	return 0;
}
