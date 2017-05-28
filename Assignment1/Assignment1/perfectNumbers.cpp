#include <iostream>
#include "simpio.h"

bool IsPerfect(int n)
{
	int sum = 0;
	for(int i=1; i<n; i++)
	{
		if (n%i == 0)
		{
			sum += i;
		}
	}

	return (sum == n);
}

int perfect_main()
{	
	cout << "Find perfect numbers from 1 to 10000" << endl;
	
	for (int i=1; i<=10000; i++)
	{
		if (IsPerfect(i))
		{
			cout << i << endl;
		}
	}

	return 0;
}
