/*
Given an array of distinct integers, find if there are two pairs (a, b) and (c, d) such that
 a+b = c+d, and a, b, c and d are distinct elements. If there are multiple answers, you can find any of them.
*/
#include <iostream>
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
bool findPairs(int arr[], int n, pair<int, int> &pair1, pair<int, int> &pair2)
{
    // TODO: If there are two pairs satisfy the condition, assign their values to pair1, pair2 and return true. Otherwise, return false.
    vector<pair<int, int>> result;
    int idx = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            pair<int, int> temp;
            temp.first = arr[i];
            temp.second = arr[j];
            result.push_back(temp);
        }
    }
    for (auto i = result.begin(); i != result.end() - 1; i++)
    {
        for (auto j = i + 1; j != result.end(); j++)
        {
            int a = (*i).first + (*i).second;
            int b = (*j).first + (*j).second;
            if (a == b)
            {
                pair1 = *i;
                pair2 = *j;
                cout << "The first pair " << pair1.first << "\t" << pair1.second << endl;
                cout << "The second pair " << pair2.first << "\t" << pair2.second << endl;
                return true;
            }
        }
    }
    return false;
}
bool checkAnswer(int arr[], int n, pair<int, int> &pair1, pair<int, int> &pair2)
{
    // TODO: If there are two pairs satisfy the condition, assign their values to pair1, pair2 and return true. Otherwise, return false.
}
int main()
{
    int arr[] = {3, 4, 7, 1, 2, 9, 8};
    int n = sizeof arr / sizeof arr[0];
    pair<int, int> pair1, pair2;
    if (findPairs(arr, n, pair1, pair2))
    {
        {
            printf("Your answer is correct.\n");
        }
    }
    else
        printf("No pair found.\n");
    return 0;
}