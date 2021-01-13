/*
Given a graph and a source vertex in the graph. 
Find shortest paths from source to destination vertice in the given graph using Dijsktra's algorithm.
*/
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
bool check(vector<int> list, int key)
{
    for (auto i = list.begin(); i != list.end(); i++)
        if (*i == key)
            return true;
    return false;
}
int Dijkstra(int **graph, int src, int dst)
{
    // TODO: return the length of shortest path from src to dst.
    vector<int> sptSet;
    int result[6] = {10000000, 10000000, 10000000, 10000000, 10000000, 10000000};
    result[src] = 0;
    sptSet.push_back(src);
    while (sptSet.size() != 6)
    {
        for (int i = 0; i < 6; i++) // Updata the index
        {
            int m = graph[sptSet[sptSet.size() - 1]][i];
            if (m != 0)
            {
                if (result[i] == 10000000)
                {
                    int adding_value = graph[sptSet[sptSet.size() - 1]][i] + result[sptSet[sptSet.size() - 1]];
                    result[i] = adding_value;
                }
                else
                {
                    if (graph[sptSet[sptSet.size() - 1]][i] + result[sptSet[sptSet.size() - 1]] < result[i])
                    {
                        result[i] = graph[sptSet[sptSet.size() - 1]][i] + result[sptSet[sptSet.size() - 1]];
                        //cout << "The value is : " << graph[sptSet[sptSet.size() - 1]][i] + result[sptSet[sptSet.size() - 1]] << endl;
                    }
                }
                graph[i][sptSet[sptSet.size() - 1]] = 0;
            }
        }
        int minValue = 10000000;
        for (int i = 0; i < 6; i++)
        {
            if (result[i] < minValue && check(sptSet, i) == false)
                minValue = result[i];
        }
        int i;
        for (i = 0; i < 6; i++)
        {
            if (result[i] == minValue && check(sptSet, i) == false)
                break;
        }
        sptSet.push_back(i);
    }
    return result[dst];
}
int main()
{
    int n = 6;
    int init[6][6] = {
        {0, 10, 20, 0, 0, 0},
        {10, 0, 0, 50, 10, 0},
        {20, 0, 0, 20, 33, 0},
        {0, 50, 20, 0, 20, 2},
        {0, 10, 33, 20, 0, 1},
        {0, 0, 0, 2, 1, 0}};

    int **graph = new int *[n];
    for (int i = 0; i < n; ++i)
    {
        graph[i] = init[i];
    }
    cout << "\n The shortest path is : " << Dijkstra(graph, 1, 3);
    system("pause");
    return 0;
}
