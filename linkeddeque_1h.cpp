#include <iostream>
#include <stack>
using namespace std;

template <class T>
struct node {
	const static int tam = 10;
	T arr[tam];
	node<T>* next = nullptr;
};

template <class T>
class linkeddeque {
private:
	node<T>* map = nullptr;
	node<T>* end_map = nullptr;
	int elements = 0;
	T* fin = nullptr;
public:
	void push_front(T x);
	void push_back(T x);
	void pop_back();
	void pop_front();
	T& operator[](int pos);
	void print();
};

template <class T>
void linkeddeque<T>::push_back(T x) {
	if (map == nullptr && end_map == nullptr) {
		node<T>* newnode = new node<T>;
		map = newnode;
		end_map = newnode;
		fin = map->arr;
	}
	else if (fin == end_map->arr + end_map->tam - 1) {
		node<T>* newnode = new node<T>;
		end_map->next = newnode;
		end_map = newnode;
		fin = end_map->arr;
	}
	else {
		fin++;
	}
	*fin = x;
	elements++;
}


template <class T>
void linkeddeque<T>::push_front(T x) {
	if (map == nullptr && end_map == nullptr) {
		node<T>* newnode = new node<T>;
		map = newnode;
		end_map = newnode;
		fin = map->arr;
	}
	else {
		node<T>* itenode = map;
		T* itearr = itenode->arr;
		T temp = *itearr;
		T temp2 = *itearr;
		*itearr = x;
		itearr++;
		while (itenode != nullptr) {
			while (itearr <= itenode->arr + itenode->tam - 1 && itearr != fin) {
				temp = *itearr;
				*itearr = temp2;
				temp2 = temp;
				itearr++;
			}
			itenode = itenode->next;
			if (itenode != nullptr) {
				itearr = itenode->arr;
			}
		}

		if (fin == itearr && fin != end_map->arr + end_map->tam - 1) {
			temp = *fin;
			*fin = temp2;
			temp2 = temp;
			fin++;
			*fin = temp;
		}
		else {
			node<T>* newnode = new node<T>;
			end_map->next = newnode;
			end_map = newnode;
			fin = end_map->arr;
			*fin = temp;
		}
	}
	elements++;

}

template <class T>
void linkeddeque<T>::pop_back() {
	if (map == nullptr) {
		return;
	}
	else if (fin == map->arr) {
		node<T>* temp = map;
		map = nullptr;
		fin = nullptr;
		delete temp;
	}
	else if (fin == end_map->arr) {
		node<T>* newendmap = map;
		for (; newendmap->next != end_map; newendmap = newendmap->next);
		node<T>* temp = end_map;
		newendmap->next = nullptr;
		fin = newendmap->arr + newendmap->tam - 1;
		end_map = newendmap;
		delete temp;
	}
	else {
		fin--;
	}
	elements--;

}

template <class T>
void linkeddeque<T>::pop_front() {
	if (map == nullptr) {
		return;
	}
	else if (fin == map->arr) {
		node<T>* temp = map;
		map = nullptr;
		fin = nullptr;
		delete temp;
	}
	else {
		node<T>* itenode = map;
		T* itearr = itenode->arr;
		while (itenode != nullptr) {
			while (itearr <= itenode->arr + itenode->tam - 1 && itearr != fin) {
				if (itearr == itenode->arr + itenode->tam - 1 && itenode->next != nullptr) {
					*itearr = *(itenode->next->arr);
				}
				else {
					*itearr = *(itearr + 1);
				}
				itearr++;
			}
			itenode = itenode->next;
			if (itenode != nullptr) {
				itearr = itenode->arr;
			}
		}

		if (fin == end_map->arr) {
			node<T>* newendmap = map;
			for (; newendmap->next != end_map; newendmap = newendmap->next);
			node<T>* temp = end_map;
			end_map = newendmap;
			fin = end_map->arr + end_map->tam - 1;
			end_map->next = nullptr;
			delete temp;
		}
		else {
			fin--;
		}
	}
	elements--;
}

template <class T>
void linkeddeque<T>::print() {
	node<T>* current = map;
	while (current) {
		for (int i = 0; i < node<T>::tam; i++) {
			T* pos = current->arr + i;
			cout << *pos << " ";
			if (pos == fin) {
				cout << endl;
				return;
			}
		}
		current = current->next;
	}
	cout << endl;
}

template <class T>
T& linkeddeque<T>::operator[](int pos) {
	if (pos >= elements) {
		static T i;
		return i;
	}
	else if (pos == 0) {
		return *map->arr;
	}
	else if (pos == elements - 1) {
		return *fin;
	}
	int count = 0;
	node<T>* p = map;
	while (p != nullptr) {
		for (T* q = p->arr; q < p->arr + p->tam; q++) {
			if (pos == count) {
				return *q;
			}
			count++;
		}
	}
}

int main() {
	linkeddeque<int> dq;

	for (int i = 0; i < 13; i++) {
		dq.push_back(i);
	}

	for (int i = 20; i < 27; i++) {
		dq.push_front(i);
	}

	dq.print();

	for (int i = 0; i < 5; i++) {
		dq.pop_back();
	}
	dq.print();

	for (int i = 0; i < 5; i++) {
		dq.pop_front();
		dq.print();
	}

	cout << dq[0] << endl;
	cout << dq[1] << endl;
	cout << dq[2] << endl;
	cout << dq[3] << endl;
	cout << dq[4] << endl;
	cout << dq[5] << endl;

}
