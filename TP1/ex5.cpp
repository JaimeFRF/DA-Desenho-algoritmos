// By: Gonçalo Leão

#include "exercises.h"

void dfsEX5(Vertex* v, bool &res){
    v->setProcesssing(true);

    for(Edge* edge : v->getAdj()){
        if(edge->getDest()->isProcessing())
            res = false;
        else if(!v->isVisited()){
            dfsEX5(edge->getDest(), res);
        }
    }
    v->setProcesssing(false);
    v->setVisited(true);

}

bool IntroGraph::isDAG() const {
    bool res = true;

    for(Vertex* v : vertexSet){
        v->setVisited(false);
        v->setProcesssing(false);
    }

    for(Vertex* v : vertexSet){
        if(!v->isVisited()){
            dfsEX5(v, res);
        }
    }
    // TODO
    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex5, test_isDAG) {
    IntroGraph myGraph;

    for(unsigned int i = 0; i < 6; i++) {
        myGraph.addVertex(i);
    }

    myGraph.addEdge(1, 2, 0);
    myGraph.addEdge(2, 5, 0);
    myGraph.addEdge(5, 4, 0);
    myGraph.addEdge(3, 1, 0);
    myGraph.addEdge(0, 4, 0);

    EXPECT_EQ(myGraph.isDAG(), true);

    myGraph.addEdge(4, 1, 0);

    EXPECT_EQ(myGraph.isDAG(), false);
}