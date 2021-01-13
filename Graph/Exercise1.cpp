/*
Implement Breadth-First Search
where Adjacency is a structure to store list of number. s
*/
#include <iostream>
#include <list>
#include <queue>
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
bool In_Queue(queue<int> queue, int key)
{
    while (queue.empty() == false)
    {
        if (queue.front() == key)
            return true;
        queue.pop();
    }
    return false;
}
bool In_list(Adjacency *List, int key)
{
    for (int i = 0; i < List->getSize(); i++)
    {
        if (List->getElement(i) == key)
            return true;
    }
    return false;
}
class Graph
{
private:
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
        adj[w].push(v);
    }

    void printGraph()
    {
        for (int v = 0; v < V; ++v)
        {
            cout << "\nAdjacency list of vertex " << v << "\nhead ";
            adj[v].print();
        }
    }

    Adjacency *BFS(int v)
    {
        // v is a vertex we start BFS
        queue<int> BFS;
        Adjacency *result = new Adjacency();
        result->push(v);
        for (int i = 0; i < adj[v].getSize(); i++)
        {
            BFS.push(adj[v].getElement(i));
        }
        while (result->getSize() != V)
        {
            if (BFS.empty() == false)
            {
                int temp = BFS.front();
                BFS.pop();
                result->push(temp);
                for (int i = 0; i < adj[temp].getSize(); i++)
                {
                    int temp2 = adj[temp].getElement(i);
                    if (In_Queue(BFS, temp2) == false && In_list(result, temp2) == false)
                        BFS.push(temp2);
                }
            }
        }
        return result;
    }
};
int main()
{
    int V = 6;
    int visited = 0;

    Graph g(V);
    Adjacency *arr = new Adjacency(V);
    int edge[][2] = {{0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 4}, {3, 4}, {3, 5}, {4, 5}};

    for (int i = 0; i < 8; i++)
    {
        g.addEdge(edge[i][0], edge[i][1]);
    }

    arr = g.BFS(visited);
    arr->printArray();
    delete arr;
    return 0;
}