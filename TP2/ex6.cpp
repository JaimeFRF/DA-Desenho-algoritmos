// By: Gonçalo Leão

#include "exercises.h"
#include <iostream>
unsigned int knapsackBF(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, bool usedItems[]) {

    for(int i = 0; i < n;i++){
        usedItems[i] = false;
    }
    unsigned int K[n + 1][maxWeight + 1];

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= maxWeight; j++){
            if(i == 0 || j == 0)
                K[i][j] = 0;
            else if(weights[i - 1] <= maxWeight && (j >= weights[i - 1])){
                unsigned int temp = std::max(K[i - 1][j], values[i - 1] + K[i - 1][j - weights[i - 1]]);
                K[i][j] = temp;
            }
            else
                K[i][j] = K[i - 1][j];
        }
    }
    int w = maxWeight;
    int res =K[n][maxWeight];
    for (int i = n; i > 0 && res > 0; i--) {

        if (res == K[i - 1][w])
            continue;
        else {
                res = res - values[i - 1];
                w = w - weights[i - 1];
                usedItems[i - 1]  =true;
        }
    }

    return K[n][maxWeight];
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP2_Ex6, testKnapsack_4items) {
    const unsigned int n = 4;
    {
        unsigned int values[n] = {10, 7, 11, 15};
        unsigned int weights[n] = {1, 2, 1, 3};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 5, usedItems), 36);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], false);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
    }

    {
        unsigned int values[n] = {3, 4, 5, 6};
        unsigned int weights[n] = {2, 3, 4, 5};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 5, usedItems), 7);
        EXPECT_EQ(usedItems[0], true);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], false);
        EXPECT_EQ(usedItems[3], false);
    }
}

TEST(TP2_Ex6, testKnapsack_5items) {
    const unsigned int n = 5;
    {
        unsigned int values[n] = {1, 2, 5, 9, 4};
        unsigned int weights[n] = {2, 3, 3, 4, 6};
        bool usedItems[n];

        EXPECT_EQ(knapsackBF(values, weights, n, 10, usedItems), 16);
        EXPECT_EQ(usedItems[0], false);
        EXPECT_EQ(usedItems[1], true);
        EXPECT_EQ(usedItems[2], true);
        EXPECT_EQ(usedItems[3], true);
        EXPECT_EQ(usedItems[4], false);
    }
}