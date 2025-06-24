#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
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
    void inorder(CBinNode** p);
public:
    CBinNode* m_root = nullptr;
    bool Insert(int x);
    bool Remove(int x);
    void print();
    void deleteallleafs();
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

void CBinTree::inorder(CBinNode** p) {
    if (*p == nullptr) return;
    inorder(&((*p)->nodes[0]));
    if ((*p)->nodes[0] == nullptr && ((*p)->nodes[1]) == nullptr) {
        CBinNode* temp = *p;
        *p = nullptr;
        delete temp;
        return;
    }
    inorder(&((*p)->nodes[1]));

}

void CBinTree::deleteallleafs() {
    if (m_root == nullptr) return;
    inorder(&m_root);
}

int main() {
    CBinTree t;
    t.Insert(20);
    t.Insert(8);
    t.Insert(22);
    t.Insert(4);
    t.Insert(12);
    t.Insert(10);
    t.Insert(14);
    t.print();
    t.deleteallleafs();
    cout << endl;
    t.print();

}
