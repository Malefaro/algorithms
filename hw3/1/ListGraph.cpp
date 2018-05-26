#include "ListGraph.hpp"


ListGraph::ListGraph(int count)
{
    adjacencyLists.resize(count);
}

ListGraph::ListGraph(const IGraph& graph)
{
    adjacencyLists.resize(graph.VerticesCount());
    for( int from = 0; from < adjacencyLists.size(); from++ )
        graph.GetNextVertices(from, adjacencyLists[from]);
}

ListGraph::~ListGraph() {}

void ListGraph::AddEdge(int from, int to)
{
    assert( from >= 0 && from < adjacencyLists.size() );
    assert( to >= 0 && to < adjacencyLists.size() );
    adjacencyLists[from].push_back(to);
    adjacencyLists[to].push_back(from);
}

int ListGraph::VerticesCount() const
{
    return adjacencyLists.size();
}

void ListGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const
{
    assert( vertex >= 0 && vertex < adjacencyLists.size() );
    vertices = adjacencyLists[vertex];
}

void ListGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const
{
    assert( vertex >= 0 && vertex < adjacencyLists.size() );

    vertices.clear();
    for( int from = 0; from < adjacencyLists.size(); from++ )
        for( int i = 0; i < adjacencyLists[from].size(); i++ )
            if( adjacencyLists[from][i] == vertex )
                vertices.push_back(from);
}
