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
    void inorder(CBinNode* p, int posiblenode1, int& node2, int target, bool& verify);
public:
    CBinNode* m_root = nullptr;
    bool Insert(int x);
    bool Remove(int x);
    void print();
    void findsumtarget(int target, int& node1, int& node2);
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

void CBinTree::inorder(CBinNode* p, int posiblenode1, int& node2, int target, bool& verify) {
    if (!p || verify == true) return;
    inorder(p->nodes[0], posiblenode1, node2, target, verify);
    if (p->value + posiblenode1 == target && verify == false) {
        node2 = p->value;
        verify = true;
        return;
    }
    inorder(p->nodes[1], posiblenode1, node2, target, verify);
}

void CBinTree::findsumtarget(int target, int& node1, int& node2) {
    if (m_root == nullptr) {
        return;
    }

    bool verify = false;
    queue<CBinNode*> rec;
    rec.push(m_root);
    while (!rec.empty()) {
        CBinNode* p = rec.front();
        rec.pop();
        inorder(m_root, p->value, node2, target, verify);
        
        if (verify == true) {
            node1 = p->value;
            return;
        }

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
    t.Insert(7);
    t.Insert(3);
    t.Insert(8);
    t.Insert(2);
    t.Insert(4);
    t.Insert(9);
    int node1 = -1;
    int node2 = -1;
    t.findsumtarget(12, node1, node2);
    cout << node1 << " ," << node2 << endl;
}
