/*
Research queue which is implemented in C library at: http://www.cplusplus.com/reference/queue/queue/. You can use library queue in c++ for this question.

Using queue, complete function void bfs(vector<vector<int>> graph, int start) to traverse all the nodes of the graph from given start node using Breadth First Search algorithm and data structure queue, and print the order of visited nodes. 

You can use below liberaries in this question.
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
void bfs(vector<vector<int>> graph, int start)
{
    cout << start << " ";
    int _size = graph.size();
    bool *is_visited = new bool[_size];
    for (int i = 0; i < _size; i++)
        is_visited[i] = false;
    is_visited[start] = true;
    queue<int> storage;
    for (int i = 0; i < graph[start].size(); i++)
    {
        int temp = graph[start][i];
        is_visited[temp] = true;
        storage.push(temp);
    }
    while (storage.empty() == false)
    {
        int temp = storage.front();
        cout << temp << " ";
        storage.pop();
        int _Size = graph[temp].size();
        for (int i = 0; i < _Size; i++)
        {
            int value = graph[temp][i];
            if (is_visited[value] == false)
            {
                storage.push(value);
                is_visited[value] = true;
            }
        }
    }
    delete[] is_visited;
}
int main()
{
    int init_graph[10][10] = {{0, 1, 1, 0, 1, 0, 1, 0, 1, 0},
                              {0, 0, 1, 1, 0, 0, 0, 1, 0, 0},
                              {0, 1, 0, 0, 0, 1, 1, 0, 1, 1},
                              {1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                              {0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
                              {1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
                              {0, 0, 1, 1, 0, 1, 0, 0, 0, 0},
                              {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
                              {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
                              {1, 0, 1, 0, 1, 0, 0, 0, 1, 0}};
    int n = 10;
    vector<vector<int>> graph(n, vector<int>());
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (init_graph[i][j])
                graph[i].push_back(j);
        }
    }

    bfs(graph, 0);
    system("pause");
    return 0;
}