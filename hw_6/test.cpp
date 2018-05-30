//
// Created by zhu on 2018/5/30.
//

#include <sstream>
#include <string>
#include <iostream>

using namespace std;

int main() {
    string A("ss11");
    stringstream ss;
    ss << A;
    string tem;
    int tem2;
    ss >> tem;
    cout << tem << endl;
    ss >> tem2;
    cout << tem2 << endl;
    return 0;
}