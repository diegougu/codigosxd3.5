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
	void nextLargerNodes(vector<T>& vals);
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
void LinkedList<T>::nextLargerNodes(vector<T>& vals) {
	if (head == nullptr || head->next == nullptr) {
		return;
	}

	node<T>* p = head;
	bool input = false;
	while (p != nullptr) {
		node<T>* q = p->next;
		for (; q && input == false; q = q->next) {
			if (q->valor > p->valor) {
				vals.push_back(q->valor);
				input = true;
			}
		}

		if (input == false) {
			vals.push_back(0);
		}
		input = false;
		p = p->next;
	}
}



int main() {
	LinkedList<int> l1, l2;
	l1.push(5);
	l1.push(1);
	l1.push(2);
	l1.print();
	vector<int> vals, vals2;
	l1.nextLargerNodes(vals);
	for (int i = 0; i < vals.size(); i++) {
		cout << vals[i] << " ";
	}
	cout << endl;

	l2.push(5);
	l2.push(3);
	l2.push(4);
	l2.push(7);
	l2.push(2);
	l2.print();
	l2.nextLargerNodes(vals2);
	for (int i = 0; i < vals2.size(); i++) {
		cout << vals2[i] << " ";
	}
	cout << endl;
}
