#include "exercises.h"

#include <cmath>

Result nearestPointsBF(std::vector<Point> &vp) {
    Result res;
    res.dmin = INT16_MAX;
    for(Point x : vp){
        for(Point y : vp){
            if(!(x == y || x.distance(y) >= res.dmin)){
                res.dmin = x.distance(y);
                res.p1 = x;
                res.p2 = y;
            }
        }
    }

    return res;
}

/// TESTS ///
#include "gtest/gtest.h"

TEST(TP2_Ex5, testNPBF) {
    testNearestPoints(nearestPointsBF, "Brute force");
}