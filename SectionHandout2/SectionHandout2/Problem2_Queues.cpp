#include "simpio.h"
#include <iostream>
#include "queue.h"
#include "stack.h"

void PrintQueue(Queue<int> q)
{
	cout << "Start - ";

	int size = q.size();
	for (int i=0; i<size; i++)
	{
		cout << q.dequeue() << " - " ;
	}

	cout << "End" << endl;
}

void ReverseQueue(Queue<int> &q)
{
	Stack<int> helperStack;
	//Queue<int> reverseQueue;

	int size = q.size();
	for (int i=0; i<size; i++)
	{
		helperStack.push(q.dequeue());
	}

	size = helperStack.size();
	for (int i=0; i<size; i++)
	{
		q.enqueue(helperStack.pop());
	}
}

int Problem2_Queues_main()
{
	Queue<int> q;
	
	q.enqueue(1);
	q.enqueue(2);
	q.enqueue(3);

	PrintQueue(q);
	
	ReverseQueue(q);

	PrintQueue(q);

	return 0;
}
