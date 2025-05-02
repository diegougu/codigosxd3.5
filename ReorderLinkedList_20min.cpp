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
	void Reorder();
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
void LinkedList<T, C>::Reorder() {
	if (head == nullptr || head->next == nullptr) {
		return;
	}
	node<T>** p = &head;
	while (*p && (*p)->next != nullptr) {
		node<T>** q = &((*p)->next);
		for (; (*q)->next != nullptr; q = &((*q)->next));
		node<T>* save = *q;
		*q = (*q)->next;
		save->next = (*p)->next;
		(*p)->next = save;
		p = &save;

		p = &((*p)->next);
	}
}

int main() {
	LinkedList<int, ASC<int>> l1, l2, l3, l4, l5;
	for (int i = 0; i < 5; i++) {
		l1.add(i);
	}
	l1.print();
	l1.Reorder();
	l1.print();

	for (int i = 0; i < 10; i++) {
		l2.add(i);
	}
	l2.print();
	l2.Reorder();
	l2.print();

	for (int i = 0; i < 7; i++) {
		l3.add(i);
	}
	l3.print();
	l3.Reorder();
	l3.print();

	for (int i = 0; i < 2; i++) {
		l4.add(i);
	}
	l4.print();
	l4.Reorder();
	l4.print();
}
