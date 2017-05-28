#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "vector.h"

int MaxSubvectorBrutForce(Vector<int> &v) {
    int sum = INT_MIN;
    int n = v.size();
    for (int i=0; i<n; i++) {
        for (int j=i; j<n; j++) {
            int localSum = 0;
            for (int p=i; p<=j; p++) {
                localSum += v[p];
            }
            sum = max(sum, localSum);
        }
    }
    return sum;
}

int MaxSubvectorReuse(Vector<int> &v) {
    int sum = INT_MIN;
    int n = v.size();
    for (int i=0; i<n; i++) {
        int interSum = 0;
        for (int j=i; j<n; j++) {
            interSum += v[j];
            sum = max(sum, interSum);
        }
    }
    return sum;
}

int MaxSum(int L, int U, Vector<int> &vec) {
    /* Zero-element vector */
    if (L > U) {
        return 0;
    }
    /* One-element vector */
    if (L == U) {
        return max(0, vec[L]);
    }
    /* The left half of the recusion is vec[L...M], the right is
     vec[M+1...U] */
    int M = (L+U)/2;
    /* Find max touching the border on the left */
    int SumLeft = 0;
    int MaxToLeft = 0;
    for (int I = M; I >= L; I--) { /* M is more than L, so I decreases from M to L */
        SumLeft = SumLeft + vec[I];
        MaxToLeft = max(MaxToLeft, SumLeft);
    }
    /* Find max touching the border on the right */
    int SumRight = 0;
    int MaxToRight = 0;
    for (int I = M+1; I <= U; I++) {
        SumRight = SumRight +vec[I];
        MaxToRight = max(MaxToRight, SumRight);
    }
    /* MaxCrossing is the maximum subvector sum which crosses the
     border */
    int MaxCrossing = MaxToLeft + MaxToRight;
    int MaxInLeftHalf = MaxSum(L, M, vec);
    int MaxInRightHalf = MaxSum(M+1, U, vec);
    return max(max(MaxCrossing, MaxInLeftHalf), MaxInRightHalf);
}

int MaxSumWrapper(Vector<int> &v) {
    return MaxSum(0, v.size() - 1, v);
}

int MaxSubvectorSumClever(Vector<int> &v) {
    int maxSum = v[0];
    int rightMaxSum = v[0];
    for (int i=1; i<v.size(); i++) {
        int next = v[i];
        rightMaxSum = max(rightMaxSum + next, next);
        maxSum = max(rightMaxSum, maxSum);
    }
    return maxSum;
}

int main()
{
    Vector<int> v;
    v.add(2);
    v.add(-5);
    v.add(12);
    v.add(9);
    v.add(-3);
    v.add(10);
    
    cout << MaxSubvectorBrutForce(v) << endl;
    cout << MaxSubvectorReuse(v) << endl;
    cout << MaxSumWrapper(v) << endl;
    cout << MaxSubvectorSumClever(v) << endl;
    
	return 0;
}
