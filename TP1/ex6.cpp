// By: Gonçalo Leão

#include "exercises.h"
#include <algorithm>
#include "TestAux.h"

void dfs_scc(Vertex* v, int &time, std::vector<int> &disc, std::vector<int> &low, std::stack<Vertex*> &stack, std::vector<bool> &inStack, std::vector<std::vector<int>> &sccs){
    disc[v->getId()] = time;
    low[v->getId()] = time;
    inStack[v->getId()] = true;
    time++;
    stack.push(v);

    for(Edge* edge : v->getAdj()){
        Vertex* w = edge->getDest();

        if(disc[w->getId()] == -1){
            dfs_scc(w, time, disc, low, stack, inStack, sccs);
            low[v->getId()] = std::min(low[v->getId()], low[w->getId()]);
        }

        else if(inStack[w->getId()]){
            low[v->getId()] = std::min(low[v->getId()], disc[w->getId()]);
        }

    }

    if(disc[v->getId()] == low[v->getId()]){
        std::vector<int> newScc;
        int w;
        do {
            w = stack.top()->getId();
            stack.pop();
            inStack[w] = false;
            newScc.push_back(w);
        } while (w != v->getId());
        sccs.push_back(newScc);
    }

}

std::vector<std::vector<int>> IntroGraph::computeSCCs() const {
    std::vector<std::vector<int>> sccs;

    int n = vertexSet.size(); //number of vertex in the graph
    std::vector<int> disc(n + 1, -1); //order in which they are visited
    std::vector<int> low(n + 1, -1); //lowest num value of any node reachable from the current one
    std::vector<bool> inStack(n + 1, false); //check if it is in stack
    std::stack<Vertex*> stack;
    int time = 1;

    for(Vertex* v : vertexSet){
        if(disc[v->getId()] == -1){
            dfs_scc(vertexSet[v->getId()-1], time, disc, low, stack, inStack, sccs);
        }
    }

    return sccs;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex6, test_SCC) {
    IntroGraph graph;
    createNetwork(graph);
    std::vector<std::vector<int>> sccs = graph.computeSCCs();

    EXPECT_EQ(sccs.size(), 3);
    EXPECT_THAT(sccs,  ::testing::UnorderedElementsAre(::testing::UnorderedElementsAre(1,2,3,5,6), ::testing::UnorderedElementsAre(4), ::testing::UnorderedElementsAre(7)));

    IntroGraph graph2;
    for(unsigned int i = 1; i <= 5; i++) {
        graph2.addVertex(i);
    }
    graph2.addEdge(1,3,0);
    graph2.addEdge(1,4,0);
    graph2.addEdge(2,1,0);
    graph2.addEdge(3,2,0);
    graph2.addEdge(4,5,0);
    sccs = graph2.computeSCCs();

    EXPECT_EQ(sccs.size(), 3);
    EXPECT_THAT(sccs,  ::testing::UnorderedElementsAre(::testing::UnorderedElementsAre(1,2,3), ::testing::UnorderedElementsAre(4), ::testing::UnorderedElementsAre(5)));
}