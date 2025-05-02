#include <iostream>
using namespace std;

template <class T>
struct node {
	T valor;
	node<T>* next = nullptr;
	node(T v, node<T>* n = nullptr) : valor(v), next(n) {}
};

template <class T>
class LinkedList {
private:
public:
	node<T>* head = nullptr;
	void push(T x);
	void print();
	void Rotate(int k);
};


template <class T>
void LinkedList<T>::push(T x) {
	node<T>* newnode = new node<T>(x);
	if (head == nullptr) {
		head = newnode;
	}
	else {
		newnode->next = head;
		head = newnode;
	}
}


template <class T>
void LinkedList<T>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}


template <class T>
void LinkedList<T>::Rotate(int k) {
	if (head == nullptr || head->next == nullptr || k == 0) {
		return;
	}

	for (int i = 0; i < k; i++) {
		node<T>** tail = &head;
		for(; (*tail)->next != nullptr ; tail = &((*tail)->next));
		(*tail)->next = head;
		head = *tail;
		*tail = nullptr;
	}
}



int main() {
	LinkedList<int> l1, l2;
	l1.push(5);
	l1.push(4);
	l1.push(3);
	l1.push(2);
	l1.push(1);

	l1.print();
	l1.Rotate(2);
	l1.print();

	l2.push(2);
	l2.push(1);
	l2.push(0);
	l2.print();
	l2.Rotate(4);
	l2.print();
}
