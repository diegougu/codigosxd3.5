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
    void inorder(CBinNode* p, unordered_set<int>& changes);
public:
    CBinNode* m_root = nullptr;
    bool Insert(int x);
    bool Remove(int x);
    void print();
    void convertgreatertree();
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

void CBinTree::inorder(CBinNode* p, unordered_set<int>& changes) {
    if (!p) return;
    inorder(p->nodes[0], changes);
    changes.insert(p->value);
    inorder(p->nodes[1], changes);

}

void CBinTree::convertgreatertree() {
    if (m_root == nullptr) return;
    queue<CBinNode*> rec;
    rec.push(m_root);
    unordered_set<int> changes;
    inorder(m_root, changes);
    while (!rec.empty()) {
        CBinNode* p = rec.front();
        rec.pop();
        int greatersum = 0;
        for (auto it = changes.begin(); it != changes.end(); it++) {
            if (*it > p->value) {
                greatersum += *it;
            }
        }
        p->value = greatersum;

        if (p->nodes[0] != nullptr) {
            rec.push(p->nodes[0]);
        }

        if (p->nodes[1] != nullptr) {
            rec.push(p->nodes[1]);
        }
    }
}

int main() {
    CBinTree t;
    t.Insert(11);
    t.Insert(2);
    t.Insert(29);
    t.Insert(1);
    t.Insert(7);
    t.Insert(15);
    t.Insert(40);
    t.Insert(35);
    t.print();
    t.convertgreatertree();
    cout << endl;
    t.print();

}
