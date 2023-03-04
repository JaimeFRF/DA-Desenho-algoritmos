// By: Gonçalo Leão

#include "exercises.h"

#include <algorithm>

struct Product{
    double value;
    double weight;
    double relation;
    int id;
};

bool productCompare(Product p1, Product p2){
    return (p1.relation > p2.relation);
}

double fractionalKnapsackGR(unsigned int values[], unsigned int weights[], unsigned int n, unsigned int maxWeight, double usedItems[]) {

    double res = 0.0;
    std::vector<Product> products;

    for(int i = 0; i < n; i++){
        Product product;
        product.id = i;
        product.value = values[i];
        product.weight = weights[i];
        product.relation = values[i] / weights[i];
        products.push_back(product);
    }
    std::sort(products.begin(), products.end(), productCompare);



    for(Product product : products){
        if(product.weight <= maxWeight){
            maxWeight -= product.weight;
            usedItems[product.id]++;
            res += product.value;
        }
        else{
            double aux = (double)maxWeight / product.weight;
            res += aux * product.value;
            usedItems[product.id] = aux;
            maxWeight -= (aux * (double)product.weight);
        }
    }

    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex4, testFractionalKnapsack_3items) {
    const unsigned int n = 3;
    {
        unsigned int values[n] = {60, 100, 120};
        unsigned int weights[n] = {10, 20, 30};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsackGR(values, weights, n, 50, usedItems), 240.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 2.0/3.0, 0.00001);
    }
}

TEST(TP3_Ex4, testFractionalKnapsack_7items) {
    const unsigned int n = 7;
    {
        unsigned int values[n] = {10, 5, 15, 7, 6, 18, 3};
        unsigned int weights[n] = {2, 3, 5, 7, 1, 4, 1};
        double usedItems[n];

        EXPECT_NEAR(fractionalKnapsackGR(values, weights, n, 15, usedItems), 52.0 + 10.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[0], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[1], 2.0/3.0, 0.00001);
        EXPECT_NEAR(usedItems[2], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[3], 0.0, 0.00001);
        EXPECT_NEAR(usedItems[4], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[5], 1.0, 0.00001);
        EXPECT_NEAR(usedItems[6], 1.0, 0.00001);
    }
}