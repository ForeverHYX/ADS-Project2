#include <iostream>
#include "FibonacciHeap.h"

using namespace std;

int main(){
    // auto p = new FibonacciNode<int>(10);
    // cout << p->left;
    // cout << p;

    auto q = new FibonacciHeap<int>;
    q->insert(10);
    q->insert(15);
    q->insert(20);
    q->insert(5);
    cout << q->find_min() << endl;
    q->delete_min();
    cout << q->find_min() << endl;
    cout << q->is_exist(5) << endl;
    cout << q->is_exist(15) << endl;
    cout << q->is_exist(45) << endl;

    // auto p = new FibonacciHeap<int>;
    // p->insert(5);
    // cout << 2;
    // q->merge(p);
    // cout << 1;
    // cout << q->find_min();
}