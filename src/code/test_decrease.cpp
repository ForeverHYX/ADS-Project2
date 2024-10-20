#include "FibonacciHeap.hpp"
#include <iostream>
using namespace std;

int main(){
    int a[] = {12, 30, 31, 7, 28};
    int b[] = {5, 91, 41, 65, 33};
    auto foo = new FibonacciHeap<int>;
    auto goo = new FibonacciHeap<int>;

    for(auto i:a){
        foo->insert(i);
    }

    for(auto i:b){
        goo->insert(i);
    }

    while(foo->is_empty() == false){
        cout << foo->find_min() << endl;
        foo->delete_min();
    }

    // while(goo->is_empty() == false){
    //     cout << goo->find_min() << endl;
    //     goo->delete_min();
    // }

    for(auto i:a){
        foo->insert(i);
    }

    // for(auto i:b){
    //     goo->insert(i);
    // }
    

    // foo->merge(goo);

    // while(foo->is_empty() == false){
    //     cout << foo->find_min() << endl;
    //     foo->delete_min();
    // }

    foo->decrease_key(foo->find_node(30), 3);
    foo->decrease_key(foo->find_node(28), 18);

    while(foo->is_empty() == false){
        cout << foo->find_min() << endl;
        foo->delete_min();
    }
}