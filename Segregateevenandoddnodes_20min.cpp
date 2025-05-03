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
	void Segregateevenandoddnodes();
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
void LinkedList<T>::Segregateevenandoddnodes() {
	if (head == nullptr || head->next == nullptr) {
		return;
	}

	node<T>** p = &head;
	node<T>** save_pairs = &head;
	for (; *save_pairs && (*save_pairs)->valor % 2 == 0; save_pairs = &((*save_pairs)->next));
	if (*save_pairs == nullptr) return;
	while (*p) {
		if ((*p)->valor % 2 == 0 && *p != head) {
			node<T>* save = (*p)->next;
			(*p)->next = *save_pairs;
			*save_pairs = *p; 
			*p = save;
			save_pairs = &((*save_pairs)->next);

		}
		else {
			p = &((*p)->next);
		}

	}
	

}



int main() {
	LinkedList<int> l1, l2;

	l1.push(6);
	l1.push(4);
	l1.push(2);
	l1.push(9);
	l1.push(8);
	l1.push(15);
	l1.push(17);
	l1.print();
	l1.Segregateevenandoddnodes();
	l1.print();

	l2.push(10);
	l2.push(8);
	l2.push(5);
	l2.push(4);
	l2.push(3);
	l2.push(2);
	l2.print();
	l2.Segregateevenandoddnodes();
	l2.print();
}
