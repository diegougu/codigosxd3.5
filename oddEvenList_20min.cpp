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
	void oddEvenList();
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
void LinkedList<T>::oddEvenList() {
	if (head == nullptr || head->next == nullptr) {
		return;
	}

	int i = 1;
	node<T>** p = &head;
	while (*p) {
		if (i % 2 != 0 && *p != head){
			node<T>* temp = *p;
			*p = temp->next;
			temp->next = head;
			head = temp;
		}
		else {
			p = &((*p)->next);
		}
		i++;
	}
}



int main() {
	LinkedList<int> l1, l2;

	l1.push(10);
	l1.push(9);
	l1.push(5);
	l1.push(3);
	l1.push(1);
	l1.print();
	l1.oddEvenList();
	l1.print();

	l2.push(7);
	l2.push(4);
	l2.push(6);
	l2.push(5);
	l2.push(3);
	l2.push(1);
	l2.push(2);
	l2.print();
	l2.oddEvenList();
	l2.print();
}
