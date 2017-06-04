#include "pqueue.h"
#include "genlib.h"
#include <iostream>


/* Implementation notes: PQueue class
 * ----------------------------------
 * The private section for the pqchunklist looks like this:

 */



/* Implementation notes: constructor
 * ---------------------------------
 *
 */
PQueue::PQueue()
{
    
}

PQueue::~PQueue()
{
    
}

bool PQueue::isEmpty()
{
    return true;
}

/* Implementation notes: size
 * --------------------------
 *
 */
int PQueue::size()
{
    return 0;
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
	if (isEmpty())
		Error("Tried to dequeue max from an empty pqueue!");
	
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
	return "chunk list";
}

/*
 * Implementation notes: printDebuggingInfo
 * ----------------------------------------
 *
 */
void PQueue::printDebuggingInfo()
{
    cout << "------------------ START DEBUG INFO ------------------" << endl;

    cout << "------------------ END DEBUG INFO ------------------" << endl;
}

