#include <iostream>
using namespace std;

class SparseMatrix0 {
public:
	int xm, ym;
	int** map = nullptr;
	SparseMatrix0(int _x, int _y) : xm(_x), ym(_y) {
		map = new int* [xm];
		for (int i = 0; i < xm; i++) {
			map[i] = nullptr;
		}
	}
	void set(int x, int y, int v);
	int get(int x, int y);
	void print();
};

void SparseMatrix0::set(int x, int y, int v) {
	if (x > xm || y > ym || x < 0 || y < 0) {
		return;
	}

	if (map[x] == nullptr) {
		map[x] = new int[ym];
		for (int i = 0; i < ym; i++) {
			map[x][i] = 0;
		}
		map[x][y] = v;
	}
	else {
		map[x][y] = v;
	}
}

int SparseMatrix0::get(int x, int y) {
	if (x > xm || y > ym || x < 0 || y < 0) {
		return -1;
	}
	
	if (map[x] == nullptr) {
		return 0;
	}
	else {
		return map[x][y];
	}
}

void SparseMatrix0::print() {
	for (int i = 0; i < xm; i++) {
		for (int j = 0; j < ym; j++) {
			cout << "(" << i << ", " << j << ", " << get(i, j) << ")" << endl;
		}
	}
	cout << endl;
}

int main() {
	SparseMatrix0 m(5, 5);
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
