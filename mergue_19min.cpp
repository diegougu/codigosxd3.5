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
	void find(C comp, T x, node<T>**& p);
public:
	node<T>* head = nullptr;
	void add(T x);
	void del(T x);
	void print();
	void mergue(LinkedList<T, C>& l2);
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
void LinkedList<T, C>::mergue(LinkedList<T, C>& l2) {
	if (head == nullptr && l2.head == nullptr) {
		return;
	}

	node<T>** p = &head;
	node<T>** q = &l2.head;

	while (*p && *q) {
		if (*p && * q && (*p)->valor > (*q)->valor) {
			node<T>* save = (*q)->next;
			(*q)->next = *p;
			*p = *q;
			*q = save;
		}
		else {
			p = &((*p)->next);
		}
	}

	if (l2.head != nullptr) {
		*p = l2.head;
		l2.head = nullptr;
	}
}


int main() {
	LinkedList<int, ASC<int>> l1, l2, l3, l4, l5, l6;
	l1.add(1);
	l1.add(3);
	l1.add(5);
	l1.add(9);
	l1.print();

	l2.add(0);
	l2.add(2);
	l2.add(4);
	l2.add(6);
	l2.add(7);
	l2.add(8);
	l2.add(10);
	l2.print();
	l1.mergue(l2);
	l1.print();
	l2.print();

	l3.add(1);
	l3.add(2);
	l3.add(3);
	l3.add(4);
	l3.add(5);
	l3.add(9);
	l3.print();

	l4.add(7);
	l4.add(8);
	l4.add(10);

	l4.print();
	l3.mergue(l4);
	l3.print();
	l4.print();

	l5.add(5);
	l5.add(6);
	l5.add(7);
	l5.add(8);
	l5.add(9);

	l5.print();
	l6.add(1);
	l6.add(2);
	l6.add(3);
	l6.add(4);

	l6.print();

	l5.mergue(l6);
	l5.print();
	l6.print();
}
