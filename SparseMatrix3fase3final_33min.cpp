#include <iostream>
using namespace std;

class SparseMatrix3;
struct objx;

struct node {
	int val, x, y;
	node* next = nullptr;
	node* down = nullptr;
	node(int _x, int _y, int _v) : x(_x), y(_y), val(_v) {}
};


class SparseMatrix3 {
public:
	int xl, yl;
	node** mapx = nullptr;
	node** mapy = nullptr;
	SparseMatrix3(int x, int y) : xl(x), yl(y) {
		mapx = new node* [xl];
		for (int i = 0; i < xl; i++) {
			mapx[i] = nullptr;
		}

		mapy = new node* [yl];
		for (int i = 0; i < yl; i++) {
			mapy[i] = nullptr;
		}
	}

	void set(int x, int y, int v);
	int get(int x, int y);
	objx operator()(int x, int y);
	void print();
private:
	bool findnext(node**& p, int x, int y);
	bool finddown(node**& q, int x, int y);
};

struct objx {
	SparseMatrix3* m = nullptr;
	objx(SparseMatrix3* m_ = nullptr) : m(m_) {}
	int x, y;
	objx operator=(int v) {
		m->set(x, y, v);
		return *this;
	}

	operator int() {
		return m->get(x, y);
	}

	objx operator=(objx& ox) {
		m->set(x, y, ox.m->get(ox.x, ox.y));
		return *this;
	}
};

bool SparseMatrix3::findnext(node**& p, int x, int y) {
	p = &mapx[x];
	for (; *p && (*p)->x == x && (*p)->y < y; p = &((*p)->next));
	return *p && (*p)->x == x && (*p)->y == y;
}

bool SparseMatrix3::finddown(node**& q, int x, int y) {
	q = &mapy[y];
	for (; *q && (*q)->y == y && (*q)->x < x; q = &((*q)->down));
	return *q && (*q)->x == x && (*q)->y == y;
}

void SparseMatrix3::set(int x, int y, int v) {
	if (x >= xl || y >= yl || x < 0 || y < 0) {
		return;
	}
	
	node** p;
	node** q;
	bool fn = findnext(p, x, y);
	bool fd = finddown(q, x, y);
	if (fn && fd) {
		if (v != 0) {
			(*p)->val = v;
		}
		else {
			node* temp = *p;
			node* temp2 = *q;
			*p = temp->next;
			*q = temp2->down;
			delete temp;
			delete temp2;
		}
	}
	else {
		if (v != 0) {
			node* newnode = new node(x, y, v);
			newnode->next = *p;
			newnode->down = *q;
			*p = newnode;
			*q = newnode;
		}
	}
}

int SparseMatrix3::get(int x, int y) {
	if (x >= xl || y >= yl || x < 0 || y < 0) {
		return -1;
	}
	node** p;
	if (findnext(p, x, y)) {
		return (*p)->val;
	}
	return 0;
}

objx SparseMatrix3::operator()(int x, int y) {
	objx ox(this);
	ox.x = x;
	ox.y = y;
	return ox;
}

void SparseMatrix3::print() {
	for (int i = 0; i < xl; i++) {
		for (int j = 0; j < yl; j++) {
			cout << "( " << i << ", " << j << ", " << get(i, j) << " )" << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main() {
	SparseMatrix3 m(4, 4);

	objx val1 = m(0, 1);
	objx val2 = m(0, 2);
	objx val3 = m(0, 0);
	objx val4 = m(1, 1);
	objx val5 = m(1, 3);
	objx val6 = m(1, 2);
	objx val7 = m(3, 1);
	objx val8 = m(3, 2);

	cout << (int)val1 << endl;
	cout << (int)val2 << endl;
	cout << (int)val3 << endl;
	cout << (int)val4 << endl;
	cout << (int)val5 << endl;
	cout << (int)val6 << endl;
	cout << (int)val7 << endl;
	cout << (int)val8 << endl;

	cout << "------------------------------" << endl;

	m(0, 1) = 10;
	m(0, 2) = 20;
	m(0, 0) = 30;
	m(1, 1) = 40;
	m(1, 3) = 50;
	m(1, 2) = 60;
	m(3, 1) = 70;
	m(3, 2) = 80;

	cout << (int)m(0, 1) << endl;
	cout << (int)m(0, 2) << endl;
	cout << (int)m(0, 0) << endl;
	cout << (int)m(1, 1) << endl;
	cout << (int)m(1, 3) << endl;
	cout << (int)m(1, 2) << endl;
	cout << (int)m(3, 1) << endl;
	cout << (int)m(3, 2) << endl;

	m(0, 1) = 900;
	m(0, 2) = 1000;
	m(0, 0) = 1100;

	cout << "------------------------------" << endl;
	cout << (int)m(0, 1) << endl;
	cout << (int)m(0, 2) << endl;
	cout << (int)m(0, 0) << endl;

	m(0, 1) = m(3, 2);

	cout << "------------------------------" << endl;
	cout << (int)m(0, 1) << endl;
	m.print();

	return 0;
}
