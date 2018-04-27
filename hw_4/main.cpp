#include <iostream>
#include <cstring>
#include <string>
#include <queue>
#include <fstream>

using namespace std;


struct Node {
    Node(int _num = 0) : num(_num) {
        memset(nxt, 0, sizeof(nxt));
    }

    int num;
    Node *nxt[4];
};

int matrix[103][103];
int vis[103][103];
int numOfCase;
int COLS, ROWS;
Node *root;
string travelWay;
int beginX, beginY;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
Node *curNode;
int curX, curY;
queue<int> queX;
queue<int> queY;
queue<Node *> queNode;
queue<Node *> quePrt;

void push(int x, int y, Node *ptr) {
    queX.push(x);
    queY.push(y);
    queNode.push(ptr);
}

void pop() {
    curX = queX.front();
    curY = queY.front();
    curNode = queNode.front();
    queX.pop();
    queY.pop();
    queNode.pop();
}

void travelPost(Node *father) {
    if (father == nullptr) {
        return;
    }
    for (const auto &item : father->nxt) {
        travelPost(item);
    }
    if (root == father) {
        cout << father->num;
    } else {
        cout << father->num << " ";
    }

}

void travelPre(Node *father) {
    if (father == nullptr) {
        return;
    }
    if (root == father) {
        cout << father->num;
    } else {
        cout << " " << father->num;
    }
    for (const auto &item : father->nxt) {
        travelPre(item);
    }
}

void travelLevel(Node *father) {
    quePrt.push(father);
    while (!quePrt.empty()) {
        curNode = quePrt.front();
        quePrt.pop();
        for (int i = 0; i < 4; i++) {
            if (curNode->nxt[i] != nullptr) {
                quePrt.push(curNode->nxt[i]);
            }
        }
        if (!quePrt.empty()) {
            cout << curNode->num << " ";
        } else {
            cout << curNode->num;
        }
    }
}

void prt() {
    if (travelWay == "Level-order-traversal") {//case 5 by this
        travelLevel(root);
    } else if (travelWay == "Pre-order-traversal") {
        travelPre(root);
    } else if (travelWay == "Post-order-traversal") {
        travelPost(root);
    }//no wrong
}

void clear() {
    while (!quePrt.empty()) {
        quePrt.pop();
    }
    while (!queX.empty()) {
        queX.pop();
    }
    while (!queY.empty()) {
        queY.pop();
    }
    while (!queNode.empty()) {
        quePrt.pop();
    }
}

int main() {
    cin >> numOfCase;
    for (int cntOfCase = 0; cntOfCase < numOfCase; cntOfCase++) {
        //reset
        clear();
        memset(matrix, 0, sizeof(matrix));
        memset(vis, 0, sizeof(vis));
        root = nullptr;
        //end reset
        cin >> COLS >> ROWS;
        cin >> beginY >> beginX;
        //read matrix
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS; col++) {
                if (matrix[row][col] < 0 || matrix[row][col] >= 10) {
                    throw (1);// todo
                }
                cin >> matrix[row][col];
            }
        }
        cin >> travelWay;
        //end read
        root = new Node(matrix[beginX][beginY]);//no wrong
        push(beginX, beginY, root);
        while (!queX.empty()) {
            pop();
            if (vis[curX][curY] == 1) {
                continue;
            }
            vis[curX][curY] = 1;
            //begin bfs
            for (int i = 0; i < 4; i++) {
                //check
                int nxtX = curX + dx[i];
                int nxtY = curY + dy[i];
                if (vis[nxtX][nxtY] == 1
                    || nxtX < 0 || nxtX >= ROWS
                    || nxtY < 0 || nxtY >= COLS) {
                    continue;
                }
                int value = matrix[nxtX][nxtY];
                if (value == 0) {
                    continue;//end check
                } else {
                    Node *nxtNode = new Node(value);
                    curNode->nxt[i] = nxtNode;
                    push(nxtX, nxtY, nxtNode);
                }
            }
            //end bfs
        }
        prt();
        cout << endl;
    }
    return 0;
}


























