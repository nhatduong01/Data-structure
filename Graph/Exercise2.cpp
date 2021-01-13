/*
Implement Depth-first search.
where Adjacency is a structure to store list of number. 
*/
#include <iostream>
#include <list>
#include <stack>
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
bool In_Queue(stack<int> stack, int key)
{
    while (stack.empty() == false)
    {
        if (stack.top() == key)
            return true;
        stack.pop();
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

    Adjacency *DFS(int v)
    {
        // v is a vertex we start DFS
        stack<int> DFS;
        Adjacency *result = new Adjacency();
        result->push(v);
        for (int i = adj[v].getSize() - 1; i >= 0; i--)
        {
            DFS.push(adj[v].getElement(i));
        }
        while (true)
        {
            if (DFS.empty() == false)
            {
                int temp = DFS.top();
                DFS.pop();
                result->push(temp);
                for (int i = adj[temp].getSize() - 1; i >= 0; i--)
                {
                    int temp2 = adj[temp].getElement(i);
                    if (In_list(result, temp2) == false)
                        DFS.push(temp2);
                }
            }
            else
            {
                break;
            }
        }
        return result;
    }
};
int main()
{
    int V = 8, visited = 0;

    Graph g(V);
    Adjacency *arr;
    int edge[][2] = {{0, 1}, {0, 2}, {0, 3}, {0, 4}, {1, 2}, {2, 5}, {2, 6}, {4, 6}, {6, 7}};
    for (int i = 0; i < 9; i++)
    {
        g.addEdge(edge[i][0], edge[i][1]);
    }

    //g.printGraph();
    //cout << endl;
    arr = g.DFS(visited);
    arr->printArray();
    delete arr;
    system("pause");
    return 0;
}