#ifndef INC_1_LISTGRAPH_HPP
#define INC_1_LISTGRAPH_HPP

#include<vector>
#include<iostream>
#include<queue>
#include<assert.h>

using std::vector;
using std::cout;
using std::queue;

#ifndef __IGRAPH__
#define __IGRAPH__
struct IGraph {
    virtual ~IGraph() {}

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;
};
#endif // __IGRAPH__

class ListGraph : public IGraph {
public:
    ListGraph(int count);
    ListGraph(const IGraph& graph);
    virtual ~ListGraph();

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to);

    virtual int VerticesCount() const;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const;

private:
    vector<vector<int>> adjacencyLists;
};

#endif //INC_1_LISTGRAPH_HPP
