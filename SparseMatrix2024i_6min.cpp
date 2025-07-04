#include <iostream>

using namespace std;

class Nodo
{
public:
    int fil;
    int col;
    int dato;
    Nodo* next = nullptr;
    Nodo(int f, int c, int d) : fil(f), col(c), dato(d) {}
};

class SparseMatrix{
private:
    bool find(Nodo**& p, int fil, int col);
public:
    Nodo* Mat = NULL;
    void set(int fil, int col, int dato);
    void print();
};

bool SparseMatrix::find(Nodo**& p, int fil, int col) {
    p = &Mat;
    for (; *p && (*p)->fil < fil; p = &((*p)->next));
    for (; *p && (*p)->fil == fil && (*p)->col < col; p = &((*p)->next));
    return *p && (*p)->fil == fil && (*p)->col == col;
}

void SparseMatrix::set(int fil, int col, int dato)
{
    Nodo** p;
    if (find(p, fil, col)) {
        if (dato != 0) {
            (*p)->dato = dato;
        }
        else {
            Nodo* temp = *p;
            *p = temp->next;
            delete temp;
        }
    }
    else {
        if (dato != 0) {
            Nodo* newnode = new Nodo(fil, col, dato);
            newnode->next = *p;
            *p = newnode;
        }
    }
}

void SparseMatrix::print()
{
    cout << "------Mat-----" << endl;
    for (Nodo* p = Mat; p; p = p->next)
        cout << "[" << p->fil << "][" << p->col << "] = " << p->dato << endl;
    cout << "------FIN Mat-----" << endl;
}

int main()
{
    SparseMatrix SM;

    int a[10][10] = { {0,10,20,30,40,50,60,70,80,90},
{10,20,30,40,50,60,70,0,80,90},
{10,20,30,0,50,60,70,80,90,0},
{20,10,90,0,10,20,60,70,80,0},
{30,20,90,10,20,30,70,0,80,10},
{30,20,0,10,20,30,70,80,90,10},
{80,20,20,20,0,60,0,90,90,0},
{70,10,30,30,0,70,70,80,80,0},
{0,20,30,20,10,70,0,80,80,10},
{80,20,90,30,10,0,80,90,90,10},
    };

    int b[10][10] = { {10,0,0,0,0,0,0,0,0,0},
{0,20,0,0,0,0,0,0,0,0},
{0,0,30,0,0,0,0,0,0,0},
{0,0,0,40,0,0,0,0,0,0},
{0,0,0,0,50,0,0,0,0,0},
{0,0,0,0,0,60,0,0,0,0},
{0,0,0,0,0,0,70,0,0,0},
{0,0,0,0,0,0,0,80,0,0},
{0,0,0,0,0,0,0,0,90,0},
{0,0,0,0,0,0,0,0,0,100},
    };

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            SM.set(i, j, a[i][j]);

    SM.print();

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            SM.set(i, j, b[i][j]);

    SM.print();

}
