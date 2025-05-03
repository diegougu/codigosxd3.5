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
	void removeNodes();
	void inverse();
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
void LinkedList<T>::inverse() {
	node<T>* tail = head;
	for (; tail->next; tail = tail->next);
	node<T>* copyt = tail;
	while (head != tail) {
		node<T>* p = head;
		for (; p->next != tail; p = p->next);
		tail->next = p;
		tail = p;
	}
	head->next = nullptr;
	head = copyt;
}

template <class T>
void LinkedList<T>::removeNodes() {
	if (head == nullptr || head->next == nullptr) {
		return;
	}
	inverse();
	for (node<T>* p = head; p; p = p->next) {
		node<T>* q = p->next;
		for (; q && q->valor < p->valor; q = q->next);
		p->next = q;
	}

	inverse();

}



int main() {
	LinkedList<int> l1, l2;
	l1.push(8);
	l1.push(3);
	l1.push(13);
	l1.push(2);
	l1.push(5);
	l1.print();
	l1.removeNodes();
	l1.print();

}
