#include <iostream>
using namespace std;

template <class T>
struct ASC {
	bool operator()(T a, T b) {
		return a > b;
	}
};

template <class T>
struct DESC {
	bool operator()(T a, T b) {
		return a < b;
	}
};

template <class T>
struct node {
	T valor;
	node<T>* next = nullptr;
	node(T v, node<T>* n = nullptr) : valor(v), next(n) {}
};

template <class T, class C>
class LinkedList {
private:
	node<T>* head = nullptr;
	void find(C comp, T x, node<T>**& p);
public:
	void add(T x);
	void del(T x);
	void print();
	void swapNodes(int k);
};

template <class T, class C>
void LinkedList<T, C>::find(C comp, T x, node<T>**& p) {
	p = &head;
	for (; *p && comp(x, (*p)->valor); p = &((*p)->next));
}

template <class T, class C>
void LinkedList<T, C>::add(T x) {
	node<T>** p;
	C comp;
	find(comp, x, p);
	node<T>* temp = new node<T>(x);
	temp->next = *p;
	*p = temp;
}

template <class T, class C>
void LinkedList<T, C>::del(T x) {
	node<T>** p;
	C comp;
	find(comp, x, p);

	node<T>* temp = *p;
	*p = temp->next;
	delete temp;
}

template <class T, class C>
void LinkedList<T, C>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}

template <class T, class C>
void LinkedList<T, C>::swapNodes(int k) {
	if (head == nullptr || head->next == nullptr) {
		return;
	}

	node<T>* tail = head;
	for (; tail->next != nullptr; tail = tail->next);

	node<T>** a = &head;
	node<T>** b = &tail;

	for (int i = 1; i < k && *a; i++) {
		a = &((*a)->next);
	}
	
	if (*a == nullptr) {
		return;
	}

	for (int i = 1; i < k; i++) {
		node<T>** p = &head;
		for (; (*p)->next != *b; p = &((*p)->next));
		b = p;
	}

	if (a == b) {
		return;
	}

	if ((*a)->next == *b) {
		node<T>* temp = (*a)->next;
		node<T>* temp2 = *a;
		node<T>* temp3 = (*b)->next;

		*a = *b;
		(*b)->next = temp2;
		temp2->next = temp3;

	}
	else {
		node<T>* temp = (*a)->next;
		node<T>* temp2 = *a;
		(*a)->next = (*b)->next;
		*a = *b;
		(*b)->next = temp;
		*b = temp2;
	}


	
}

int main() {
	LinkedList<int, ASC<int>> l1, l2, l3, l4, l5;
	l1.add(1);
	l1.add(2);
	l1.add(3);
	l1.add(4);
	l1.add(5);
	l1.print();
	l1.swapNodes(2);
	l1.print();

	l2.add(1);
	l2.add(2);
	l2.add(3);
	l2.add(4);
	l2.add(5);
	l2.add(6);
	l2.add(7);
	l2.add(8);
	l2.print();
	l2.swapNodes(2);
	l2.print();

	l3.add(1);
	l3.add(2);
	l3.add(3);
	l3.add(4);
	l3.add(5);
	l3.add(6);
	l3.add(7);
	l3.add(8);
	l3.add(9);
	l3.add(10);
	l3.print();
	l3.swapNodes(5);
	l3.print();
}
