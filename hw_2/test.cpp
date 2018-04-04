//
// Created by zhu on 2018/4/2.
//
//
// Created by zhu on 2018/4/2.
//

#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <fstream>


using namespace std;

bool isNumber(char word) {
    return word >= '0' && word <= '9';
}

bool isAddSub(char word) {
    return word == '-' || word == '+';
}

bool isMulDiv(char word) {
    return word == '/' || word == '*';
}

bool isAcc(char word) {
    return isAddSub(word) || isMulDiv(word);
}

void dfs(int curX, int curY, int nxtX, int nxtY);

int prec(char word);

bool checkWord(char preWord, char nextWord);

string infix2postfix(vector<char> infixVector);

vector<vector<char> > numberGen(vector<char> input);

vector<char> infixString;
int cntLeft;
int cntRight;
bool isReach;
int ROWS, COLS;
char board[105][105];
int vis[105][105];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int numOfCase;

int main() {
    fstream inputStream("data.dat");
    inputStream >> numOfCase;
    cout << numOfCase << endl;
    for (int cntCase = 0; cntCase < numOfCase; cntCase++) {
        memset(vis, 0, sizeof(vis));
        memset(board, 0, sizeof(board));
        cntLeft = 0;
        cntRight = 0;
        isReach = false;
        while (!infixString.empty()) {
            infixString.pop_back();
        }
        inputStream >> COLS >> ROWS;
        cout << COLS << '\n' << ROWS << endl;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                inputStream >> board[i][j];
                cout << board[i][j] << ' ';
            }
            cout << endl;
        }
        dfs(0, 0, 0, 0);
        if (isReach) {
            auto chec = numberGen(infixString);
            for (const auto &item:chec) {
                for (const auto &item1:item) {
                    cout << item1;
                }
                cout << ' ';//可能最后不需要输出空 todo
            }
            cout << endl;
        }
    }
    return 0;
}

vector<vector<char> > numberGen(vector<char> input) {
    vector<vector<char>> res;
    int length = input.size();
    vector<char> tem;
    char curChar = input[0];
    tem.push_back(curChar);
    char lastChar = curChar;
    for (int index = 1; index < length; index++) {
        curChar = input[index];
        if (isNumber(lastChar)) {//todo simplify
            if (isNumber(curChar)) {
            } else {
                res.push_back(tem);
                tem.clear();
            }
        } else {
            res.push_back(tem);
            tem.clear();
        }
        tem.push_back(curChar);

        lastChar = curChar;
    }
    res.push_back(tem);
    return res;
}

void dfs(int curX, int curY, int nxtX, int nxtY) {
    if (isReach || nxtX < 0 || nxtX >= ROWS || nxtY < 0 || nxtY >= COLS
        || (vis[nxtX][nxtY] == 1)) {
        return;
    }
    if (checkWord(board[curX][curY], board[nxtX][nxtY])) {
        cntLeft += board[nxtX][nxtY] == '(' ? 1 : 0;
        cntRight += board[nxtX][nxtY] == ')' ? 1 : 0;
        infixString.push_back(board[nxtX][nxtY]);
        vis[nxtX][nxtY] = 1;
        if (nxtX == ROWS - 1 && nxtY == COLS - 1 && cntLeft == cntRight) {
            isReach = true;
            return;
        }
        for (int i = 0; i < 4; i++) {
            dfs(nxtX, nxtY, nxtX + dx[i], nxtY + dy[i]);
        }
        if (!isReach) {
            infixString.pop_back();
            vis[nxtX][nxtY] = 0;
            cntLeft -= board[nxtX][nxtY] == '(' ? 1 : 0;
            cntRight -= board[nxtX][nxtY] == ')' ? 1 : 0;
        }
    }
}




bool checkWord(char preWord, char nextWord) {
    if (isNumber(preWord)) {
        return isNumber(nextWord) || isAcc(nextWord) ||
               nextWord == ')';
    }
    if (isAcc(preWord)) {
        return isNumber(nextWord) || nextWord == '(';
    }
    if (cntLeft < cntRight) {//检测括号
        return false;
    }
    if (preWord == '(') {
        return isNumber(nextWord) || nextWord == '(';
    }
    if (preWord == ')') {
        return isAcc(nextWord) || nextWord == ')';
    }
    return false;
}

int prec(char word) {
    if (isMulDiv(word)) {
        return 2;
    } else if (isAddSub(word)) {
        return 1;
    } else {
        return 0;
    }
}























