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
	void partition(int x);
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
void LinkedList<T>::partition(int x) {
	if (head == nullptr || head->next == nullptr) {
		return;
	}

	node<T>* save = head;
	node<T>** p = &head;
	while (*p) {
		if ((*p)->valor < x && *p != head) {
			if (save == head && save->valor >= x) {
				node<T>* save3 = *p;
				*p = (*p)->next;
				save3->next = save;
				save = save3;
				head = save3;
			}
			else {
				node<T>* save2 = (*p)->next;
				(*p)->next = save->next;
				save->next = *p;
				*p = save2;
				save = save->next;
			}
		}
		else {
			p = &((*p)->next);
		}
	}

}



int main() {
	LinkedList<int> l1, l2, l3;
	l1.push(2);
	l1.push(5);
	l1.push(2);
	l1.push(3);
	l1.push(4);
	l1.push(1);
	l1.print();
	l1.partition(3);
	l1.print();


	l2.push(1);
	l2.push(2);
	l2.print();
	l2.partition(2);
	l2.print();


	l3.push(1);
	l3.push(4);
	l3.push(3);
	l3.push(2);
	l3.push(1);
	l3.push(5);
	l3.push(7);
	l3.push(4);
	l3.push(8);
	l3.print();
	l3.partition(5);
	l3.print();
}
