/*
Implement topologicalSort function on a graph.
To Mathch the answer
To match the given answer, please always traverse from 0 when performing the sorting.
*/
#include <iostream>
#include <list>
#include <queue>
#include <vector>
using namespace std;

class Adjacency
{
private:
    list<int> adjList;
    int size;

public:
    Adjacency() {}
    Adjacency(int V) {}
    void push(int data)
    {
        adjList.push_back(data);
        size++;
    }
    void print()
    {
        for (auto const &i : adjList)
            cout << " -> " << i;
    }
    void printArray()
    {
        for (auto const &i : adjList)
            cout << i << " ";
    }
    int getSize() { return adjList.size(); }
    int getElement(int idx)
    {
        auto it = adjList.begin();
        advance(it, idx);
        return *it;
    }
};
class Graph
{

    int V;
    Adjacency *adj;

public:
    Graph(int V)
    {
        this->V = V;
        adj = new Adjacency[V];
    }
    void addEdge(int v, int w)
    {
        adj[v].push(w);
    }

    void topologicalSort()
    {
        int *in_degree = new int[V];
        for (int i = 0; i < V; i++)
        {
            in_degree[i] = 0;
        }
        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < adj[i].getSize(); j++)
            {
                int temp = adj[i].getElement(j);
                in_degree[temp]++;
            }
        }
        vector<int> result;
        while (result.size() != V)
        {
            unsigned int min = 1000000;
            int idx = 0;
            for (int i = V - 1; i >= 0; i--)
            {
                if (in_degree[i] < min && in_degree[i] >= 0)
                {
                    min = in_degree[i];
                    idx = i;
                }
            }
            result.push_back(idx);
            in_degree[idx]--;
            int _size = adj[idx].getSize();
            for (int i = 0; i < _size; i++)
            {
                int temp = adj[idx].getElement(i);
                in_degree[temp]--;
            }
        }
        for (auto i = result.begin(); i != result.end(); i++)
        {
            cout << *i << " ";
        }
    }
};
int main()
{
    Graph g(6);
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);
    g.topologicalSort();
    system("pause");
    return 0;
}