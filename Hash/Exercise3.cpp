/*
Inplement function 
to hashing key using Fold shift or Rotation algorithm. 
Review Fold shift:
The folding method for constructing hash functions begins by dividing the item into equal-size pieces (the last piece may not be of equal size). 
These pieces are then added together to give the resulting hash value.
*/
#include <iostream>
#include <math.h>
using namespace std;
long long foldShift(long long key, long long addressSize)
{
    long long divisor = pow(10, addressSize);
    long long numdigit = log(key) / log(10) + 1;
    //cout <<"The number of digit is : "<<numdigit<<endl;
    long long size = numdigit / addressSize + 1;
    long long *storage = new long long[size];
    if (numdigit % addressSize == 0)
    {
        long long idx = 0;
        while (key != 0)
        {
            storage[idx] = key % divisor;
            key /= divisor;
            idx++;
        }
    }
    else
    {
        long long left = numdigit % addressSize;
        key *= pow(10, addressSize - left);
        //cout <<"The key is :"<<key<<endl;
        long long idx = 0;
        while (key != 0)
        {
            storage[idx] = key % divisor;
            key /= divisor;
            idx++;
        }
        storage[0] /= pow(10, addressSize - left);
    }
    long long sum = 0;
    for (long long i = 0; i < size; i++)
    {
        //cout <<"The storage is : "<<storage[i]<<endl;
        sum += storage[i];
    }
    //cout <<"The value of sum is :"<<sum <<endl;
    delete[] storage;
    return sum % divisor;
}
long long rotation(long long key, long long addressSize)
{
    if (key == 0)
        return 0;
    long long numdigit = log(key) / log(10) + 1;
    long long digit = key % 10;
    key /= 10;
    long long temp = digit * pow(10, numdigit - 1);
    key += temp;
    //cout<<"Key is : "<<key<<endl;
    return foldShift(key, addressSize);
}
long long main()
{
    cout << rotation(343453434535, 4);
    return 0;
}