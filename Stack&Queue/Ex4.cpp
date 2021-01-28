#include <iostream>
#include <string>
#include <vector>
using namespace std;

int baseballScore(string ops)
{
    vector<int> result;
    int idx = 0;
    for (unsigned int i = 0; i < ops.length(); i++)
    {
        switch (ops[i])
        {
        case '+':
            result[idx] = result[idx - 1] + result[idx - 2];
            idx++;
            break;
        case 'D':
            result[idx] = result[idx - 1] * 2;
            idx++;
            break;
        case 'C':
            result.erase(result.begin() + idx - 1);
            idx--;
        default:
            result[idx] = ops[i] - 48;
            idx++;
        }
    }
    int sum = 0;
    for(auto i = result.begin(); i!=result.end(); i ++)
    {
        sum +=*i;
    }
    return sum;
}
int main()
{
    
    return 0;
}