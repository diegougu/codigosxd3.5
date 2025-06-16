#include <iostream>
#include <vector>

using namespace std;

template <class T>
struct CLess {
	bool operator()(T a, T b) {
		return a < b;
	}
};

template <class T>
struct CGreater {
	bool operator()(T a, T b) {
		return a > b;
	}
};

template <class T, class C>
class PriorityQueue {
private:
	vector<T> priorityq;
public:
	void push(T x);
	void pop();
	void print();
};

template <class T, class C>
void PriorityQueue<T, C>::push(T x) {
	C comp;
	priorityq.push_back(x);
	int pos = priorityq.size() - 1;
	bool verify = true;
	while (pos > 0 && verify == true) {
		int newpos = (pos % 2 == 0) ? (pos / 2) - 1 : (pos / 2);
		if (comp(priorityq[pos], priorityq[newpos])) {
			swap(priorityq[pos], priorityq[newpos]);
			pos = newpos;
		}
		else {
			verify = false;
		}
	}
}


template <class T, class C>
void PriorityQueue<T, C>::pop() {
	if (priorityq.empty()) {
		return;
	}
	C comp;
	swap(priorityq.front(), priorityq.back());
	priorityq.pop_back();

	int pos = 0;
	bool verify = true;
	while (pos < priorityq.size() && verify == true) {
		int left = (pos * 2) + 1;
		int right = (pos + 1) * 2;

		if (left <= priorityq.size() - 1 && right <= priorityq.size() - 1 && comp(priorityq[left], priorityq[right])) {
			if (comp(priorityq[left], priorityq[pos])) {
				swap(priorityq[left], priorityq[pos]);
				pos = left;
			}
			else {
				verify = false;
			}
		}
		else if (left <= priorityq.size() - 1 && right > priorityq.size() - 1) {
			if (comp(priorityq[left], priorityq[pos])) {
				swap(priorityq[left], priorityq[pos]);
				pos = left;
			}
			else {
				verify = false;
			}
		}
		else if (left <= priorityq.size() - 1 && right <= priorityq.size() - 1 && comp(priorityq[right] , priorityq[left])) {
			if (comp(priorityq[right], priorityq[pos])) {
				swap(priorityq[right], priorityq[pos]);
				pos = right;
			}
			else {
				verify = false;
			}
		}
		else if (left > priorityq.size() - 1 && right <= priorityq.size() - 1) {
			if (comp(priorityq[right], priorityq[pos])) {
				swap(priorityq[right], priorityq[pos]);
				pos = right;
			}
			else {
				verify = false;
			}
		}
		else {
			verify = false;
		}
	}
}

template <class T, class C>
void PriorityQueue<T, C>::print() {
	for (int i = 0; i < priorityq.size(); i++) {
		cout << priorityq[i] << " ";
	}
	cout << endl;
}


int main() {
	PriorityQueue<int, CGreater<int>> pq;
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
