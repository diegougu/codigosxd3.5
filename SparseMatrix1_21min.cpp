#include <iostream>
using namespace std;

struct node {
	int val, x, y;
	node* next = nullptr;
	node(int _v, int _x, int _y, node* n = nullptr) : val(_v), x(_x), y(_y), next(n) {}
};

class SparseMatrix1 {
public:
	int ejex, ejey;
	SparseMatrix1(int _ejex, int _ejey) : ejex(_ejex), ejey(_ejey) {}
	void set(int x, int y, int v);
	int get(int x, int y);
	void print();
private:
	node* head = nullptr;
	bool find(int x, int y, node**& p);
};

bool SparseMatrix1::find(int x, int y, node**& p) {
	p = &head;
	for (; *p && (*p)->x < x; p = &((*p)->next));

	for (; *p && (*p)->y < y && (*p)->x == x; p = &((*p)->next));

	return *p && (*p)->x == x && (*p)->y == y;
}

void SparseMatrix1::set(int x, int y, int v) {
	if (x >= ejey || y >= ejey || x < 0 || y < 0) {
		return;
	}

	node** p;
	if (find(x, y, p)) {
		if (v != 0) {
			(*p)->val = v;
		}
		else {
			node* temp = *p;
			*p = temp->next;
			delete temp;
		}
	}
	else {
		node* newnode = new node(v, x, y);
		newnode->next = *p;
		*p = newnode;
	}
}

int SparseMatrix1::get(int x, int y) {
	if (x >= ejey || y >= ejey || x < 0 || y < 0) {
		return -1;
	}
	
	node** p;
	if (find(x, y, p)) {
		return (*p)->val;
	}
	else {
		return 0;
	}
}

void SparseMatrix1::print() {
	for (node* p = head; p; p = p->next) {
		cout << "( " << p->x << ", " << p->y << ", " << p->val << " )" << " ";
	}
	cout << endl;
}

int main() {
	SparseMatrix1 m(5, 5);
	m.set(1, 1, 11);
	m.set(0, 0, 12);
	m.set(0, 2, 13);
	m.set(1, 0, 14);
	m.set(0, 1, 15);
	m.set(3, 0, 16);
	m.set(3, 3, 17);
	m.set(2, 2, 18);
	m.set(1, 3, 19);
	m.set(2, 0, 20);
	m.set(2, 4, 21);
	m.set(2, 3, 22);
	m.set(2, 1, 23);
	m.print();
}
