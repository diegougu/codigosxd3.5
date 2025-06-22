#include <iostream>
using namespace std;

struct node {
	int val, x, y;
	node* next = nullptr;
	node(int _v, int _x, int _y, node* n = nullptr) : val(_v), x(_x), y(_y), next(n) {}
};

class SparseMatrix2 {
public:
	int mx, my;
	node** mapx = nullptr;
	SparseMatrix2(int _x, int _y) : mx(_x), my(_y) {
		mapx = new node* [mx];
		for (int i = 0; i < mx; i++) {
			mapx[i] = nullptr;
		}
	}
	void set(int x, int y, int v);
	int get(int x, int y);
	void print();
private:
	bool find(int x, int y, node**& p);
};

bool SparseMatrix2::find(int x, int y, node**& p) {
	p = &mapx[x];
	for (; *p && (*p)->y < y; p = &((*p)->next));
	return *p && (*p)->x == x && (*p)->y == y;
}

void SparseMatrix2::set(int x, int y, int v) {
	if (x > mx || y > my || x < 0 || y < 0) {
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

int SparseMatrix2::get(int x, int y) {
	if (x > mx || y > my || x < 0 || y < 0) {
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

void SparseMatrix2::print() {
	for (int i = 0; i < mx; i++) {
		for (int j = 0; j < my; j++) {
			cout << "(" << i << ", " << j << ", " << get(i, j) << ")" << endl;
		}
	}
	cout << endl;
}

int main() {
	SparseMatrix2 m(5, 5);
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
