#include <iostream>
#include <math.h>

using namespace std;

template <class T>
struct CGreater {
	bool operator()(T a, T b) {
		return a > b;
	}
};

template <class T>
struct CLess {
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

template<class T, class C>
class CircularLinkedList {
private:
	bool find(T x, C comp, node<T>**& p);
public:
	node<T>* head = nullptr;
	void add(T x);
	void del(T x);
	void print();
	void SplitaCircularLinkedListintotwohalves(CircularLinkedList<T, C>& l2);
};


template <class T, class C>
bool CircularLinkedList<T, C>::find(T x, C comp, node<T>**& p) {
	do {
		p = &((*p)->next);
	} while (*p != head && comp(x, (*p)->valor));

	return (*p)->valor == x;
}


template <class T, class C>
void CircularLinkedList<T, C>::add(T x) {
	C comp;
	node<T>** p = &head;
	if (*p && find(x, comp, p)) {
		return;
	}

	node<T>* newnode = new node<T>(x);
	if (*p && !comp(x, head->valor)) {
		node<T>* q = head;
		do {
			q = q->next;
		} while (q->next != head);
		newnode->next = head;
		q->next = newnode;
		head = newnode;

	}
	else {
		newnode->next = *p;
		*p = newnode;
		if (head->next == nullptr) {
			head->next = head;
		}
	}
}


template <class T, class C>
void CircularLinkedList<T, C>::print() {
	node<T>* p = head;
	if (head == nullptr) {
		cout << "nullptr" << endl;
		return;
	}
	do {
		cout << p->valor << " ";
		p = p->next;
	} while (p != head);
	cout << endl;
}

template <class T, class C>
void CircularLinkedList<T, C>::del(T x) {
	C comp;
	node<T>** p = &head;
	if (head == nullptr || (!find(x, comp, p) && head->valor != x)) {
		return;
	}


	if (x == head->valor) {
		node<T>* q = head;
		do {
			q = q->next;
		} while (q->next != head);

		node<T>* temp = head;
		head = head->next;
		q->next = head;

		if (x == head->valor && head->next == head) {
			head = nullptr;
		}
		delete temp;
	}
	else {
		node<T>* temp = *p;
		*p = temp->next;
		delete temp;
	}
}

template <class T, class C>
void CircularLinkedList<T, C>::SplitaCircularLinkedListintotwohalves(CircularLinkedList<T, C>& l2) {
	if (head == nullptr) {
		return;
	}
	
	int size = 1;
	int mita = 1;
	node<T>* p = head;
	node<T>* mitad = head;
	bool segunda_vuelta = false;
	int compare = 0;
	do {
		p = p->next;
		if (segunda_vuelta == false) {
			size++;
		}
		else if (segunda_vuelta == true && mita != compare) {
			mitad = mitad->next;
			mita++;
		}

		if (p->next == head && segunda_vuelta == false) {
			p = head;
			segunda_vuelta = true;
			compare = (size % 2 == 0) ? size / 2 : size / 2 + 1;
		}

	} while (p->next != head);

	node<T>* temp = mitad->next;
	mitad->next = head;
	l2.head = temp;
	node<T>* x = l2.head;
	for (; x->next != head; x = x->next);
	x->next = l2.head;

}

int main() {
	CircularLinkedList<int, CGreater<int>> l1, l2, l3, l4;
	for (int i = 0; i < 3; i++) {
		l1.add(i);
	}
	l1.print();
	l1.SplitaCircularLinkedListintotwohalves(l2);
	l1.print();
	l2.print();

	for (int i = 0; i < 8; i++) {
		l3.add(i);
	}
	l3.print();
	l3.SplitaCircularLinkedListintotwohalves(l4);
	l3.print();
	l4.print();
}
