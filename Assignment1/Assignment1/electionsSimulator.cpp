#include <iostream>
#include "simpio.h"
#include "random.h"

#define NUMBER_TRIALS 500

void countRecordedVotes(int realVotes, double votingError, int &validVotes, int &invalidVotes)
{
	for (int i=1; i<=realVotes; i++)
	{
		if (RandomChance(votingError))
		{
			invalidVotes++;
		}
		else
		{
			validVotes++;
		}
	}
}

bool makeTrial(int voters, double percentageSpread, double votingError)
{
	int realVotesForA = (int)voters*(0.5 + percentageSpread/2.);
	int realVotesForB = voters - realVotesForA;
	
	int recordedVotesForA = 0;
	int recordedVotesForB = 0;
	
	countRecordedVotes(realVotesForA, votingError, recordedVotesForA, recordedVotesForB);

	countRecordedVotes(realVotesForB, votingError, recordedVotesForB, recordedVotesForA);

	return (recordedVotesForA > recordedVotesForB);
}

double performSimulation(int trials, int voters, double percentageSpread, double votingError)
{
	int invalidTrials = 0;

	for (int i=1; i<=trials; i++)
	{
		if (!makeTrial(voters, percentageSpread, votingError))
		{
			invalidTrials++;
		}
	}

	return (double)invalidTrials/trials*100;
}

int elections_main()
{
	Randomize();
	
	cout << "Enter number of voters: ";
	int voters = GetInteger();
	cout << "Enter percentage spread between candidates: ";
	double percentageSpread = GetReal();
	cout << "Enter voting error percentage: ";
	double votingError = GetReal();
	
	//int voters = 10000;
	//double percentageSpread = .005;
	//double votingError = .15;

	cout << endl << "Chance of an invalid election result after " << NUMBER_TRIALS <<" trials = " << performSimulation(NUMBER_TRIALS, voters, percentageSpread, votingError) << "%" << endl;

	return 0;
}
