// By: Gonçalo Leão

#include "exercises.h"

#include "MSTTestAux.h"

std::vector<Vertex *> GreedyGraph::prim() {
    MutablePriorityQueue<Vertex> q;
    std::vector<Vertex *> res;

    for(Vertex* vertex : vertexSet){
        vertex->setDist(INF);
        vertex->setVisited(false); //is not in the mstSet
        q.insert(vertex);
    }
    vertexSet[0]->setDist(0);

    while(!q.empty()){
        Vertex* v = q.extractMin();
        if(!v->isVisited()){
            for(Edge* edge : v->getAdj()){
                Vertex* destVertex = edge->getDest();
                if(!destVertex->isVisited() && edge->getWeight() < destVertex->getDist()){
                    destVertex->setDist(edge->getWeight());
                    q.decreaseKey(destVertex);
                    destVertex->setPath(edge);
                }
            }
        }
        v->setVisited(true);
        res.push_back(v);
    }
    return res;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <chrono>

TEST(TP3_Ex5, test_prim) {
    GreedyGraph graph = createMSTTestGraph();
    std::vector<Vertex *> res = graph.prim();

    std::stringstream ss;
    for(const auto v : res) {
        ss << v->getId() << "<-";
        if ( v->getPath() != nullptr ) {
            ss << v->getPath()->getOrig()->getId();
        }
        ss << "|";
    }
    std::cout << ss.str() << std::endl;

    EXPECT_TRUE(isSpanningTree(res));
    EXPECT_EQ(spanningTreeCost(res), 11);
}

TEST(TP3_Ex5, test_performance_prim) {
    //Change these const parameters as needed
    const int MIN_SIZE = 10;
    const int MAX_SIZE = 30; //Try with 100
    const int STEP_SIZE = 10;
    const int N_REPETITIONS = 50;
    for (int n = MIN_SIZE; n <= MAX_SIZE; n += STEP_SIZE) {
        GreedyGraph g;
        generateRandomGridGraph(n, g);
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 1; i <= N_REPETITIONS; i++)
            g.prim();
        auto finish = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
        std::cout << "Processing grid (Prim) " << n << " x " << n << " average time (milliseconds)=" << (elapsed / N_REPETITIONS) << std::endl;
    }
}
