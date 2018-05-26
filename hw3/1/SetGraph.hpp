#ifndef INC_1_SETGRAPH_HPP
#define INC_1_SETGRAPH_HPP

#include <iostream>
#include <vector>
#include <unordered_set>
#include <cassert>

using namespace std;

#ifndef __IGRAPH__
#define __IGRAPH__

struct IGraph {
    virtual ~IGraph() {}
    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const  = 0;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;
};
#endif

class SetGraph : public IGraph{
public:
    virtual ~SetGraph() override {}
    virtual void AddEdge(int from, int to) override ;
    virtual int VerticesCount() const  override ;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const override ;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const override ;
    SetGraph(const IGraph& graph);
    SetGraph();
    SetGraph(int size);
private:
    vector<unordered_set<int>> Set;
};

#endif //INC_1_SETGRAPH_HPP
