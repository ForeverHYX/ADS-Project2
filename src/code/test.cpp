#include <iostream>
#include <vector>
#include "BinomialHeap.h"

using namespace std;

int main(){
    
    auto p = new BinomialHeap<int>;
    auto q = new BinomialHeap<int>;
    
    int data_p[] = {12, 21, 52, 5, 8};
    int data_q[] = {53, 7, 43, 66, 11, 9, 27};


    for(auto i:data_p)  p->insert(i);
    for(auto i:data_q)  q->insert(i);

    cout << "minimum key of p is " << p->find_min() << endl;
    cout << "minimum key of q is " << q->find_min() << endl;

    p->delete_min();
    q->delete_min();

    cout << "delete min key..." << endl;

    cout << "minimum key of p is " << p->find_min() << endl;
    cout << "minimum key of q is " << q->find_min() << endl;

    p->merge(q);

    cout << "21 in p is " << p->is_exist(21) << endl;
    cout << "22 in p is " << p->is_exist(22) << endl;

    cout << "merge q to p, then p is: ";
    while(p->find_min() != -1){
        cout << p->find_min() << ' ';
        p->delete_min();
    }

    cout << endl;

}