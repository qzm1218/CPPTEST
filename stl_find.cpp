#include <vector>
#include <list>
#include <deque>
#include <algorithm>
#include <iostream>

using namespace std;

int main(int argc,char *argv[])
{
    const int arraySize = 7;
    int ia[arraySize] = { 0, 1, 2, 3, 4, 5, 6};

    vector<int> ivec(ia, ia + arraySize);
    list<int> ilist(ia, ia + arraySize);
    deque<int> ideque(ia, ia + arraySize);


    vector<int>::iterator iterVec = find(ivec.begin(), ivec.end(), 4);
    if ( iterVec != ivec.end() )
        cout << "4 is found." << endl;
    else
        cout << "4 is not found." << endl;

    list<int>::iterator iterList = find(ilist.begin(), ilist.end(), 5);
    if ( iterList != ilist.end() )
        cout << "5 is found." << endl;
    else 
        cout << "5 is not found." << endl;

    deque<int>::iterator iterDeque = find(ideque.begin(), ideque.end(), 6);
    if ( iterDeque != ideque.end() )
        cout << "6 is found." << endl;
    else
        cout << "6 is not found." << endl;

    return 0;
}
