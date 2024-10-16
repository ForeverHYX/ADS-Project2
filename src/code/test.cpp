#include <iostream>
<<<<<<< HEAD
#include <vector>
=======
>>>>>>> 39056e3fc99c26c5c68323c62f8917a4216cf109
#include "BinomialHeap.h"

using namespace std;

int main(){
<<<<<<< HEAD
    
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
=======
    // test binomial heap
    // auto t = new BinomialTree(10);
    // auto p = new BinomialTree(20);
    // auto q = new BinomialTree(30);
    // auto r = new BinomialTree(5);

    // t = merge_binomial_tree(t, p);
    // q = merge_binomial_tree(r, q);
    // t = merge_binomial_tree(t, q);

    

    // std::cout << t->val << std::endl;
    // std::cout << t->degree << std::endl;
    // std::cout << t->child_list.front()->val << std::endl;
    // std::cout << t->child_list.front()->degree << std::endl;

    // auto t = new BinomialHeap;

    // // std::cout << 1 << std::endl;
    // // t->insert(1);

    // auto u = new BinomialHeap;

    // t->insert(2);

    // t->insert(1);

    // u->insert(3);

    // u->insert(4);

    // t = merge_binomial_heap(t, u);

    // std::cout << (*(u->root_list.begin()))->val << std::endl;
    
    auto t = new BinomialHeap;
    t->insert(10);
    cout << t->get_degree();
    t->insert(15);

    cout << t->get_degree();
    // t->insert(20);

    // cout << t->get_degree();
    t->insert(20);
    t->insert(5);

    cout << t->get_degree() << endl;
    cout << t->find_min()->val << endl;
}
>>>>>>> 39056e3fc99c26c5c68323c62f8917a4216cf109
