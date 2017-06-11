#include "pqueue.h"
#include "genlib.h"
#include <iostream>


/* Implementation notes: PQueue class
 * ----------------------------------
 * The private section for the pqheap looks like this:

 */

/* Implementation notes: constructor
 * ---------------------------------
 *
 */
PQueue::PQueue()
{
    elements = new int[2];
    numAllocated = 2;
    numUsed = 0;
}

PQueue::~PQueue()
{
    delete[] elements;
}

bool PQueue::isEmpty()
{
    return (size() == 0);
}

/* Implementation notes: size
 * --------------------------
 *
 */
int PQueue::size()
{
    return numUsed;
}


/* Implementation notes: enqueue
 * -----------------------------
 *
 */
void PQueue::enqueue(int newValue)
{
    
}


/* Implementation notes: dequeueMax
 * --------------------------------
 *
 */
int PQueue::dequeueMax()
{
    return 0;
}


/* Implementation notes: bytesUsed
 * -------------------------------
 *
 */
int PQueue::bytesUsed()
{
    return 0;
}
	

string PQueue::implementationName()
{
	return "heap";
}

/*
 * Implementation notes: printDebuggingInfo
 * ----------------------------------------
 *
 */
void PQueue::printDebuggingInfo()
{
    int count = 0;
    
    cout << "------------------ START DEBUG INFO ------------------" << endl;
    
    cout << "------------------ END DEBUG INFO ------------------" << endl;
}
