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
    void Inorder(CBinNode* p);
public:
    CBinNode* m_root = nullptr;
    bool Insert(int x);
    bool Remove(int x);
    void print();
    void distanceK(int k, CBinNode* target, vector<int>& vc);
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

bool VCchek(vector<int> visited, int x) {
    for (int i = 0; i < visited.size(); i++) {
        if (x == visited[i]) {
            return true;
        }
    }
    return false;
}

void CBinTree::distanceK(int k, CBinNode* target, vector<int>& vc) {
    if (m_root == nullptr) {
        return;
    }
    int moved = 0;
    vector<int> visited;
    queue<CBinNode*> rec;
    rec.push(target);
    visited.push_back(target->value);
    while (!rec.empty() && k >= moved) {
        int n = rec.size();
        for (int i = 0; i < n; i++) {
            CBinNode* p = rec.front();
            rec.pop();

            if (moved == k) {
                vc.push_back(p->value);
            }

            CBinNode* father = m_root;
            for (; father != nullptr && father != p && father->nodes[0] != p && father->nodes[1] != p; father = father->nodes[father->value < p->value]);

            if (father != nullptr && !VCchek(visited, father->value)) {
                rec.push(father);
                visited.push_back(father->value);
            }

            if (p->nodes[0] != nullptr && !VCchek(visited, p->nodes[0]->value)) {
                rec.push(p->nodes[0]);
                visited.push_back(p->nodes[0]->value);
            }

            if (p->nodes[1] != nullptr && !VCchek(visited, p->nodes[1]->value)) {
                rec.push(p->nodes[1]);
                visited.push_back(p->nodes[1]->value);
            }

        }
        moved++;
    }
}

int main() {
    CBinTree t;
    t.Insert(50);
    t.Insert(30);
    t.Insert(80);
    t.Insert(20);
    t.Insert(40);
    t.Insert(70);
    t.Insert(100);
    t.Insert(35);
    t.Insert(45);
    t.print();
    vector<int> vc;
    t.distanceK(2, t.m_root->nodes[0], vc);
    for (int i = 0; i < vc.size(); i++) {
        cout << vc[i] << " ";
    }
    cout << endl;
}
