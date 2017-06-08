#include "pqueue.h"
#include "genlib.h"
#include <iostream>


/* Implementation notes: PQueue class
 * ----------------------------------
 * The private section for the pqchunklist looks like this:

 */

const int MaxElemsPerBlock = 5;

/* Implementation notes: constructor
 * ---------------------------------
 *
 */
PQueue::PQueue()
{
    head = NULL;
}

PQueue::~PQueue()
{
    while (head != NULL) {
        Chunk *next = head->next;
        delete head->values;
        delete head;
        head = next;
    }
}

bool PQueue::isEmpty()
{
    return (head == NULL);
}

/* Implementation notes: size
 * --------------------------
 *
 */
int PQueue::size()
{
    int count = 0;
    for (Chunk *cur = head; cur != NULL; cur = cur->next)
        count += cur->numUsed;
    return count;
}


/* Implementation notes: enqueue
 * -----------------------------
 *
 */
void PQueue::enqueue(int newValue)
{
    if (head == NULL) {
        head = newChunk();
        insertToChunk(newValue, head);
        return;
    }
    
    Chunk *previousChunk = NULL;
    Chunk *chunkToInsert = head;
    while (true) {
        if (chunkToInsert == NULL) {
            //allocate new chunk
            chunkToInsert = newChunk();
            if (previousChunk != NULL) {
                previousChunk->next = chunkToInsert;
            }
            // insert to current
            break;
        } else if (chunkToInsert->next == NULL) {
            // insert to current
            break;
        } else {
            int maxCurrent = chunkToInsert->values[0];
            int maxNext = chunkToInsert->next->values[0];
            
            if (newValue > maxCurrent || newValue > maxNext) {
                // insert to current
                break;
            } else {
                // go to next chunk
                previousChunk = chunkToInsert;
                chunkToInsert = chunkToInsert->next;
            }
        }
    }
    insertToChunk(newValue, chunkToInsert);
}


/* Implementation notes: dequeueMax
 * --------------------------------
 *
 */
int PQueue::dequeueMax()
{
	if (isEmpty())
		Error("Tried to dequeue max from an empty pqueue!");
	
    int max = head->values[0];
    head->numUsed--;
    for (int i = 0; i < head->numUsed; i++) {
        head->values[i] = head->values[i+1];
    }
    if (head->numUsed == 0) {
        Chunk *next = head->next;
        delete head->values;
        delete head;
        head = next;
    }
	return max;
}


/* Implementation notes: bytesUsed
 * -------------------------------
 *
 */
int PQueue::bytesUsed()
{
    int total = sizeof(*this);
    for (Chunk *cur = head; cur != NULL; cur = cur->next)
        total += sizeof(*cur) + sizeof(int)*cur->numUsed;
    return total;
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
    int count = 0;
    
    cout << "------------------ START DEBUG INFO ------------------" << endl;
    for (Chunk *cur = head; cur != NULL; cur = cur->next) {
        cout << "Chunk #" << count << " (at address " << cur << ") vals = [";
        for (int i = 0; i<cur->numUsed; i++) {
            cout << cur->values[i] << ", ";
        }
        cout << "] next = " << cur->next << endl;
        count++;
    }
    cout << "------------------ END DEBUG INFO ------------------" << endl;
}

PQueue::Chunk * PQueue::newChunk() {
    Chunk *chunk = new Chunk();
    chunk->values = new int[MaxElemsPerBlock];
    chunk->numUsed = 0;
    chunk->next = NULL;
    return chunk;
}

void PQueue::insertToChunk(int newValue, PQueue::Chunk *&chunkToInsert) {
    if (chunkToInsert->numUsed == 0) {
        chunkToInsert->values[0] = newValue;
        chunkToInsert->numUsed++;
    } else if (chunkToInsert->numUsed == MaxElemsPerBlock) {
        // split chunk
        int halfSize = MaxElemsPerBlock / 2 + 1;
        Chunk *nextNewChunk = newChunk();
        for (int i=halfSize; i<MaxElemsPerBlock; i++) {
            nextNewChunk->values[i - halfSize] = chunkToInsert->values[i];
        }
        chunkToInsert->numUsed = halfSize;
        nextNewChunk->numUsed = MaxElemsPerBlock - halfSize;
        
        nextNewChunk->next = chunkToInsert->next;
        chunkToInsert->next = nextNewChunk;
        
        if (nextNewChunk->values[0] > newValue) {
            insertToChunk(newValue, nextNewChunk);
        } else {
            insertToChunk(newValue, chunkToInsert);
        }
    } else {
        // must find right position in current chunk and shift values
        int insertPosition;
        for (insertPosition = 0; insertPosition < chunkToInsert->numUsed; insertPosition++) {
            if (chunkToInsert->values[insertPosition] < newValue) {
                break;
            }
        }
        // shift values
        for (int i = chunkToInsert->numUsed-1; i >= insertPosition; i--) {
            chunkToInsert->values[i+1] = chunkToInsert->values[i];
        }
        chunkToInsert->values[insertPosition] = newValue;
        chunkToInsert->numUsed++;
    }
}

