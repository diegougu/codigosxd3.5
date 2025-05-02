#include <iostream>
#include <vector>
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
	int pairSum();
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
int LinkedList<T>::pairSum() {
	node<T>* ini = head;
	node<T>* fin = head;
	for (; fin->next != nullptr; fin = fin->next);

	int maxsum = INT_MIN;
	while (fin->next != ini) {
		if (ini->valor + fin->valor > maxsum) {
			maxsum = ini->valor + fin->valor;
		}

		ini = ini->next;
		node<T>* newfin = head;
		for (; newfin->next != fin; newfin = newfin->next);
		fin = newfin;
	}
	return maxsum;

}



int main() {
	LinkedList<int> l1, l2, l3;
	l1.push(1);
	l1.push(2);
	l1.push(4);
	l1.push(5);
	l1.print();
	cout << l1.pairSum() << endl;
	l2.push(3);
	l2.push(2);
	l2.push(2);
	l2.push(4);
	l2.print();
	cout << l2.pairSum() << endl;
}
