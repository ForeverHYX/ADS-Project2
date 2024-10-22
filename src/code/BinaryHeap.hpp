#ifndef BINARYHEAP_HPP
#define BINARYHEAP_HPP

#include <vector>
#include <stdexcept>

template <class T>
struct BinaryHeap {
    std::vector<T> heap;

    BinaryHeap() {
        heap.clear();
<<<<<<< HEAD
    }

<<<<<<< HEAD
    void insert(T key) {
        heap.push_back(key);
        _up_shift();
=======
    bool is_empty(){
        return heap->size() == 0;
    }

    void insert(T key){
        heap = _insert(heap, key);
>>>>>>> bbc157ddd98f4fb7af4e5279a68fd28a233f7fb7
=======
    }

    void insert(T key) {
        heap.push_back(key);
        _up_shift();
>>>>>>> 460a2c1f3ac1e2c03ec0d780eb3197dd5e69ccf5
    }

    T find_min() {
        if (heap.empty()) {
            throw std::underflow_error("Heap is empty");
        }
        return heap[0];
    }

    void delete_min() {
        if (heap.empty()) {
            throw std::underflow_error("Heap is empty");
        }
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            _down_shift();
        }
    }

private:
    void _up_shift() {
        size_t child = heap.size() - 1;
        size_t parent = (child - 1) / 2;

        T tmp = heap[child];

        while (child > 0) {
            if (heap[parent] <= tmp) {
                break;
            }
            heap[child] = heap[parent];
            child = parent;
            parent = (child - 1) / 2;
        }

        heap[child] = tmp;
    }

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> 460a2c1f3ac1e2c03ec0d780eb3197dd5e69ccf5
    void _down_shift() {
        size_t parent = 0;
        size_t left = 2 * parent + 1;
        size_t end = heap.size() - 1;

        T tmp = heap[parent];

        while (left <= end) {
            size_t right = left + 1;
            if (right <= end && heap[left] > heap[right]) {
                left = right;
<<<<<<< HEAD
=======
    std::vector<T>* _down_shift(std::vector<T>* heap){
        if(heap->size() == 0)   return heap;
        size_t parent = 0;
        size_t left = 2 * parent + 1;
        T tmp = heap->at(parent);
        while(left < heap->size()){
            if(left + 1 < heap->size() && heap->at(left) > heap->at(left + 1)){
                left ++;
>>>>>>> bbc157ddd98f4fb7af4e5279a68fd28a233f7fb7
=======
>>>>>>> 460a2c1f3ac1e2c03ec0d780eb3197dd5e69ccf5
            }

            if (tmp <= heap[left]) {
                break;
            }

            heap[parent] = heap[left];
            parent = left;
            left = 2 * parent + 1;
        }

<<<<<<< HEAD
<<<<<<< HEAD
        heap[parent] = tmp;
=======
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
>>>>>>> bbc157ddd98f4fb7af4e5279a68fd28a233f7fb7
    }
};

#endif
=======
        heap[parent] = tmp;
    }
};

#endif
>>>>>>> 460a2c1f3ac1e2c03ec0d780eb3197dd5e69ccf5
