#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "SetGraph.hpp"
#include "MatrixGraph.hpp"
#include "ListGraph.hpp"
#include "ArcGraph.hpp"

using namespace std;

int BFS(const IGraph& graph, int vertex,int to, void (*visit)(int))
{
    vector<bool> visited(graph.VerticesCount(), false);
    queue<int> qu;
    qu.push(vertex);
    visited[vertex] = true;
    vector<int> minpaths(graph.VerticesCount(), -1);
    int path = 1;
    int m = 0;
    while( qu.size() != 0 ) {
        int current = qu.front();
        qu.pop();
        //visit(current);
        if(!visited[current]) {
            vector<int> adjacentVertices;
            graph.GetNextVertices(current, adjacentVertices);
            if (adjacentVertices.empty() && current != to)
                minpaths[current] = -1;
//        if( find(adjacentVertices.begin(), adjacentVertices.end(), to) == adjacentVertices.end()){
//            minpaths[current]++;
//        }
            for (int i = 0; i < adjacentVertices.size(); i++) {
                if (!visited[adjacentVertices[i]]) {
                    qu.push(adjacentVertices[i]);
                    visited[adjacentVertices[i]] = true;
                }
                minpaths[adjacentVertices[i]] = path;
                if (m == 0)
                    m = adjacentVertices.size() + 1;
            }
            visited[current] = true;
        }
        m--;
        if (m == 0)
            path++;
        //m--;
    }

    int min = 2147483647;

    for (auto obj : minpaths){
        cout << obj << ' ';
        if ( obj < min && (obj != -1) )
            min = obj;
    }
    cout << endl;
    int k = 0;
    for (auto obj : minpaths){
        if(obj == min)
            ++k;
    }
    return k;
}

int findMin(const IGraph& graph, int u,int w,int n, int v)
{
    std::vector<std::pair<int, int>> LongPath(n , pair<int,int>(-1,0));
    LongPath[u].first = 0;
    LongPath[u].second = 1;


    std::vector<bool> visited(v, false);
    std::queue<int> qu;
    qu.push(u);


    while (!qu.empty()) {
        int current = qu.front();
        qu.pop();
        if(!visited[current]) {
            std::vector<int> adjacentVertices;
            graph.GetNextVertices(current, adjacentVertices);

            for (auto &obj : adjacentVertices) {
//            cout << obj << " first: " << LongPath[obj].first << " second: "<<LongPath[obj].second<< endl;
//            cout << current << " first: " << LongPath[current].first << " second: "<<LongPath[current].second<< endl;
                if (LongPath[obj].first > LongPath[current].first + 1) {
                    LongPath[obj].first = LongPath[current].first + 1;
                    LongPath[obj].second = LongPath[current].second;
                } else if (LongPath[obj].first == -1) {
                    LongPath[obj].first = LongPath[current].first + 1;
                    LongPath[obj].second = LongPath[current].second;
                } else if (LongPath[obj].first == LongPath[current].first + 1)
                    LongPath[obj].second += LongPath[current].second;
                qu.push(obj);

//                if (!visited[current]) {
//                    qu.push(obj);
//                    visited[obj] = true;
//                }
            }
            visited[current] = true;
        }
        //cout << endl;

    }
    //cout << LongPath[w].first;
    return LongPath[w].second;
}

int main() {


    int n = 0, v = 0;
    std::cin >> v >> n;
    MatrixGraph graph(v);
    for (int i = 0 ; i < n; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }
    int u, w;
    std::cin >> u >> w;
    cout << findMin(graph,u,w,n,v) << endl;
    return 0;
}

/*
4
5
0 1
0 2
1 2
1 3
2 3

0 3
 */