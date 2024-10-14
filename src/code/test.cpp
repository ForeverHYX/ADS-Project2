#include <iostream>
#include "BinomialHeap.h"

using namespace std;

int main(){
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
