#include "BusSystem.h"
// using namespace std;
int main()
{
    BusSystem *bs = new BusSystem();
    cout << bs->query("SQ 10") << "\n";
    cout << bs->query("INS 50 56D1-23342 0001 12023 15000") << "\n";
    cout << bs->query("INS 50 50D1-23342 000 1234 5678") << "\n";
    cout << bs->query("INS 50 51D1-23369 0 4500 5678") << "\n";
    cout << bs->query("INS 50 52D1-23342 0 5688 6000") << "\n";
    cout << bs->query("INS 50 53D1-23342 1 1234 7000") << "\n";
    cout << bs->query("INS 50 54D1-23342 001 1236 5564") << "\n";
    cout << bs->query("INS 50 54D1-23342 1 12000 15000") << "\n";
    cout << bs->query("INS 50 54D1-23342 0 17000 18000") << "\n";
    cout << bs->query("INS 50 42E2-08949 0 3000 5678") << "\n";
    cout << bs->query("INS 50 69E2-08949 1 3500 5678") << "\n";

    //cout<<"Number of deleted buses : " <<bs->query("DEL 50 1234 5679";
    //cout <<"The number of finished buses is :" <<bs->query("CE 50 16000 0");
    cout << bs->query("GS 50 17500 1");
    cout << "\n The next test \n";
    cout << bs->query("GE 50 5678 00000") << "\n";
    cout << "There are : " << bs->query("CS 50 5000 1");
    delete bs;
    return 0;
}
