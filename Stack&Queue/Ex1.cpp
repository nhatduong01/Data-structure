#include <iostream>
#include <string>
using namespace std;
string removeDuplicates(string S)
{
    string result = "";
    int idx = 0;
    for (int i = 0; i < S.length(); i++)
    {
        if (result.length() == 0)
        {
            result += S[i];
            idx++;
        }
        else
        {
            if (S[i] == result[idx - 1])
            {
                result.erase(result.begin() + idx - 1);
                idx--;
            }
            else
            {
                result += S[i];
                idx++;
            }
        }
    }
    return result;
}
int main()
{
    cout << removeDuplicates("abbaca") << endl;
    system("pause");
    return 0;
}