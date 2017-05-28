#include "simpio.h"
#include <iostream>
#include "vector.h"

struct eMailMsg
{
 string to; // i.e. "professor@stanford.edu"
 string from; // i.e. "student@stanford.edu"
 string message; // body of message
 string subject; // i.e. "CS106 Rocks!"
 int date; // date email was sent
 int time; // time email was sent
};

void RemoveSpam(Vector<eMailMsg> &m)
{
	Vector<eMailMsg> clearM;

	for (int i=0; i<m.size(); i++)
	{
		string subj = m[i].subject;
		if (subj.find("SPAM") != 0)
		{
			clearM.add(m[i]);
		}
	}

	m = clearM;
}

int Problem1_Vectors_main()
{
	Vector<eMailMsg> mails;
	
	eMailMsg spamMail;
	spamMail.message = "msg text 1";
	spamMail.subject = "SPAM here";
	mails.add(spamMail);

	eMailMsg normalMail;
	normalMail.message = "msg text 2";
	normalMail.subject = "subject here";
	mails.add(normalMail);

	RemoveSpam(mails);

	return 0;
}
