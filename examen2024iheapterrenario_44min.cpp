#include <iostream>
#include <deque>
#include <vector>
using namespace std;

template <class T>
class CMaxHeap3
{
public:
    void push(int n);
    int top();
    void pop();
    void print();
private:
    std::deque<T> heap;
};

template <class T>
int CMaxHeap3<T>::CMaxHeap3::top()
{
    if (heap.empty()) return -1;
    return heap.front();
}

template <class T>
void CMaxHeap3<T>::CMaxHeap3::push(int x)
{
    heap.push_back(x);
    int pos = heap.size() - 1;
    bool stop = false;

    while (pos > 0 && stop == false) {
        int newpos = (pos % 3 == 0) ? (pos / 3) - 1 : (pos / 3);
        if (heap[pos] > heap[newpos]) {
            swap(heap[pos], heap[newpos]);
            pos = newpos;
        }
        else {
            stop = true;
        }
    }
}

template <class T>
void CMaxHeap3<T>::CMaxHeap3::pop()
{
    if (heap.empty()) return;
    swap(heap.front(), heap.back());
    heap.pop_back();
    int pos = 0;
    bool stop = false;
    while (pos < heap.size() && stop == false) {
        int left = (pos * 3) + 1;
        int mid = (pos * 3) + 2;
        int right = (pos * 3) + 3;

        if (left < heap.size() && mid < heap.size() && right < heap.size()) {
            if (heap[left] > heap[mid] && heap[left] > heap[right] && heap[left] > heap[pos]) {
                swap(heap[pos], heap[left]);
                pos = left;
            }
            else if (heap[mid] > heap[left] && heap[mid] > heap[right] && heap[mid] > heap[pos]) {
                swap(heap[pos], heap[mid]);
                pos = mid;
            }
            else if (heap[right] > heap[left] && heap[right] > heap[mid] && heap[right] > heap[pos]) {
                swap(heap[pos], heap[right]);
                pos = right;
            }
            else {
                stop = true;
            }
        }
        else if (left < heap.size() && mid < heap.size() && right >= heap.size()) {
            if (heap[left] > heap[mid] && heap[left] > heap[pos]) {
                swap(heap[pos], heap[left]);
                pos = left;
            }
            else if (heap[mid] > heap[left] && heap[mid] > heap[pos]) {
                swap(heap[pos], heap[mid]);
                pos = mid;
            }
            else {
                stop = true;
            }
        }
        else if (left < heap.size() && mid >= heap.size() && right >= heap.size()) {
            if (heap[left] > heap[pos]) {
                swap(heap[pos], heap[left]);
                pos = left;
            }
            else {
                stop = true;
            }
        }
        else {
            stop = true;
        }
    }

}

template <class T>
void CMaxHeap3<T>::CMaxHeap3::print()
{
    for (auto i = heap.begin(); i != heap.end(); ++i)
        std::cout << *i << " ";
    std::cout << "\n";
}

int main()
{
    CMaxHeap3<int> h;
    std::vector<int> vpush = { 30,35,40,50,43,36,60,51,70,90,66,77,23,21,49,88,73 };
    for (auto i : vpush) {
        h.push(i);
        h.print();
    }
    cout << "--------------------------------" << endl;

        for (int j = 0; j < 5; j++) {
            h.pop();
            h.print();
        }
}
