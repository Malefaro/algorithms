#include "ArcGraph.hpp"

void ArcGraph::AddEdge(int from, int to) {
    assert( (from >= 0 && from < Arcs.size()) && (to >= 0 && to < Arcs.size()) );
    node tmp(from,to);
    node tmp2(to,from);
    for (auto obj : Arcs){
        if(obj == tmp || obj == tmp2)
            return;
    }
    Arcs.push_back(tmp);
    Arcs.push_back(tmp2);
}

int ArcGraph::VerticesCount() const {
    return Arcs.size();
}

void ArcGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    for( auto obj : Arcs)
        if( obj.from == vertex)
            vertices.push_back(obj.to);
}

void ArcGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    for( auto obj : Arcs)
        if( obj.to == vertex)
            vertices.push_back(obj.from);
}

ArcGraph::ArcGraph(const IGraph &graph) {
    Arcs.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i) {
        std::vector<int> vertices;
        graph.GetNextVertices(i, vertices);
        for (auto &obj : vertices) {
            Arcs.push_back(node(i, obj));
        }
    }
}

ArcGraph::ArcGraph(int size) {
    Arcs.resize(size);
}
