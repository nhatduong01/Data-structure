/*
Research queue which is implemented in C library at http://www.cplusplus.com/reference/queue/queue/. You can use library queue in c++ for this question.

Using queue, complete function bool isBipartite(vector<vector<int>> graph) to determine if a graph is bipartite or not (the graph can be disconnected). In caat https://en.wikipedia.org/wiki/Bipartite_graph.

You can use below liberaries in this question.
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
bool isBipartite(vector<vector<int>> graph)
{
    int _size = graph.size();
    int *colours = new int[_size];
    /*
    -1 means is not colored
    0 is the first colour
    1 is the second colour
    */
    for (int i = 0; i < _size; i++)
    {
        colours[i] = -1;
    }
    int src = 0; // We will start from the vertex 0
    colours[src] = 0;
    queue<int> storage;
    storage.push(src);
    while (storage.empty() == false)
    {
        int temp = storage.front();
        storage.pop();
        for (int i = 0; i < graph[temp].size(); i++)
        {
            if (colours[temp] == colours[graph[temp][i]])
            {
                delete[] colours;
                return false;
            }
            else if (colours[graph[temp][i]] == -1)
            {
                colours[graph[temp][i]] = 1 - colours[temp];
                storage.push(graph[temp][i]);
            }
        }
    }
    delete[] colours;
    return true;
}
int main()
{
    int G[6][6] = {{0, 1, 0, 0, 0, 1},
                   {1, 0, 1, 0, 0, 0},
                   {0, 1, 0, 1, 0, 0},
                   {0, 0, 1, 0, 1, 0},
                   {0, 0, 0, 1, 0, 1},
                   {1, 0, 0, 0, 1, 0}};
    int n = 6;

    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (G[i][j])
                graph[i].push_back(j);
        }
    }
    for (int i = 0; i < graph.size(); i++)
    {
        for (int j = 0; j < graph[i].size(); j++)
            cout << graph[i][j] << "\t";
        cout << endl;
    }
    //isBipartite(graph) ? cout << "Yes" : cout << "No";
    return 0;
}