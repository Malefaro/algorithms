#ifndef INC_1_ARCGRAPH_HPP
#define INC_1_ARCGRAPH_HPP

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

struct IGraph {
    virtual ~IGraph() {}
    virtual void AddEdge(int from, int to) = 0;
    virtual int VerticesCount() const  = 0;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;
};

class ArcGraph : public IGraph{
public:
    virtual ~ArcGraph() override {}
    virtual void AddEdge(int from, int to) override ;
    virtual int VerticesCount() const  override ;
    virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const override ;
    virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const override ;
    ArcGraph(const IGraph& graph);
    ArcGraph();
    ArcGraph(int size);
private:
    struct node
    {
        node() = default;
        node(int f, int t) : from(f) , to(t) {}
        int from;
        int to;
        friend bool operator == (const node& n1, const node& n2){
            return (n1.from == n2.from) && (n1.to == n2.to);
        }
    };
    vector<node> Arcs;

};

#endif //INC_1_ARCGRAPH_HPP
