#include "SetGraph.hpp"

void SetGraph::AddEdge(int from, int to) {
    assert( (from >= 0 && from < Set.size()) && (to >= 0 && to < Set.size()) );
    Set[from].insert(to);
    Set[to].insert(from);
}

int SetGraph::VerticesCount() const {
    return Set.size();
}

void SetGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    for (int i = 0; i<Set.size(); ++i) {
        if (Set[vertex].find(i) != Set[vertex].end())
            vertices.push_back(i);
    }
}

void SetGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    GetNextVertices(vertex, vertices);
}

SetGraph::SetGraph(const IGraph &graph) {
    Set.resize(graph.VerticesCount());
    for (int i = 0; i < graph.VerticesCount(); ++i){
        vector<int> vertices;
        graph.GetNextVertices(i , vertices);
        for ( auto obj : vertices){
            Set[i].insert(obj);
            Set[obj].insert(i);
        }
    }
}

SetGraph::SetGraph(int size) {
    Set.resize(size);
}
