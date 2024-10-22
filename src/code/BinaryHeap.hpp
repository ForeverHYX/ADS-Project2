#ifndef BINARYHEAP_HPP
#define BINARYHEAP_HPP

#include <vector>
#include <stdexcept>

template <class T>
struct BinaryHeap {
    std::vector<T> heap;

    BinaryHeap() {
        heap.clear();
    }

    void insert(T key) {
        heap.push_back(key);
        _up_shift();
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

    void _down_shift() {
        size_t parent = 0;
        size_t left = 2 * parent + 1;
        size_t end = heap.size() - 1;

        T tmp = heap[parent];

        while (left <= end) {
            size_t right = left + 1;
            if (right <= end && heap[left] > heap[right]) {
                left = right;
            }

            if (tmp <= heap[left]) {
                break;
            }

            heap[parent] = heap[left];
            parent = left;
            left = 2 * parent + 1;
        }

        heap[parent] = tmp;
    }
};

#endif
