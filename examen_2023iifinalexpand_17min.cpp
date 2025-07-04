#include <iostream>
#include <thread>
#include <queue>
using namespace std;

int m[10][10] =
{
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,1,0,0,0,0,},
    {0,2,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,2,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
};

void printm()
{
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            if (m[j][i] == 0)
                std::cout << "  ";
            else
                std::cout << m[j][i] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "---------------------------\n";
}

void expand(int x, int y) {
    queue<pair<int, int>> rec;
    rec.push(make_pair(x, y));
    while (!rec.empty()) {
        pair<int, int> p = rec.front();
        rec.pop();

        if (p.first - 1 >= 0 && m[p.first - 1][p.second] == 0) {
            m[p.first - 1][p.second] = m[p.first][p.second] + 1;
            rec.push(make_pair(p.first - 1, p.second));
        }

        if (p.first + 1 < 10 && m[p.first + 1][p.second] == 0) {
            m[p.first + 1][p.second] = m[p.first][p.second] + 1;
            rec.push(make_pair(p.first + 1, p.second));
        }

        if (p.second - 1 >= 0 && m[p.first][p.second - 1] == 0) {
            m[p.first][p.second - 1] = m[p.first][p.second] + 1;
            rec.push(make_pair(p.first, p.second - 1));
        }

        if (p.second + 1 < 10 && m[p.first][p.second + 1] == 0) {
            m[p.first][p.second + 1] = m[p.first][p.second] + 1;
            rec.push(make_pair(p.first, p.second + 1));
        }
    }
}


void levels(){
    thread t1(expand, 1, 5);
    thread t2(expand, 2, 1);
    thread t3(expand, 3, 7);
    thread t4(expand, 7, 4);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    

}

int main()
{
    printm();
    levels();
    printm();
}
