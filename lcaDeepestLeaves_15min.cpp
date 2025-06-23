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
    void inorder(CBinNode* p, int depth, pair<CBinNode*, int>& leaf1, pair<CBinNode*, int>& leaf2);
public:
    CBinNode* m_root = nullptr;
    bool Insert(int x);
    bool Remove(int x);
    void print();
    int lcaDeepestLeaves();
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

void CBinTree::inorder(CBinNode* p, int depth, pair<CBinNode*, int>& leaf1, pair<CBinNode*, int>& leaf2) {
    if (!p) return;
    inorder(p->nodes[0], depth + 1, leaf1, leaf2);
    if (p->nodes[0] == nullptr && p->nodes[1] == nullptr) {
        if (depth > leaf1.second) {
            leaf1 = make_pair(p, depth);
        }
        else if (depth > leaf2.second) {
            leaf2 = make_pair(p, depth);
        }
    }
    inorder(p->nodes[1], depth + 1, leaf1, leaf2);
}


int CBinTree::lcaDeepestLeaves() {
    pair<CBinNode*, int> leaf1, leaf2;
    leaf1.second = -1;
    leaf2.second = -1;
    inorder(m_root, 0, leaf1, leaf2);
    CBinNode* p = m_root;
    CBinNode* q = m_root;
    int val;
    while (p == q) {
        val = p->value;
        p = p->nodes[p->value < leaf1.first->value];
        q = q->nodes[q->value < leaf2.first->value];
    }
    return val;

}


int main() {
    CBinTree t;
    t.Insert(50);
    t.Insert(30);
    t.Insert(80);
    t.Insert(10);
    t.Insert(40);
    t.Insert(70);
    t.Insert(90);
    t.Insert(35);
    t.Insert(45);

    t.print();
    cout << endl;
    cout << t.lcaDeepestLeaves() << endl;

}
