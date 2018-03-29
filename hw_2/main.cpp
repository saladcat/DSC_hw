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

using namespace std;

class fixStr {
public:
    fixStr() : infixStr(), cntRight(0), cntLeft(0), curChar(' ') {

    }

    void push_back(char nextChar);

    void pop();

    bool check(char nextChar);

    vector<char> inFix2PostFix();

private:
    vector<char> infixStr;
    int cntLeft;
    int cntRight;
    char curChar;

    bool isNum(char);

    bool isSym(char);
};

bool fixStr::isNum(char num) {
    return num >= '0' && num <= '9';
}

bool fixStr::isSym(char sym) {
    return sym == '+' || sym == '-' || sym == '*' || sym == '/';
}

bool fixStr::check(char nextChar) {
    if (nextChar == ')' && cntLeft <= cntRight) {
        return false;
    }
    switch (curChar) {
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

void fixStr::push_back(char nextChar) {
    if (check(nextChar)) {
        if (nextChar == '(') {
            cntLeft++;
        } else if (nextChar == ')') {
            cntRight++;
        }
        curChar = nextChar;
        infixStr.push_back(nextChar);
    } else {
        throw ("without check to push_back");
    }
}

void fixStr::pop() {
    if (curChar == '(') {
        cntLeft--;
    } else if (curChar == ')') {
        cntRight--;
    }
    infixStr.pop_back();
    curChar = *(infixStr.end() - 1);
}

vector<char> fixStr::inFix2PostFix() {
    return infixStr;
}

int main() {

    return 0;
}
/*

char board[105][105];

char table[20] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        '+', '-', '*', '/', '(', ')'
};
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int numOfCase;
int M, N;


int main() {
    cin >> numOfCase;
    for (int cntCase = 0; cntCase < numOfCase; cntCase++) {
        cin >> M >> N;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                cin >> board[i][j];
            }
        }
    }

}*/
