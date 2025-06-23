#include <iostream>
#include <queue>
#include <vector>

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
    bool m_b = 0;
    bool find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void inorder(CBinNode* p, int low, int high);
public:
    CBinNode* m_root = nullptr;
    bool Insert(int x);
    bool Remove(int x);
    void print();
    void trim(int low, int high);
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



void CBinTree::print() {
    queue<CBinNode*> rec;
    rec.push(m_root);
    while (!rec.empty()) {
        int n = rec.size();
        for (int i = 0; i < n; i++) {
            CBinNode* p = rec.front();
            rec.pop();

            cout << p->value << " ";
            if (p->nodes[0] != nullptr) {
                rec.push(p->nodes[0]);
            }

            if (p->nodes[1] != nullptr) {
                rec.push(p->nodes[1]);
            }
        }
        cout << endl;
    }

}


void CBinTree::inorder(CBinNode* p, int low, int high) {
    if (!p) return;
    inorder(p->nodes[0], low, high);
    while (p != nullptr && (p->value < low || p->value > high)) {
        CBinNode** p1;
        if (!find(p->value, p1)) {
            return;
        }
        if ((*p1)->nodes[0] != nullptr && (*p1)->nodes[1] != nullptr) {
            CBinNode** q = Rep(p1);
            (*p1)->value = (*q)->value;
            p1 = q;
        }
        CBinNode* temp = *p1;
        *p1 = (*p1)->nodes[(*p1)->nodes[0] == 0];
        p = *p1;
        delete temp;
    }
    if (p == nullptr) return;
    inorder(p->nodes[1], low, high);
}

void CBinTree::trim(int low, int high) {
    if (m_root == nullptr) return;
    inorder(m_root, low, high);
}

int main() {
    CBinTree t;
    t.Insert(50);
    t.Insert(30);
    t.Insert(40);
    t.Insert(20);
    t.Insert(10);
    t.Insert(5);
    t.Insert(12);
    t.Insert(70);
    t.Insert(64);
    t.Insert(100);
    t.Insert(150);
    t.Insert(250);
    t.print();
    t.trim(40, 100);
    cout << endl;
    t.print();
}
