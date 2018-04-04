/*
 * 什么是合法的计算式，一个合法的计算式括号必须对称，
 * 加减乘除左边必须是右括号或者数字，
 * 加减乘除右边只能是左括号或者数字
 * 数字左右必须是加减乘除或者括号（左边是右括号，右边是左括号）
 * 左括号左边必须是加减乘除，右括号右边必然是加减乘除
 * 左括号右边必须是数字或者左括号，左
 *
 *
 * 首先新建一个棋盘来保存所有的数据
 * 定义一个函数来输出他，完成一个任务
 *
 * 对于合法的infix字符串，声明一个class，有函数check(char) 用于检测某个字符可不可以加在后面
 * push_back(char) 更新infix字符串， pop()去去除字符串最后一个字符，
 * class 中包含一个vector用于存储已经确认合法的字符串
 * 一个vector用于储存数字
 * 一个stack用于储存符号
 * 一个vector 用于储存postfix字符串？
 *
 * */


#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <fstream>
#include <cstring>

using namespace std;

class FixStr {
public:
    FixStr() : infixStr(), cntRight(0), cntLeft(0), curChar(' ') {

    }

    bool isEmpty();

    void push_back(char nextChar);

    void pop();

    bool check(char nextChar);

    void prt();

    vector<char> inFix2PostFix();


private:
    vector<char> infixStr;
    int cntLeft;
    int cntRight;
    char curChar;

    bool isNum(char);

    bool isSym(char);

    bool isLess(char lChar, char rChar);
};

bool FixStr::isNum(char num) {
    return num >= '0' && num <= '9';
}

bool FixStr::isSym(char sym) {
    return sym == '+' || sym == '-' || sym == '*' || sym == '/';
}

bool FixStr::check(char nextChar) {
    //cntLeft是左括号的数量，cntRight是右括号的数量
    if (nextChar == ')' && cntLeft <= cntRight) {
        return false;
    }
    switch (curChar) {
        case ' ':
            return true;
        case '+':
        case '-':
        case '*':
        case '/':
            return isNum(nextChar) || nextChar == '(';
        case '(':
            return isNum(nextChar) || nextChar == '(';
        case ')':
            return isSym(nextChar) || nextChar == ')';
        default:// is number
            return isNum(nextChar) || isSym(nextChar) || nextChar == ')';
    }
}

void FixStr::push_back(char nextChar) {
    if (nextChar == '(') {
        cntLeft++;
    } else if (nextChar == ')') {
        cntRight++;
    }
    curChar = nextChar;
    infixStr.push_back(nextChar);
}

void FixStr::pop() {
    if (curChar == '(') {
        cntLeft--;
    } else if (curChar == ')') {
        cntRight--;
    }
    infixStr.pop_back();
    curChar = *(infixStr.end() - 1);
}


void FixStr::prt() {
    for (auto &item:infixStr) {
        cout << item << " ";
    }
    cout << endl;
}

bool FixStr::isEmpty() {
    return infixStr.empty();
}

vector<char> FixStr::inFix2PostFix() {
    vector<char> output;
    stack<char> symStack;
    for (auto item:infixStr) {
        if (isNum(item)) {
            output.push_back(item);
        } else if (isSym(item)) {
            while (!(symStack.empty() || isLess(symStack.top(), item))) {
                output.push_back(symStack.top());
                symStack.pop();
            }
            symStack.push(item);
        } else {
            if (item == ')') {
                while (!symStack.empty()) {
                    if (symStack.top() != '(') {
                        output.push_back(symStack.top());
                        symStack.pop();
                    } else {
                        symStack.pop();
                        break;
                    }
                }
            } else if (item == '(') {
                symStack.push(item);
            }
        }
    }
    while (!symStack.empty()) {
        if (symStack.top() != '(') {
            output.push_back(symStack.top());
        }
        symStack.pop();
    }

    for (auto &item:output) {
        cout << item << " ";
    }
    cout << endl;
    return output;
}

bool FixStr::isLess(char lChar, char rChar) {
    return (lChar == '+' || lChar == '-') ||
           ((lChar == '*' || lChar == '/') && (rChar == '*' || rChar == '/')) ||
           lChar == '(';
}

char board[105][105];
int vis[105][105];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int numOfCase;
int M, N;
bool isFindIt;
FixStr myStr;

void dfs(int x, int y) {
    if (!isFindIt && vis[x][y] == 0 && myStr.check(board[x][y])) {
        myStr.push_back(board[x][y]);
        vis[x][y] = 1;
        if (x == M - 1 && y == N - 1) {
            isFindIt = true;
            cout << "Yes" << endl;
            myStr.prt();
            myStr.inFix2PostFix();
            return;
        }
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; j++) {
                dfs(x + dx[i], y + dy[i]);
            }
        }
        vis[x][y] = 0;
        myStr.pop();
    }
}

int main() {
    fstream is("data.dat");
    is >> numOfCase;
    cout << numOfCase << endl;
    for (int cntCase = 0; cntCase < numOfCase; cntCase++) {
        is >> M >> N;
        cout << M << "\n" << N << endl;
        memset(board, 0, sizeof(board));
        memset(vis, 0, sizeof(vis));
        isFindIt = false;
        if (!myStr.isEmpty()) {
            myStr.pop();
        }
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                is >> board[i][j];
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        dfs(0, 0);
    }
    return 0;
}
