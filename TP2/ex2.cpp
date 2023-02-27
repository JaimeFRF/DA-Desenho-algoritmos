// By: Gonçalo Leão

#include <algorithm>
#include "exercises.h"

bool subsetSumBF(unsigned int A[], unsigned int n, unsigned int T, unsigned int subset[], unsigned int &subsetSize) {
    if(T == 0)
        return true;

    if(n == 0)
        return false;
    /*
    if(A[n -1] > T)
        return subsetSumBF(A, n - 1, T, subset, subsetSize);
        Is this necessary?
    */
    if(subsetSumBF(A, n - 1, T, subset, subsetSize)){
        return true;
    }

    if(subsetSumBF(A, n - 1, T - A[n - 1], subset, subsetSize)){
        subset[subsetSize] = A[n - 1];
        subsetSize++;
        return true;
    }


}

/// TESTS ///
#include <gtest/gtest.h>

unsigned int sum(unsigned int A[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

// Checks if A is a subset of B
bool isSubset(unsigned int A[], unsigned int nA, unsigned int B[], unsigned int nB) {
    for(unsigned int i = 0; i < nA; i++) {
        bool foundNum = false;
        for(unsigned int j = 0; j < nB; j++) {
            if(A[i] == B[j]) {
                foundNum = true;
                break;
            }
        }
        if(!foundNum) return false;
    }
    return true;
}

TEST(TP2_Ex2, testSubsetSum) {
    unsigned int A[] = {3, 34, 4, 12, 5, 2};
    unsigned int subset[6];
    unsigned int subsetSize = 0;

    unsigned int T = 9;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);

    subsetSize = 0;
    T = 20;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), true);
    EXPECT_EQ(sum(subset, subsetSize), T);
    EXPECT_EQ(isSubset(subset, subsetSize, A,6), true);
    subsetSize = 0;
    T = 30;
    EXPECT_EQ(subsetSumBF(A,6,T,subset,subsetSize), false);
}