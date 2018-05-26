#include "MatrixGraph.hpp"

void MatrixGraph::AddEdge(int from, int to) {
    assert( (from >= 0 && from < Matrix.size()) && (to >= 0 && to < Matrix.size()) );
    Matrix[from][to] = true;
    Matrix[to][from] = true;
}

int MatrixGraph::VerticesCount() const {
    return Matrix.size();
}

void MatrixGraph::GetNextVertices(int vertex, std::vector<int> &vertices) const {
    assert(vertex >= 0 && vertex < Matrix.size());
    for ( int i = 0; i < Matrix.size(); ++i)
        if (Matrix[vertex][i] == true)
            vertices.push_back(i);
}

void MatrixGraph::GetPrevVertices(int vertex, std::vector<int> &vertices) const {
    assert(vertex >= 0 && vertex < Matrix.size());
    GetNextVertices(vertex, vertices);
}

MatrixGraph::MatrixGraph(const IGraph &graph) {
    Matrix.resize(graph.VerticesCount());
    for (auto obj : Matrix)
        obj.resize(graph.VerticesCount(), false);
    for ( int i = 0; i < graph.VerticesCount(); ++i){
        vector<int> vertices;
        graph.GetNextVertices(i, vertices);
        for (auto obj : vertices){
            Matrix[i][obj] = true;
            Matrix[obj][i] = true;
        }
    }
}

MatrixGraph::MatrixGraph(int size) {
    Matrix.resize(size, vector<bool>(size,false));
//    for ( auto obj : Matrix)
//        obj.resize(size, false);
}
