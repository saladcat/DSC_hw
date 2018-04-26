#include <iostream>
#include <cstring>
#include <string>
#include <queue>

using namespace std;

struct Node {
    Node(int _num = 0) : num(_num) {
        memset(nxt, 0, sizeof(nxt));
    }

    int num;
    Node *nxt[4];
};

int matrix[103][103];
bool vis[103][103];
int numOfCase;
int COLS, ROWS;
Node *root;
string travelWay;
int beginX, beginY;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
Node *cur;

queue<int> queX;
queue<int> queY;
queue<int> queI;

int main() {
    cin >> numOfCase;
    for (int cntOfCase = 0; cntOfCase < numOfCase; cntOfCase++) {
        //reset
        memset(matrix, 0, sizeof(matrix));
        memset(vis, 0, sizeof(vis));
        root = nullptr;
        //end reset
        cin >> beginX >> beginY;
        //read matrix
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS; col++) {
                cin >> matrix[row][col];
            }
        }
        cin >> travelWay;
        //end read
        queX.push(beginX);
        queY.push(beginY);
        while (!queX.empty()) {
            int curX = queX.front();
            int curY = queY.front();
            queX.pop();
            queY.pop();
        }
    }
    return 0;
}


























