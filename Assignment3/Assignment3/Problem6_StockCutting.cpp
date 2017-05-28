//
//  Problem6_StockCutting.cpp
//  Assignment3
//
//  Created by AC27 on 30/03/17.
//  Copyright © 2017 AC27. All rights reserved.
//

#include "Problem6_StockCutting.h"
#include <iostream>
#include "simpio.h"
#include "vector.h"

void printVector(Vector<int> value) {
    for (int i = 0; i < value.size(); i++) {
        cout << value[i];
        if (i != value.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

int calculateStocks(Vector<int> &arrangment, int stockLength) {
    int totalStocks = 0;
    int localStockSum = 0;
    for (int i=0; i<arrangment.size(); i++) {
        int length = arrangment[i];
        localStockSum += length;
        if (localStockSum >= stockLength) {
            totalStocks++;
            if (localStockSum == stockLength) {
                localStockSum = 0;
            } else {
                localStockSum = length;
            }
        }
    }
    if (localStockSum > 0) {
        totalStocks++;
    }
    return totalStocks;
}

int CutStockRec(Vector<int> &requests, Vector<int> permutations, int stockLength, int currentMin) {
    if (requests.size() == 0) {
//        printVector(permutations);
        int c = calculateStocks(permutations, stockLength);
//        cout << "num " << c << endl;
        return c;
    }
    for (int i=0; i<requests.size(); i++) {
        int elem = requests[i];
        Vector<int> copyRequests = requests;
        Vector<int> copyPermutaitons = permutations;
        
        copyRequests.removeAt(i);
        copyPermutaitons.add(elem);
        currentMin = std::min(currentMin, CutStockRec(copyRequests, copyPermutaitons, stockLength, currentMin));
    }
    return currentMin;
}

int CutStockRecAlter(Vector<int> &requests, int stockLength, int currentMin, int totalStocks, int currentStockSum) {
    if (requests.size() == 0) {
        if (currentStockSum > 0) {
            totalStocks++;
        }
        
        return std::min(totalStocks, currentMin);
    }
    if (totalStocks >= currentMin) {
        return currentMin;
    }
    
    for (int i=0; i<requests.size(); i++) {
        int length = requests[i];
        Vector<int> copyRequests = requests;
        copyRequests.removeAt(i);
        
        int newTotalStocks = totalStocks;
        int newCurrentStockSum = currentStockSum;
        
        newCurrentStockSum += length;
        if (newCurrentStockSum >= stockLength) {
            newTotalStocks++;
            if (newCurrentStockSum == stockLength) {
                newCurrentStockSum = 0;
            } else {
                newCurrentStockSum = length;
            }
        }
        
        currentMin = std::min(currentMin, CutStockRecAlter(copyRequests, stockLength, currentMin, newTotalStocks, newCurrentStockSum));
    }
    
    return currentMin;
}

int CutStock(Vector<int> &requests, int stockLength) {
    Vector<int> p;
//    return CutStockRec(requests, p, stockLength, INT_MAX);
    return CutStockRecAlter(requests, stockLength, INT_MAX, 0, 0);
}

int Problem6_StockCutting_main() {
    Vector<int> requests;
//    requests.add(4);
//    requests.add(3);
//    requests.add(4);
//    requests.add(1);
//    requests.add(7);
//    requests.add(8);
    
    requests.add(4);
    requests.add(3);
    requests.add(4);
    requests.add(1);
    requests.add(7);
    requests.add(8);
    requests.add(1);
    requests.add(9);
    requests.add(9);
    requests.add(2);
    requests.add(2);
    
//    requests.add(7);
//    requests.add(8);
//    requests.add(4);
//    requests.add(3);
//    requests.add(4);
//    requests.add(1);
    
//    requests.add(4);
//    requests.add(4);
//    requests.add(1);
//    requests.add(3);
//    requests.add(7);
//    requests.add(8);
    
//    printVector(requests);
    cout << CutStock(requests, 10) << endl;
//    cout << calculateStocks(requests, 10) << endl;
    return 0;
}
