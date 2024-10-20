#include <iostream>
#include "BinaryHeap.hpp"
using namespace std;

int main(){
    auto foo = new BinaryHeap<int>;
    foo->insert(15);
    foo->insert(5);
    foo->insert(25);
    foo->insert(35);
    foo->insert(55);

    cout << foo->find_min() << endl;

    foo->delete_min();
    cout << foo->find_min() << endl;
    cout << foo->find_min() << endl;
    cout << foo->find_min() << endl;
    cout << foo->find_min() << endl;
}