
#include <iostream>
#include <string>
using namespace std;

bool isValidParentheses(string s)
{
    string result = "";
    int idx = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (idx == 0)
        {
            result += s[i];
            idx++;
        }
        else
        {
            bool Default = false;
            switch (s[i])
            {
            case ']':
                if (result[idx - 1] == '[')
                {
                    result.erase(result.begin() + idx - 1);
                    idx--;
                }
                else
                {
                    Default = true;
                }
                break;
            case ')':
                if (result[idx - 1] == '(')
                {
                    result.erase(result.begin() + idx - 1);
                    idx--;
                }
                else
                {
                    Default = true;
                }
                break;
            case '}':
                if (result[idx - 1] == '{')
                {
                    result.erase(result.begin() + idx - 1);
                    idx--;
                }
                else
                {
                    Default = true;
                }
                break;
            default:
                Default = true;
            }
            if (Default)
            {
                result += s[i];
                idx++;
            }
        }
    }
    return result.length() == 0 ? true : false;
}
int main()
{
    cout << isValidParentheses("(])") << "\n";
    return 0;
}
