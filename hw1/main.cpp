#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <algorithm>

using namespace std;

bool isPalindrome(string str, int reduceCount);

bool isPal(string str);

int main() {
//    fstream is("data.dat");
    int n;
    cin >> n;
    cin.get();
    string str;
    while (getline(cin, str)) {
        str.erase(str.length());
        if (isPalindrome(str, n)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}

bool isPal(string str) {
    if (str == string("") || str.length() == 1) {
        return true;
    }
    if (str[0] != str[str.length() - 1]) {
        return false;
    } else {
        return isPal(str.substr(1, str.length() - 2));
    }


}

bool isPalindrome(string str, int reduceCount) {
    bool flag = false;
    if (isPal(str)) {
        flag = true;
    } else if (reduceCount != 0) {
        for (int i = 0; i < str.length(); i++) {
            string eraseString = str;
            eraseString.erase(static_cast<unsigned int>(i), 1);
            flag = isPalindrome(eraseString, reduceCount - 1);
            if (flag) {
                break;
            }
        }
    } else {
        flag = false;
    }
    return flag;
}
