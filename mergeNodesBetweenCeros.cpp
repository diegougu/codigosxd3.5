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
	void mergeNodesBetweenCeros();
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
void LinkedList<T>::mergeNodesBetweenCeros() {
	if (head == nullptr) {
		return;
	}

	node<T>** p = &head;
	while (*p) {
		int carry = 0;
		node<T>** q = p;
		do {
			carry += (*q)->valor;
			q = &((*q)->next);
		} while ((*q)->valor != 0);

		*p = *q;
		(*q)->valor = carry;
		p = &((*p)->next);
	}

}



int main() {
	LinkedList<int> l1, l2;
	l1.push(0);
	l1.push(2);
	l1.push(5);
	l1.push(4);
	l1.push(0);
	l1.push(1);
	l1.push(3);
	l1.push(0);
	l1.print();
	l1.mergeNodesBetweenCeros();
	l1.print();

	l2.push(0);
	l2.push(2);
	l2.push(2);
	l2.push(0);
	l2.push(3);
	l2.push(0);
	l2.push(1);
	l2.push(0);
	l2.print();
	l2.mergeNodesBetweenCeros();
	l2.print();

}
