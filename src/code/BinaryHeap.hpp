#include <vector>

template <class T>
struct BinaryHeap{
    std::vector<T>* heap;

    BinaryHeap(){
        heap = new std::vector<T>;
        heap->clear();
    }

    bool is_empty(){
        return heap->size() == 0;
    }

    void insert(T key){
        heap = _insert(heap, key);
    }

    T find_min(){
        return heap->at(0);
    }

    void delete_min(){
        heap = _delete_min(heap);
    }

    std::vector<T>* _up_shift(std::vector<T>* heap){
        size_t child = heap->size() - 1;
        size_t parent = child / 2;

        T tmp = heap->at(child);

        while(child != 0){
            if(heap->at(parent) <= tmp){
                break;
            }
            else{
                heap->at(child) = heap->at(parent);
                child = parent;
                parent = child / 2;
            }
        }

        heap->at(child) = tmp;
        return heap;
    }

    std::vector<T>* _down_shift(std::vector<T>* heap){
        if(heap->size() == 0)   return heap;
        size_t parent = 0;
        size_t left = 2 * parent + 1;
        T tmp = heap->at(parent);
        while(left < heap->size()){
            if(left + 1 < heap->size() && heap->at(left) > heap->at(left + 1)){
                left ++;
            }

            if(tmp <= heap->at(left)){
                break;
            }

            heap->at(parent) = heap->at(left);
            parent = left;
            left = 2 * parent + 1;
        }

        heap->at(parent) = tmp;

        return heap;
    }

    std::vector<T>* _insert(std::vector<T>* heap, T key){
        heap->push_back(key);
        return _up_shift(heap);
    }

    std::vector<T>* _delete_min(std::vector<T>* heap){
        if(heap->size() == 0) return heap;
        heap->at(0) = heap->at(heap->size() - 1);
        heap->pop_back();
        return _down_shift(heap);
    }
};
