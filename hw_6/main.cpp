#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <map>
#include <algorithm>
#include <stack>
#include <list>

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

void init(void);

list<string> getInfix(string input);

double caculatePostfix(list<string> input);

string getEntity(stringstream &sstream);

double string2num(string input);

list<string> infix2postfix(list<string> infixVector);

struct Node {
    string name;
    string formula;
    double price;

    bool operator<(const Node &right);

    void getPrice();

};

bool Node::operator<(const Node &right) {
    return this->price < right.price;
}

std::map<string, int> PRICE;
int numOfCase;
int numOfNode;
string temFormula;
Node data[2000];
int swapCnt = 0;


void Swap(Node *left, Node *right) {
    if (left == right) {
        return;
    }
    Node tem = *right;
    *right = *left;
    *left = tem;
    swapCnt++;
}

int partition(int left, int right) {
    double pivotValue = data[left].price;
    int lPos = left, rPos = right;
    do {
        do { lPos++; } while (lPos < right && data[lPos].price <= pivotValue);
        do { rPos--; } while (left < rPos && data[rPos].price >= pivotValue);
        if (lPos < rPos) { Swap(data + lPos, data + rPos); }
    } while (lPos < rPos);
    Swap(data + left, data + rPos);
    return rPos;
}

/*
procedure quicksort(a, left, right)
    if right > left
        select a pivot value a[pivotIndex]
        pivotNewIndex := partition(a, left, right, pivotIndex)
        quicksort(a, left, pivotNewIndex-1)
        quicksort(a, pivotNewIndex+1, right)

*/
void qSort(int begin, int end) {
    if (begin < end) {
        int pivot = partition(begin, end);
        qSort(begin, pivot);
        qSort(pivot + 1, end);
    }
}

void print() {
    for (int i = 0; i < numOfNode; i++) {
        printf("%-40s%-25s%10.2lf\n", data[i].name.c_str(), data[i].formula.c_str(), data[i].price);
    }
    printf("%d swaps during qsort\n", swapCnt);
}

int main() {
    init();
    cin >> numOfCase;
    cout << numOfCase << endl;
    for (int p = 0; p < numOfCase; p++) {
        cin >> numOfNode;
        cout << numOfNode << endl;
        swapCnt = 0;
        for (int i = 0; i < numOfNode; i++) {
            cin >> setw(40) >> data[i].name;
            cin >> setw(25) >> data[i].formula;
            cin >> data[i].price;
            if (data[i].price == 0) {
                data[i].getPrice();
            }
        }
        qSort(0, numOfNode);
        print();
    }
    return 0;
}

double caculatePostfix(list<string> input) {
    double res = 0;
    string cur;
    stack<double> number;
    while (!input.empty()) {
        cur = input.front();
        input.pop_front();
        if (isdigit(cur[0])) {
            number.push(atoi(cur.c_str()));
        } else if (cur == "*") {
            double tem1 = number.top();
            number.pop();
            double tem2 = number.top();
            number.pop();
            double tem3 = tem1 * tem2;
            number.push(tem3);
        } else if (cur == "+") {
            double tem1 = number.top();
            number.pop();
            double tem2 = number.top();
            number.pop();
            double tem3 = tem1 + tem2;
            number.push(tem3);
        }
    }
    return number.top();
}

list<string> getInfix(string input) {
    list<string> res;
    stringstream ss;
    ss << input;
    string element = getEntity(ss);
    while (!element.empty()) {
        if (isalpha(element[0])) {
            res.push_back(element);
            res.emplace_back("*");
            res.emplace_back("1");
        } else if (isdigit(element[0])) {
            res.emplace_back("*");
            res.push_back(element);
        } else if (element == "(" || element == "[") {
            res.emplace_back("(");
        } else if (element == ")" || element == "]") {
            res.emplace_back(")");
            res.emplace_back("*");
            res.emplace_back("1");
        } else {
            throw (1);
        }
        element = getEntity(ss);
    }
    auto index = res.begin();
    while (index != res.cend()) {
        auto next = index;
        next++;
        if (isdigit((*index)[0]) && next != res.cend() && (*next) != ")" &&
            !((*next) == "+" || (*next) == "*")) {
            res.insert(next, "+");
            index = res.begin();
        } else {
            index++;
        }
    }
    for (auto &item:res) {
        if (isalpha(item[0])) {
            item = to_string(PRICE[item]);
        }
    }
    return res;
}


double string2num(string input) {
    if (isalpha(input[0])) {
        return PRICE[input];
    } else if (isdigit(input[0])) {
        double sum = 0;
        for (const auto &item:input) {
            sum = sum * 10 + item - '0';
        }
        return sum;
    }
    throw (1);
    return 0;
}

string getEntity(stringstream &sstream) {
    auto nextChar = static_cast<char>(sstream.peek());
    string res;
    if (isdigit(nextChar)) {
        while (isdigit(nextChar)) {
            nextChar = static_cast<char>(sstream.get());
            res.push_back(nextChar);
            nextChar = static_cast<char>(sstream.peek());
        }
        return res;
    }
    if (isupper(nextChar)) {
        nextChar = static_cast<char>(sstream.get());
        res.push_back(nextChar);
        nextChar = static_cast<char>(sstream.peek());
        while (islower(nextChar)) {
            nextChar = static_cast<char>(sstream.get());
            res.push_back(nextChar);
            nextChar = static_cast<char>(sstream.peek());
        }
        return res;
    }
    if (nextChar == ')' || nextChar == ']') {
        nextChar = static_cast<char>(sstream.get());
        return string(")");
    }
    if (nextChar == '(' || nextChar == '[') {
        nextChar = static_cast<char>(sstream.get());
        return string("(");
    }
    return "";
}

void Node::getPrice() {
    if (price == 0) {
        auto infix = getInfix(this->formula);
        auto postfix = infix2postfix(infix);
        price = caculatePostfix(postfix);
    } else {
        return;
    }

}


void init(void) {
    PRICE[string("")] = 0;
    PRICE[string("H")] = 1;
    PRICE[string("He")] = 4;
    PRICE[string("Li")] = 7;
    PRICE[string("Be")] = 9;
    PRICE[string("B")] = 11;
    PRICE[string("C")] = 12;
    PRICE[string("N")] = 14;
    PRICE[string("O")] = 16;
    PRICE[string("F")] = 19;
    PRICE[string("Ne")] = 20;
    PRICE[string("Na")] = 23;
    PRICE[string("Mg")] = 24;
    PRICE[string("Al")] = 27;
    PRICE[string("Si")] = 28;
    PRICE[string("P")] = 31;
    PRICE[string("S")] = 32;
    PRICE[string("Cl")] = 35;
    PRICE[string("Ar")] = 40;
    PRICE[string("K")] = 39;
    PRICE[string("Ca")] = 40;
    PRICE[string("Sc")] = 45;
    PRICE[string("Ti")] = 48;
    PRICE[string("V")] = 51;
    PRICE[string("Cr")] = 52;
    PRICE[string("Mn")] = 55;
    PRICE[string("Fe")] = 56;
    PRICE[string("Co")] = 59;
    PRICE[string("Ni")] = 59;
    PRICE[string("Cu")] = 64;
    PRICE[string("Zn")] = 65;
    PRICE[string("Ga")] = 70;
    PRICE[string("Ge")] = 73;
    PRICE[string("As")] = 75;
    PRICE[string("Se")] = 79;
    PRICE[string("Br")] = 80;
    PRICE[string("Kr")] = 84;
    PRICE[string("Rb")] = 85;
    PRICE[string("Sr")] = 88;
    PRICE[string("Y")] = 89;
    PRICE[string("Zr")] = 91;
    PRICE[string("Nb")] = 93;
    PRICE[string("Mo")] = 96;
    PRICE[string("Tc")] = 97;
    PRICE[string("Ru")] = 101;
    PRICE[string("Rh")] = 103;
    PRICE[string("Pd")] = 106;
    PRICE[string("Ag")] = 108;
    PRICE[string("Cd")] = 112;
    PRICE[string("In")] = 115;
    PRICE[string("Sn")] = 119;
    PRICE[string("Sb")] = 122;
    PRICE[string("Te")] = 128;
    PRICE[string("I")] = 127;
    PRICE[string("Xe")] = 131;
    PRICE[string("Cs")] = 133;
    PRICE[string("Ba")] = 137;
    PRICE[string("La")] = 139;
    PRICE[string("Ce")] = 140;
    PRICE[string("Pr")] = 141;
    PRICE[string("Nd")] = 144;
    PRICE[string("Pm")] = 145;
    PRICE[string("Sm")] = 150;
    PRICE[string("Eu")] = 152;
    PRICE[string("Gd")] = 157;
    PRICE[string("Tb")] = 159;
    PRICE[string("Dy")] = 163;
    PRICE[string("Ho")] = 165;
    PRICE[string("Er")] = 167;
    PRICE[string("Tm")] = 169;
    PRICE[string("Yb")] = 173;
    PRICE[string("Lu")] = 175;
    PRICE[string("Hf")] = 178;
    PRICE[string("Ta")] = 181;
    PRICE[string("W")] = 184;
    PRICE[string("Re")] = 186;
    PRICE[string("Os")] = 190;
    PRICE[string("Ir")] = 192;
    PRICE[string("Pt")] = 195;
    PRICE[string("Au")] = 197;
    PRICE[string("Hg")] = 201;
    PRICE[string("Tl")] = 204;
    PRICE[string("Pb")] = 207;
    PRICE[string("Bi")] = 209;
    PRICE[string("Po")] = 209;
    PRICE[string("At")] = 210;
    PRICE[string("Rn")] = 222;
    PRICE[string("Fr")] = 223;
    PRICE[string("Ra")] = 226;
    PRICE[string("Ac")] = 227;
    PRICE[string("Th")] = 232;
    PRICE[string("Pa")] = 231;
    PRICE[string("U")] = 238;
    PRICE[string("Np")] = 237;
    PRICE[string("Pu")] = 244;
    PRICE[string("Am")] = 243;
    PRICE[string("Cm")] = 247;
    PRICE[string("Bk")] = 247;
    PRICE[string("Cf")] = 251;
    PRICE[string("Es")] = 252;
    PRICE[string("Fm")] = 257;
    PRICE[string("Md")] = 258;
    PRICE[string("No")] = 259;
    PRICE[string("Lr")] = 262;
    PRICE[string("Rf")] = 267;
    PRICE[string("Db")] = 270;
    PRICE[string("Sg")] = 269;
    PRICE[string("Bh")] = 270;
    PRICE[string("Hs")] = 270;
    PRICE[string("Mt")] = 278;
    PRICE[string("Ds")] = 281;
    PRICE[string("Rg")] = 281;
    PRICE[string("Cn")] = 285;
    PRICE[string("Nh")] = 286;
    PRICE[string("Fl")] = 289;
    PRICE[string("Mc")] = 289;
    PRICE[string("Lv")] = 293;
    PRICE[string("Ts")] = 293;
    PRICE[string("Og")] = 294;
}


int prec(string word);


list<string> infix2postfix(list<string> infixVector) {
    list<string> res;
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
