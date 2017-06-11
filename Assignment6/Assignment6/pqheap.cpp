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
    if (numAllocated == numUsed)
        enlargeCapacity();
    elements[numUsed] = newValue;
    numUsed++;
    bubbleUp();
}


/* Implementation notes: dequeueMax
 * --------------------------------
 *
 */
int PQueue::dequeueMax()
{
    if (isEmpty())
        Error("Tried to dequeue max from an empty pqueue!");
    
    int max = elements[0];
    swap(0, numUsed - 1);
    numUsed--;
    heapify();
    return max;
}


/* Implementation notes: bytesUsed
 * -------------------------------
 *
 */
int PQueue::bytesUsed()
{
    return sizeof(*this) + sizeof(int)*numAllocated;
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
    cout << "------------------ START DEBUG INFO ------------------" << endl;
    int i, sum;
    for (sum = 0, i = 1; sum < numUsed; sum += i, i *= 2) {
        for (int j = sum; j < sum + i && j < numUsed; j++) {
            cout << elements[j] << " ";
        }
        cout << endl;
    }
    cout << "------------------ END DEBUG INFO ------------------" << endl;
}

void PQueue::enlargeCapacity()
{
    numAllocated *= 2;
    int *newArray = new int[numAllocated];
    for (int i = 0; i < numUsed; i++)
        newArray[i] = elements[i];
    delete[] elements;
    elements = newArray;
}

void PQueue::bubbleUp()
{
    int childIdx = numUsed - 1;
    int parentIdx = (childIdx - 1) / 2;
    while (childIdx > 0 && childIdx != parentIdx && elements[childIdx] > elements[parentIdx]) {
        swap(childIdx, parentIdx);
        childIdx = parentIdx;
        parentIdx = (childIdx - 1) / 2;
    }
}

void PQueue::heapify()
{
    int parentIdx = 0;
    int leftChildIdx = 2*parentIdx + 1;
    int rightChildIdx = 2*parentIdx + 2;
    while (true) {
        if (leftChildIdx >= numUsed) {
            break;
        }
        if (rightChildIdx >= numUsed) {
            if (elements[leftChildIdx] > elements[parentIdx]) {
                swap(leftChildIdx, parentIdx);
                parentIdx = leftChildIdx;
            }
            break;
        }
        
        if (max(elements[leftChildIdx], elements[rightChildIdx]) > elements[parentIdx]) {
            if (elements[leftChildIdx] > elements[rightChildIdx]) {
                swap(leftChildIdx, parentIdx);
                parentIdx = leftChildIdx;
            } else {
                swap(rightChildIdx, parentIdx);
                parentIdx = rightChildIdx;
            }
        } else {
            break;
        }
        
        leftChildIdx = 2*parentIdx + 1;
        rightChildIdx = 2*parentIdx + 2;
    }
}

void PQueue::swap(int i, int j)
{
    int tmp = elements[i];
    elements[i] = elements[j];
    elements[j] = tmp;
}
