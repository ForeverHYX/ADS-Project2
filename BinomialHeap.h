#include<list>
#include<iostream>

// defination

struct BinomialHeap;
struct BinomialTree;

struct BinomialHeap{
    std::list<BinomialTree*> root_list;

    BinomialHeap() = default;
    void insert(int key);
    BinomialTree* find_min();
    void delete_min();
    std::list<BinomialTree*>::iterator locate_by_degree(size_t tar_degree);
    size_t get_degree();
    void add_tree(BinomialTree* new_tree);
};

BinomialHeap* merge_binomial_heap(BinomialHeap* p, BinomialHeap* q);

struct BinomialTree{
    /* data */
    size_t degree = 0;
    int val;
    std::list<BinomialTree*> child_list;

    BinomialTree() = default;
    BinomialTree(int init_key);
    BinomialTree* add_sub_tree(BinomialTree* new_sub_tree);
};

BinomialTree* merge_binomial_tree(BinomialTree* p, BinomialTree* q);

// implementation

void BinomialHeap::insert(int key){
    auto t = new BinomialHeap;
    auto p = new BinomialTree(key);
    t->root_list.push_back(p);

    auto q = merge_binomial_heap(this, t);
    this->root_list = std::move(q->root_list);
}

BinomialTree* BinomialHeap::find_min(){
    BinomialTree* ret = nullptr;
    int min_key = 0x7fffffff;
    for(auto i:root_list){
        if(i->val < min_key){
            min_key = i->val;
            ret = i;
        }
    }
    return ret;
}

std::list<BinomialTree*>::iterator BinomialHeap::locate_by_degree(size_t tar_degree){
    auto ret = this->root_list.begin();
    while(ret != root_list.end()){
        if(tar_degree == (*ret)->degree){
            break;
        }
        ret++;
    }
    return ret;
}

size_t BinomialHeap::get_degree(){
    size_t degree = 0;
    for(auto i:this->root_list){
        if(i->degree >= degree){
            degree = i->degree;
        }
    }
    return degree;
}


void BinomialHeap::add_tree(BinomialTree* new_tree){
    auto u = this->locate_by_degree(new_tree->degree);
    if(u == this->root_list.end()){
        this->root_list.push_back(new_tree);
    }
    else{
        auto t = merge_binomial_tree(*u, new_tree);
        this->root_list.erase(u);
        this->add_tree(t);
    }
    return;
}

BinomialHeap* merge_binomial_heap(BinomialHeap* p, BinomialHeap* q){
    auto ret_heap = new BinomialHeap;
    auto max_degree = std::max(p->get_degree(), q->get_degree());
    for(size_t i = 0; i <= max_degree; ++i){
        auto r = p->locate_by_degree(i);
        auto s = q->locate_by_degree(i);
        if(r == p->root_list.end() && s == q->root_list.end()){
            ;
        }
        else if(r != p->root_list.end() && s == q->root_list.end()){
            ret_heap->add_tree(*r);
        }
        else if(r == p->root_list.end() && s != q->root_list.end()){
            ret_heap->add_tree(*s);
        }
        else{
            auto u = merge_binomial_tree(*r, *s);
            ret_heap->add_tree(u);
        }
    }

    return ret_heap;
}

BinomialTree::BinomialTree(int init_key){
    degree = 0;
    val = init_key;
}

BinomialTree* BinomialTree::add_sub_tree(BinomialTree* new_sub_tree){
    this->degree += 1;
    this->child_list.push_back(new_sub_tree);
    return this;
}

BinomialTree* merge_binomial_tree(BinomialTree* p, BinomialTree* q){
    if(p->val <= q->val){
        return p->add_sub_tree(q);
    }
    else{
        return q->add_sub_tree(p);
    }
}