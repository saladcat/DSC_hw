#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

bool checkNumber(int pre, int nxt);

void dfs(int curX, int curY, int nxtX, int nxtY);

int ROWS, COLS;
int numOfCase;
int board[105][105];
int vis[105][105];
bool isReach;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};


int main() {
//    fstream is("data.dat");
    cin >> numOfCase;
    cout << numOfCase << endl;
    for (int cntOfCase = 0; cntOfCase < numOfCase; cntOfCase++) {
        isReach = false;
        memset(board, 0, sizeof(board));
        memset(vis, 0, sizeof(vis));
        cin >> COLS >> ROWS;
        cout << COLS << '\n' << ROWS << endl;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                cin >> board[i][j];
            }
        }
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (j == COLS - 1) {
                    cout << board[i][j];
                } else {
                    cout << board[i][j] << ' ';
                }
            }
            cout << endl;
        }
        vis[0][0] = 1;
        for (int i = 0; i < 4; i++) {
            dfs(0, 0, 0 + dx[i], 0 + dy[i]);
        }
        if (isReach) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}

bool checkNumber(int pre, int nxt) {//吃屎了，考试的时候这里写错了
    if (pre > nxt) {
        return true;
    }
    return nxt % pre != 0;
}

void dfs(int curX, int curY, int nxtX, int nxtY) {
    if (isReach || vis[nxtX][nxtY] == 1 || nxtX < 0 || nxtX >= ROWS || nxtY < 0 ||
        nxtY >= COLS) {
        return;
    }
    if (checkNumber(board[curX][curY], board[nxtX][nxtY])) {
        vis[nxtX][nxtY] = 1;
        if (nxtX == ROWS - 1 && nxtY == COLS - 1) {
            isReach = true;
            return;
        }
        for (int i = 0; i < 4; i++) {
            dfs(nxtX, nxtY, nxtX + dx[i], nxtY + dy[i]);
        }
        if (!isReach) {
            vis[nxtX][nxtX] = 0;
        }
    }
}

















