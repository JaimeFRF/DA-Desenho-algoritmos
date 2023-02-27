// By: Gonçalo Leão

#include "exercises.h"

int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int max = INT16_MIN;

    for(int h = 0; h < (n - 1); h++){
        int res = A[h];
        for(int k = (h + 1); k < n; k++){
            res += A[k];
            if(res > max){
                max = res;
                i = h;
                j = k;
            }
        }
    }
    int res = 0;
    for(int h = i; h < (j + 1); h++){
        res += A[h];
    }

    return res;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex3, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceBF(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}