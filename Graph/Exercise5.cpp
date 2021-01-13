/*
Given an undirected, connected and weighted graph, find Minimum Spanning Tree (MST) of the graph using Kruskal’s algorithm.
Below are the steps for finding MST using Kruskal’s algorithm:
1. Sort all the edges in non-decreasing order of their weight.
2. Pick the smallest edge. Check if it forms a cycle with the spanning tree formed so far. If cycle is not formed, include this edge. 
Else, discard it.
3. Repeat step#2 until there are (V-1) edges in the spanning tree.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <vector>
#include <set>
using namespace std;
class subset
{
public:
    int parent;
    int rank;
};
int find(subset subsets[], int i)
{
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}
void Union(subset subsets[], int x, int y)
{
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;

    else
    {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}
struct Graph
{
    int V, E;
    vector<pair<int, pair<int, int>>> edges;
    // Constructor
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
    }

    void addEdge(int u, int v, int w)
    {
        edges.push_back({w, {u, v}});
    }

    //YOUR CODE HERE
    int kruskalMST()
    {
        // TODO: return weight of the minimum spanning tree.
        int result = 0;
        for (unsigned int i = 0; i < edges.size(); i++)
        {
            for (unsigned int j = 0; j < edges.size() - 1; j++)
            {
                int k = j + 1;
                if (edges[k].first < edges[j].first)
                {
                    swap(edges[k], edges[j]);
                }
            }
        }
        int Vertice = V;
        int i = 0; // Used to store edges
        int e = 0;
        subset *Subsets = new subset[V * sizeof(subset)];
        for (int v = 0; v < V; ++v)
        {
            Subsets[v].parent = v;
            Subsets[v].rank = 0;
        }
        while (e < Vertice - 1 && i < E)
        {
            pair<int, pair<int, int>> current_edge = this->edges[i++];
            int x = find(Subsets, current_edge.second.first);
            int y = find(Subsets, current_edge.second.second);
            if (x != y)
            {
                result += current_edge.first;
                Union(Subsets, x, y);
            }
        }
        delete[] Subsets;
        return result;
    }
};
int main()
{
    int V = 9, E = 14;
    Graph g(V, E);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(2, 3, 7);
    g.addEdge(2, 8, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 14);
    g.addEdge(4, 5, 10);
    g.addEdge(5, 6, 2);
    g.addEdge(6, 7, 1);
    g.addEdge(6, 8, 6);
    g.addEdge(7, 8, 7);
    cout << g.kruskalMST();
    return 0;
}