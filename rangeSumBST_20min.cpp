#include <iostream>
using namespace std;

struct CBinNode {
    int value;
    CBinNode* nodes[2];

    CBinNode(int v) {
        value = v;
        nodes[0] = nullptr;
        nodes[1] = nullptr;
    }
};

class CBinTree {
private:
    CBinNode* m_root = nullptr;
    bool m_b = 0;
    bool find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void Inorder(CBinNode* p);
public:
    int rangeSumBST(int low, int high);
    bool Insert(int x);
    bool Remove(int x);
    void print();
};

bool CBinTree::find(int x, CBinNode**& p) {
    for (p = &m_root; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x) {
    CBinNode** p;
    if (find(x, p)) {
        return false;
    }
    *p = new CBinNode(x);
    return true;
}

CBinNode** CBinTree::Rep(CBinNode** p) {
    m_b = !m_b;
    p = &((*p)->nodes[!m_b]);
    while ((*p)->nodes[m_b]) {
        p = &((*p)->nodes[m_b]);
    }
    return p;
}

bool CBinTree::Remove(int x) {
    CBinNode** p;
    if (!find(x, p)) {
        return false;
    }


    if ((*p)->nodes[0] && (*p)->nodes[1]) {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }

    CBinNode* temp = *p;
    *p = (*p)->nodes[(*p)->nodes[0] == 0];
    delete temp;
    return true;
}

void CBinTree::Inorder(CBinNode* p) {
    if (!p) return;
    Inorder(p->nodes[0]);
    cout << p->value << " ";
    Inorder(p->nodes[1]);
}


void CBinTree::print() {
    Inorder(m_root);
    cout << endl;
}

int CBinTree::rangeSumBST(int low, int high) {
    if (m_root == nullptr) {
        return 0;
    }
    int carry = 0;
    CBinNode** p = &m_root;
    CBinNode** q = &m_root;

    while (p || q) {

        if (p && q && *p == *q) {
            carry += (*p)->value;
        }
        else {
            if (p && (*p)->value >= low && (*p)->value <= high) {
                carry += (*p)->value;
            }

            if (q && (*q)->value >= low && (*q)->value <= high) {
                carry += (*q)->value;
            }
        }


        if (p && (*p)->value != low) {
            p = &((*p)->nodes[(*p)->value < low]);
        }
        else {
            p = nullptr;
        }

        if (q && (*q)->value != high) {
            q = &((*q)->nodes[(*q)->value < high]);
        }
        else {
            q = nullptr;
        }
    }
    return carry;

}

int main() {
    CBinTree t, t2, t3;
    t.Insert(10);
    t.Insert(5);
    t.Insert(15);
    t.Insert(3);
    t.Insert(7);
    t.Insert(18);
    t.print();
    cout << t.rangeSumBST(7, 15) << endl;


    t2.Insert(10);
    t2.Insert(5);
    t2.Insert(15);
    t2.Insert(3);
    t2.Insert(7);
    t2.Insert(18);
    t2.Insert(13);
    t2.Insert(1);
    t2.Insert(6);
    t2.print();
    cout << t2.rangeSumBST(6, 10) << endl;

}
