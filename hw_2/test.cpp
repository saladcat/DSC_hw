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
#include <stack>


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

int prec(string word);

bool checkWord(char preWord, char nextWord);

vector<string> infix2postfix(vector<string> infixVector);

vector<string> numberGen(vector<char> input);

vector<char> infixVector;
int cntLeft;
int cntRight;
bool isReach;
int ROWS, COLS;
char board[105][105];
int vis[105][105];
int dx[4] = {1, 0, 0, -1};
int dy[4] = {0, 1, -1, 0};
int numOfCase;

int main() {
//    fstream inputStream("data.dat");
    cin >> numOfCase;
    cout << numOfCase << endl;
    for (int cntCase = 0; cntCase < numOfCase; cntCase++) {
        memset(vis, 0, sizeof(vis));
        memset(board, 0, sizeof(board));
        cntLeft = 0;
        cntRight = 0;
        isReach = false;
        while (!infixVector.empty()) {
            infixVector.pop_back();
        }
        cin >> COLS >> ROWS;
        cout << COLS << '\n' << ROWS << endl;
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                cin >> board[i][j];
                cout << board[i][j] << ' ';
            }
            cout << endl;
        }
        dfs(0, 0, 0, 0);
        if (isReach) {
            cout << "Yes" << endl;
            auto infixString = numberGen(infixVector);
            for (const auto &item:infixString) {
                for (const auto &item1:item) {
                    cout << item1;
                }
                cout << ' ';//可能最后不需要输出空 todo
            }
            cout << endl;
            auto postFixString = infix2postfix(infixString);
            for (const auto &item:postFixString) {
                for (const auto &item1:item) {
                    cout << item1;
                }
                cout << ' ';//可能最后不需要输出空 todo
            }
            cout << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}

vector<string> numberGen(vector<char> input) {
    vector<string> res;
    int length = input.size();
    string tem;
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
        infixVector.push_back(board[nxtX][nxtY]);
        vis[nxtX][nxtY] = 1;
        if (nxtX == ROWS - 1 && nxtY == COLS - 1 && cntLeft == cntRight) {
            isReach = true;
            return;
        }
        for (int i = 0; i < 4; i++) {
            dfs(nxtX, nxtY, nxtX + dx[i], nxtY + dy[i]);
        }
        if (!isReach) {
            infixVector.pop_back();
            vis[nxtX][nxtY] = 0;
            cntLeft -= board[nxtX][nxtY] == '(' ? 1 : 0;
            cntRight -= board[nxtX][nxtY] == ')' ? 1 : 0;
        }
    }
}


bool checkWord(char preWord, char nextWord) {
    if (cntLeft < cntRight) {//检测括号
        return false;
    }
    if (nextWord == ')' && cntLeft == cntRight) {
        return false;
    }
    if (isNumber(preWord)) {
        return isNumber(nextWord) || isAcc(nextWord) || nextWord == ')';
    }
    if (isAcc(preWord)) {
        return isNumber(nextWord) || nextWord == '(';
    }
    if (preWord == '(') {
        return isNumber(nextWord) || nextWord == '(';
    }
    if (preWord == ')') {
        return isAcc(nextWord) || nextWord == ')';
    }
    return false;
}

vector<string> infix2postfix(vector<string> infixVector) {
    vector<string> res;
    stack<string> signStack;
    for (const auto &word:infixVector) {
        if (isNumber(word[0])) {// if is number, then output
            res.push_back(word);
        } else if (word[0] == '(') {// if it's (, then push signStack
            signStack.push(word);
        } else if (word[0] ==
                   ')') {// if it's ),then pop_and_output until pop'(' which would be output
            string topWord = signStack.top();
            signStack.pop();
            while (topWord[0] != '(') {
                res.push_back(topWord);
                topWord = signStack.top();
                signStack.pop();
            }
        } else if (isAcc(word[0])) {
            //until stack is empty or stack_top's precedence is less than curWord's
            while (!(signStack.empty() ||
                     prec(signStack.top()) < prec(word))) {//take place <= by < and done
                string topWord = signStack.top();
                signStack.pop();
                res.push_back(topWord);
            }
            signStack.push(word);
        }
    }
    while (!signStack.empty()) {
        res.push_back(signStack.top());
        signStack.pop();
    }
    return res;
}

int prec(string word) {
    if (isMulDiv(word[0])) {
        return 2;
    } else if (isAddSub(word[0])) {
        return 1;
    } else {
        return 0;
    }
}























