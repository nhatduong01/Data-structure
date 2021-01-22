/*Implement these three hashing functions
*/
#include <iostream>
#include <math.h>
using namespace std;
long int midSquare(long int seed)
{
    long int square = seed * seed;
    long int numdigit = log(square) / log(10) + 1;
    long int omit = ceil((double)numdigit / 4);
    //cout << "Omit is :" << omit << endl;
    square /= pow(10, omit);
    long int result = square % (long int)pow(10, 4);
    return result;
}
long int moduloDivision(long int seed, long int mod)
{
    return seed % mod + 1;
}
long int digitExtraction(long int seed, int *extractDigits, int size)
{
    long int numdigit = log(seed) / log(10) + 1;
    long int *arr = new long int[numdigit];
    long int idx = numdigit - 1;
    //cout << "seed is : " << seed << endl;
    while (seed)
    {
        arr[idx] = seed % 10;
        seed /= 10;
        idx--;
    }
    // cout << "The array is : \n";
    // for (int i = 0; i < numdigit; i++)
    //     cout << arr[i] << " ";
    idx = 0; // We use idx for the result
    for (int i = 0; i < size; i++)
    {
        idx += arr[extractDigits[i]] * pow(10, size - 1 - i);
    }
    return idx;
    delete[] arr;
}
int main()
{
    int a[] = {1, 2, 5};
    cout << digitExtraction(122443, a, 3) << endl;
    cout << midSquare(50451);
    return 0;
}