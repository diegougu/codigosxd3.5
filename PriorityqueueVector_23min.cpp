#include <iostream>
#include <vector>
using namespace std;

template <class T>
struct cless {
	bool operator()(T a, T b) {
		return a < b;
	}
};

template <class T>
struct cgreater {
	bool operator()(T a, T b) {
		return a > b;
	}
};

template <class T, class C>
class PriorityQueue {
public:
	C comp;
	vector<T> pq;
	void push(T v);
	void pop();
	void print();
};

template <class T , class C>
void PriorityQueue<T, C>::push(T v) {
	pq.push_back(v);
	int pos = pq.size() - 1;
	bool stop = false;
	while (pos > 0 && stop == false) {
		int newpos = (pos % 2 == 0) ? (pos / 2) - 1 : (pos / 2);
		if (comp(pq[pos], pq[newpos])) {
			swap(pq[pos], pq[newpos]);
			pos = newpos;
		}
		else {
			stop = true;
		}
	}
}

template <class T, class C>
void PriorityQueue<T, C>::pop() {
	if (pq.empty()) return;
	swap(pq.front(), pq.back());
	pq.pop_back();
	int pos = 0; 
	bool stop = false;
	while (pos < pq.size() && stop == false) {
		int left = (pos * 2) + 1;
		int right = (pos + 1) * 2;

		if (left < pq.size() && right < pq.size()) {
			if (comp(pq[left], pq[right]) && comp(pq[left], pq[pos])) {
				swap(pq[pos], pq[left]);
				pos = left;
			}
			else if (comp(pq[right], pq[left]) && comp(pq[right], pq[pos])) {
				swap(pq[pos], pq[right]);
				pos = right;
			}
			else {
				stop = true;
			}
		}
		else if (left < pq.size() && right >= pq.size() && comp(pq[left], pq[pos])) {
			swap(pq[pos], pq[left]);
			pos = left;
		}
		else if (left >= pq.size() && right < pq.size() && comp(pq[right], pq[pos])) {
			swap(pq[pos], pq[right]);
			pos = right;
		}
		else {
			stop = true;
		}
	}
}

template <class T, class C>
void PriorityQueue<T, C>::print() {
	for (int i = 0; i < pq.size(); i++) {
		cout << pq[i] << " ";
	}
	cout << endl;
}


int main() {
	PriorityQueue<int, cgreater<int>> pq;
	pq.push(20);
	pq.print();
	pq.push(50);
	pq.print();
	pq.push(70);
	pq.print();
	pq.push(80);
	pq.print();
	pq.push(10);
	pq.print();
	pq.push(5);
	pq.print();
	pq.push(90);
	pq.print();
	pq.push(100);
	pq.print();
	pq.push(40);
	pq.print();
	pq.push(30);
	pq.print();

	cout << "-----------------" << endl;
	pq.pop();
	pq.print();
	pq.pop();
	pq.print();
	pq.pop();
	pq.print();
	pq.pop();
	pq.print();
	pq.pop();
	pq.print();
	pq.pop();
	pq.print();
}
