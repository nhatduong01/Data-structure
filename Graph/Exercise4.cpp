/*
Implement function to detect a cyclic in Graph
*/
#include <iostream>
#include <list>
using namespace std;

class DirectedGraph
{
    int V;
    list<int> *adj;
    bool isCyclicUtil(int v, bool visited[], bool *rs)
    {
        if (visited[v] == false)
        {
            visited[v] = rs[v] = true;
            int _size = adj[v].size();
            while (_size)
            {
                int temp = getElement(v, _size - 1);
                if (visited[temp] == false && isCyclicUtil(temp, visited, rs))
                {
                    return true;
                }
                else if (rs[temp] == true)
                    return true;
                _size--;
            }
        }
        rs[v] = false;
        return false;
    }

public:
    int getElement(int location, int idx)
    {
        auto it = adj[location].begin();
        advance(it, idx);
        return *it;
    }
    DirectedGraph()
    {
        V = 0;
        adj = NULL;
    }
    DirectedGraph(int V)
    {
        this->V = V;
        adj = new list<int>[V];
    }
    void addEdge(int v, int w)
    {
        adj[v].push_back(w);
    }
    bool isCyclic()
    {
        int v = 0;
        bool *visited = new bool[V];
        bool *rs = new bool[V];
        for (int i = 0; i < V; i++)
        {
            rs[i] = visited[i] = false;
        }
        for (int i = 0; i < V; i++)
        {
            if (isCyclicUtil(i, visited, rs))
                return true;
        }
        return false;
    }
};
int main()
{
    DirectedGraph g(8);
    int edege[][2] = {{0, 6}, {1, 2}, {1, 4}, {1, 6}, {3, 0}, {3, 4}, {5, 1}, {7, 0}, {7, 1}};

    for (int i = 0; i < 9; i++)
        g.addEdge(edege[i][0], edege[i][1]);

    if (g.isCyclic())
        cout << "Graph contains cycle";
    else
        cout << "Graph doesn't contain cycle";
    system("pause");
    return 0;
}