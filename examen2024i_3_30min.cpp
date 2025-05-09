#include <iostream>
using namespace std;
class XVector
{
public:
    XVector(int size_map, int size_vec);
    ~XVector();
    void expand(int newsize_map);
    void push_back(int v);
    void push_front(int v);
    int& operator[](int pos);
    int elements = 0;
    int** map = nullptr;
    int** fin_map = nullptr;
    int* fin_vec = nullptr;
    int size_map, size_vec;
};

XVector::XVector(int sm, int sv)
{
    size_map = sm;
    size_vec = sv;
    map = new int* [size_map];
    fin_map = map;
}

XVector::~XVector()
{}

int& XVector::operator[](int pos) {
    if (pos >= elements) {
        static int x;
        return x;
    }
    int vec_pos = pos % size_vec;
    int map_pos = pos / size_vec;

    int** m = map + map_pos;
    int* v = *m + vec_pos;
    return *v;
}

void XVector::expand(int newsize_map) {
    int** newmap = new int* [newsize_map];
    for (int i = 0; i < size_map; i++) {
        newmap[i] = map[i];
    }
    int** temp = map;
    fin_map = newmap + size_map - 1;
    map = newmap;
    size_map = newsize_map;
    delete temp;
}

void XVector::push_back(int v) {
    if (fin_vec == nullptr) {
        *fin_map = new int[size_vec];
        fin_vec = *fin_map;
        *fin_vec = v;
    }
    else if (fin_vec == *fin_map + size_map - 1) {
        if (fin_map == map + size_map - 1) {
            expand(size_map * 2);
        }
        fin_map++;
        *fin_map = new int[size_vec];
        fin_vec = *fin_map;
        *fin_vec = v;
    }
    else {
        fin_vec++;
        *fin_vec = v;
    }
    elements++;
}

void XVector::push_front(int v) {
    if (fin_vec == nullptr) {
        *fin_map = new int[size_vec];
        fin_vec = *fin_map;
        *fin_vec = v;
    }
    else {
        if (fin_vec == *fin_map + size_map - 1) {
            if (fin_map == map + size_map - 1) {
                expand(size_map * 2);
            }
            fin_map++;
            *fin_map = new int[size_vec];
            fin_vec = *fin_map;
        }
        else {
            fin_vec++;
        }
        int* ite_vec = fin_vec;
        int** ite_map = fin_map;

        while (ite_map >= map) {
            while (ite_vec >= *ite_map) {
                if (ite_vec == *ite_map && ite_map != map) {
                    int** past = ite_map - 1;
                    *ite_vec = *(*past + size_vec - 1);
                }
                else {
                    *ite_vec = *(ite_vec - 1);
                }
                ite_vec--;
            }
            ite_map--;
            if (ite_map >= map) {
                ite_vec = *ite_map + size_vec - 1;
            }
        }
        **map = v;
    }
    elements++;
}

void print(XVector* p)
{ //no modificar esta función
    for (int i = 0; i < p->size_vec; i++)
        std::cout << (*p)[i] << " ";
    std::cout << "\n";
}

int main()
{
    //no modificar esta función main
    XVector v(4, 3);
    v.push_back(3); v.push_back(8); v.push_back(1);
    v.push_back(4); v.push_back(9); v.push_back(6);
    v.push_back(7);
    print(&v);
    v.push_front(5); v.push_front(2);
    print(&v);
    v.push_front(11); v.push_front(17);
    v.push_back(22);
    print(&v);
    v.push_front(33); v.push_back(77);
    print(&v);
}
