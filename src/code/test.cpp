#include "FibonacciHeap.hpp"
#include <iostream>
using namespace std;

int main(){
    auto foo = new FibonacciHeap<int>;
    foo->insert(10);
    foo->insert(15);
    foo->insert(20);

    auto t = foo->find_min();

    cout << foo->find_min() << endl;

    foo->decrease_key(foo->heap, 5);

    cout << foo->find_min() << endl;

}