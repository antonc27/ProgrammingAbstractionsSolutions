/* Implementation notes: PQueue class
 * ----------------------------------
 * The private section for the pqheap looks like this:

 */

/* Implementation notes: constructor
 * ---------------------------------
 *
 */
template <typename ElemType>
PQueue<ElemType>::PQueue(int (cmp)(ElemType, ElemType))
{
    cmpFn = cmp;
    elements = new ElemType[2];
    numAllocated = 2;
    numUsed = 0;
}

template <typename ElemType>
PQueue<ElemType>::~PQueue()
{
    delete[] elements;
}

template <typename ElemType>
bool PQueue<ElemType>::isEmpty()
{
    return (size() == 0);
}

/* Implementation notes: size
 * --------------------------
 *
 */
template <typename ElemType>
int PQueue<ElemType>::size()
{
    return numUsed;
}


/* Implementation notes: enqueue
 * -----------------------------
 *
 */
template <typename ElemType>
void PQueue<ElemType>::enqueue(ElemType newValue)
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
template <typename ElemType>
ElemType PQueue<ElemType>::dequeueMax()
{
    if (isEmpty())
        Error("Tried to dequeue max from an empty pqueue!");
    
    ElemType max = elements[0];
    swap(0, numUsed - 1);
    numUsed--;
    heapify();
    return max;
}


/* Implementation notes: bytesUsed
 * -------------------------------
 *
 */
template <typename ElemType>
int PQueue<ElemType>::bytesUsed()
{
    return sizeof(*this) + sizeof(ElemType)*numAllocated;
}
	
template <typename ElemType>
string PQueue<ElemType>::implementationName()
{
	return "templetazed heap";
}

/*
 * Implementation notes: printDebuggingInfo
 * ----------------------------------------
 *
 */
template <typename ElemType>
void PQueue<ElemType>::printDebuggingInfo()
{
//    cout << "------------------ START DEBUG INFO ------------------" << endl;
//    int i, sum;
//    for (sum = 0, i = 1; sum < numUsed; sum += i, i *= 2) {
//        for (int j = sum; j < sum + i && j < numUsed; j++) {
//            cout << elements[j] << " ";
//        }
//        cout << endl;
//    }
//    cout << "------------------ END DEBUG INFO ------------------" << endl;
}

template <typename ElemType>
void PQueue<ElemType>::enlargeCapacity()
{
    numAllocated *= 2;
    ElemType *newArray = new ElemType[numAllocated];
    for (int i = 0; i < numUsed; i++)
        newArray[i] = elements[i];
    delete[] elements;
    elements = newArray;
}

template <typename ElemType>
void PQueue<ElemType>::bubbleUp()
{
    int childIdx = numUsed - 1;
    int parentIdx = (childIdx - 1) / 2;
    while (childIdx > 0 && childIdx != parentIdx && compareIfLeftGreaterThenRight(childIdx, parentIdx)) {
        swap(childIdx, parentIdx);
        childIdx = parentIdx;
        parentIdx = (childIdx - 1) / 2;
    }
}

template <typename ElemType>
void PQueue<ElemType>::heapify()
{
    int parentIdx = 0;
    int leftChildIdx = 2*parentIdx + 1;
    int rightChildIdx = 2*parentIdx + 2;
    while (true) {
        if (leftChildIdx >= numUsed) {
            break;
        }
        if (rightChildIdx >= numUsed) {
            if (compareIfLeftGreaterThenRight(leftChildIdx, parentIdx)) {
                swap(leftChildIdx, parentIdx);
                parentIdx = leftChildIdx;
            }
            break;
        }
        
        bool isLeftChildGreaterThenParent = compareIfLeftGreaterThenRight(leftChildIdx, parentIdx);
        bool isRightChildGreaterThenParent = compareIfLeftGreaterThenRight(rightChildIdx, parentIdx);
        if (isLeftChildGreaterThenParent || isRightChildGreaterThenParent) {
            if (compareIfLeftGreaterThenRight(leftChildIdx, rightChildIdx)) {
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

template <typename ElemType>
bool PQueue<ElemType>::compareIfLeftGreaterThenRight(int left, int right)
{
    return cmpFn(elements[left], elements[right]) > 0;
}

template <typename ElemType>
void PQueue<ElemType>::swap(int i, int j)
{
    ElemType tmp = elements[i];
    elements[i] = elements[j];
    elements[j] = tmp;
}
