#include <iostream>
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


template <class T>
struct node {
	T val;
	node* next = nullptr;
	node(T v, node* n = nullptr) : val(v), next(n) {}
};

template <class T, class C>
class LinkedPriortyQueue {
private:
	node<T>* head = nullptr;
	int elements = 0;
public:
	void push(T x);
	void pop();
	void print();
};

template <class T, class C>
void LinkedPriortyQueue<T, C>::push(T x) {
	node<T>* newnode = new node<T>(x);
	if (head == nullptr) {
		head = newnode;
		elements++;
	}
	else {
		C comp;
		node<T>* pos = head;
		for (; pos->next != nullptr; pos = pos->next);
		pos->next = newnode;
		pos = newnode;
		elements++;
		bool verify = true;
		int poslogic = elements - 1;
		while (pos != head && verify == true) {
			int newposlogic = (poslogic % 2 == 0) ? (poslogic / 2) - 1 : (poslogic / 2);
			node<T>* newpos = head;
			for (int i = 0; i < newposlogic; i++) {
				newpos = newpos->next;
			}

			if (comp(pos->val, newpos->val)) {
				swap(newpos->val, pos->val);
				pos = newpos;
				poslogic = newposlogic;
			}
			else {
				verify = false;
			}

		}
	}
}


template <class T, class C>
void LinkedPriortyQueue<T, C>::pop() {
	if (head == nullptr) {
		return;
	}
	else if (head->next == nullptr) {
		node<T>* temp = head;
		head = nullptr;
		delete temp;
		elements--;
	}
	else {
		C comp;
		node<T>** temp = &head;
		for (; (*temp)->next != nullptr; temp = &((*temp)->next));
		swap(head->val, (*temp)->val);
		node<T>* del = *temp;
		*temp = nullptr;
		delete del;
		elements--;
		node<T>* pos = head;
		int poslogic = 0;
		bool verify = true;

		while (pos != nullptr && poslogic < elements && verify == true) {
			int leftlogic = (poslogic * 2) + 1;
			int rightlogic = (poslogic + 1) * 2;
			node<T>* left = head;
			node<T>* right = head;
			for (int i = 0; left != nullptr && i < leftlogic; i++) {
				left = left->next;
			}

			for (int i = 0; right != nullptr && i < rightlogic; i++) {
				right = right->next;
			}

			if (left != nullptr && right != nullptr && comp(left->val, right->val)) {
				if (comp(left->val, pos->val)) {
					swap(left->val, pos->val);
					pos = left;
					poslogic = leftlogic;
				}
				else {
					verify = false;
				}
			}
			else if (left != nullptr && right == nullptr) {
				if (comp(left->val, pos->val)) {
					swap(left->val, pos->val);
					pos = left;
					poslogic = leftlogic;
				}
				else {
					verify = false;
				}
			}
			else if (left != nullptr && right != nullptr && comp(right->val, left->val)) {
				if (comp(right->val, pos->val)) {
					swap(right->val, pos->val);
					pos = right;
					poslogic = rightlogic;
				}
				else {
					verify = false;
				}
			}
			else if (left == nullptr && right != nullptr) {
				if (comp(right->val, pos->val)) {
					swap(right->val, pos->val);
					pos = right;
					poslogic = rightlogic;
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
}

template <class T, class C>
void LinkedPriortyQueue<T, C>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->val << " ";
	}
	cout << endl;
}


int main() {
	LinkedPriortyQueue<int, CGreater<int>> pq;
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
