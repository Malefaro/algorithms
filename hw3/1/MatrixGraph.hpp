#ifndef INC_1_MATRIXGRAPH_HPP
#define INC_1_MATRIXGRAPH_HPP

#include <iostream>
#include <vector>
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

class MatrixGraph : public IGraph{
public:
    virtual ~MatrixGraph() override {}
    virtual void AddEdge(int from, int to) override ;
    virtual int VerticesCount() const  override ;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const override ;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const override ;
    MatrixGraph(const IGraph& graph);
    MatrixGraph();
    MatrixGraph(int size);
private:
    vector<vector<bool>> Matrix;
};

#endif //INC_1_MATRIXGRAPH_HPP
