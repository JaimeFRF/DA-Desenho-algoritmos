// By: Gonçalo Leão

#include "exercises.h"

#include "TestAux.h"

void bfsAux(Vertex* v, std::vector<int> &res){
    std::queue<Vertex*> q;
    q.push(v);
    v->setVisited(true);
    res.push_back(v->getId());
    while(!q.empty()){
        Vertex* u = q.front();
        q.pop();
        for(Edge* w : u->getAdj()){
            if(!w->getDest()->isVisited()){
                res.push_back(w->getDest()->getId());
                q.push(w->getDest());
                w->getDest()->setVisited(true);
            }
        }
    }

}

std::vector<int> IntroGraph::bfs(const int & source) const {
    std::vector<int> res;
    bfsAux(findVertex(source), res);
    // TODO
    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex3, test_bfs) {
    IntroGraph graph;
    createNetwork(graph);
    std::vector<int> vs = graph.bfs(1);

    unsigned int ids[] = {1, 2, 3, 4, 5, 6, 7};
    EXPECT_EQ(vs.size(), 7);
    for (unsigned int i = 0; i < vs.size(); i++) {
        EXPECT_EQ(vs[i], ids[i]);
    }
}