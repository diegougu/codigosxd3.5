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
class elementor {
private:
	node<T>* head = nullptr;
	T* ptr = nullptr;
	bool find(node<T>**& pos, T*& posptr, T x);
public:
	void add(T x);
	void del(T x);
	void print();
};


template <class T>
bool elementor<T>::find(node<T>**& pos, T*& posptr, T x) {
	pos = &head;
	posptr = head->arr;
	while (*pos) {
		while (posptr <= (*pos)->arr + (*pos)->tam - 1) {
			if (*posptr >= x) {
				return *posptr == x;
			}
			posptr++;
		}
		pos = &((*pos)->next);
		if (*pos != nullptr) {
			posptr = (*pos)->arr;
		}
	}
	return false;
}


template <class T>
void elementor<T>::add(T x) {
	if (head == nullptr) {
		node<T>* newnode = new node<T>;
		head = newnode;
		ptr = head->arr;
		*ptr = x;
	}
	else {
		if (x > *ptr) {
			node<T>* tail = head;
			for (; tail->next != nullptr; tail = tail->next);
			if (ptr == tail->arr + tail->tam - 1) {
				node<T>* newnode = new node<T>;
				tail->next = newnode;
				ptr = newnode->arr;
			}
			else {
				ptr++;
				*ptr = x;
			}
			return;
		}
		else if (x == *ptr) {
			return;
		}

		T* posptr;
		node<T>** pos;
		if (find(pos, posptr, x)) {
			return;
		}

		T temp = *posptr;
		T temp2 = *posptr;
		*posptr = x;
		posptr++;
		bool ptrinend = false;
		while (*pos) {
			while (posptr <= (*pos)->arr + (*pos)->tam - 1 && posptr <= ptr) {
				temp = *posptr;
				*posptr = temp2;
				temp2 = temp;
				posptr++;
			}
			if ((*pos)->arr + (*pos)->tam - 1 == ptr) {
				ptrinend = true;
			}
			pos = &((*pos)->next);
			if (*pos != nullptr) {
				posptr = (*pos)->arr;
			}
		}

		if (ptrinend == true) {
			node<T>* newnode = new node<T>;
			*pos = newnode;
			ptr = newnode->arr;
		}
		else {
			ptr++;
		}
		*ptr = temp;

	}
	
}

template <class T>
void elementor<T>::del(T x) {
	if (head == nullptr) {
		return;
	}
	else if(ptr == head->arr && x == *ptr){
		node<T>* temp = head;
		head = nullptr;
		ptr = nullptr;
		delete temp;
	}
	else {
		T* posptr;
		node<T>** pos;
		if (!find(pos, posptr, x)) {
			return;
		}

		bool ptrend = false;
		node<T>** tail = &head;
		while (*pos) {
			while (posptr <= (*pos)->arr + (*pos)->tam - 1 && posptr != ptr) {
				if (posptr == (*pos)->arr + (*pos)->tam - 1 && (*pos)->next != nullptr) {
					*posptr = *((*pos)->next->arr);
				}
				else {
					*posptr = *(posptr + 1);
				}
				posptr++;
			}

			if ((*pos)->arr == ptr) {
				tail = pos;
				ptrend = true;
			}

			pos = &((*pos)->next);
			if (*pos != nullptr) {
				posptr = (*pos)->arr;
			}
		}

		if (ptrend == true) {
			node<T>* temp = head;
			for (; temp->next != *tail; temp = temp->next);
			node<T>* temp2 = *tail;
			temp->next = nullptr;
			ptr = temp->arr + temp->tam - 1;
			delete temp2;
		}
		else {
			ptr--;
		}

	}
}

template <class T>
void elementor<T>::print() {
	int nodeIndex = 0;
	for (node<T>* p = head; p; p = p->next, nodeIndex++) {
		for (T* q = p->arr; q <= p->arr + p->tam - 1; q++) {
			if (q == ptr) {
				cout << *q << endl;
				return;
			}
			cout << *q << " ";
		}
	}
}



int main() {
	elementor<int> ele;
	int arr[17] = { 2,14,3,4,5,7,9,8,1,10,11,17,12,13,16,6,15 };
	for (int i = 0; i < 17; i++) {
		ele.add(arr[i]);
	}
	ele.print();
	cout << "delete" << endl;
	for (int i = 0; i < 17; i++) {
		ele.del(arr[i]);
		ele.print();
	}
}
