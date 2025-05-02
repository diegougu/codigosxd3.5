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
	void RemoveDuplicatesII();
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
void LinkedList<T, C>::RemoveDuplicatesII() {
	if (head == nullptr || head->next == nullptr) {
		return;
	}

	node<T>** p = &head;
	while (*p) {
		node<T>** q = &((*p)->next);

		if (*q && (*p)->valor == (*q)->valor) {
			for (; *q && (*q)->valor == (*p)->valor; q = &((*q)->next));
			*p = *q;
		}
		else {
			p = &((*p)->next);
		}

	}

}

int main() {
	LinkedList<int, ASC<int>> l1, l2, l3, l4, l5;
	l1.add(1);
	l1.add(2);
	l1.add(3);
	l1.add(4);
	l1.add(5);
	l1.add(6);
	l1.add(6);
	l1.add(6);
	l1.print();
	l1.RemoveDuplicatesII();
	l1.print();

	l2.add(1);
	l2.add(1);
	l2.add(1);
	l2.add(1);
	l2.add(1);
	l2.add(2);
	l2.add(3);
	l2.print();
	l2.RemoveDuplicatesII();
	l2.print();

	l3.add(1);
	l3.add(1);
	l3.add(1);
	l3.add(1);
	l3.add(2);
	l3.add(2);
	l3.add(2);
	l3.add(2);
	l3.add(2);
	l3.print();
	l3.RemoveDuplicatesII();
	l3.print();

	l4.add(1);
	l4.add(2);
	l4.add(2);
	l4.add(2);
	l4.add(3);
	l4.add(3);
	l4.print();
	l4.RemoveDuplicatesII();
	l4.print();

	l5.add(1);
	l5.add(2);
	l5.add(2);
	l5.add(3);
	l5.add(4);
	l5.add(4);
	l5.add(4);
	l5.add(5);
	l5.print();
	l5.RemoveDuplicatesII();
	l5.print();

}
