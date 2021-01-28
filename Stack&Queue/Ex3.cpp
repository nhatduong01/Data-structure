#include <iostream>
#include <vector>
#include <queue>
using namespace std;
bool check_Cylic(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        if (arr[i] == 0)
            return false;
    return true;
}
vector<int> topologicalSorting(vector<vector<int>> graph)
{
    vector<int> result;
    int size = graph.size();
    int *arr = new int[size];
    for (int i = 0; i < size; i++)
        arr[i] = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < graph[i].size(); j++)
        {
            arr[graph[i][j]]++;
        }
    }
    for (int i = 0; i < size; i++)
        cout << arr[i] << "\t";
    if (check_Cylic(arr, size) == true)
        return result;
    while (result.size() != size)
    {
        int min = 100000;
        for (int i = 0; i < size; i++)
        {
            if (min > arr[i] && arr[i] >= 0)
                min = arr[i];
        }
        if (min != 0)
        {
            result.clear();
            return result;
        }
        int i = 0;
        for (; i < size; i++)
        {
            if (arr[i] == min)
            {
                arr[i]--;
                result.push_back(i);
                break;
            }
        }
        for (int j = 0; j < graph[i].size(); j++)
        {
            arr[graph[i][j]]--;
        }
    }
    delete[] arr;
    return result;
}
int main()
{
    int n = 6;
    int G[6][6] = {{0, 1, 0, 1, 0, 0},
                   {0, 0, 1, 1, 0, 0},
                   {0, 0, 0, 1, 1, 1},
                   {0, 0, 0, 0, 1, 1},
                   {0, 0, 0, 0, 0, 1},
                   {0, 0, 0, 0, 0, 0}};
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (G[i][j] == 1)
                graph[i].push_back(j);
        }
    }

    vector<int> res = topologicalSorting(graph);
    if (res.empty())
        printf("-1");
    else
    {
        for (int e : res)
            printf("%d ", e);
    }
    system("pause");
    return 0;
}