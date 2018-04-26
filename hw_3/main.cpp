#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct Node {
    Node(int price, string name) : _price(price), _name(name), nxt(nullptr) {
    }

    int _price;
    string _name;
    Node *nxt;
};

class LinkList {
public:
    LinkList();

    void erase(int price);

    void insertAfter(string gift, int price, int priceToInsertAfter);

    void insertBack(string gift, int price);

    void reverse();

    friend ostream &operator<<(ostream &os, const LinkList &linkList);

    void prt();

private:
    Node *_header;
};

void LinkList::reverse() {
    Node *cur = _header->nxt;
    Node *pre = nullptr;
    Node *nxt = nullptr;
    while (cur != nullptr) {
        nxt = cur->nxt;
        cur->nxt = pre;
        pre = cur;
        cur = nxt;
    }
    _header->nxt = pre;
}

LinkList::LinkList() :
        _header(new Node(-1, "header")) {//change 0 to -1, pass the final case

}

void LinkList::erase(int price) {
    Node *cur = _header->nxt;
    Node *pre = _header;
    while (cur != nullptr &&
           cur->_price != price) {//wtf problem describe that there are no duplicate price
        pre = cur;                                  //but in many cases, there exist duplicate price
        cur = cur->nxt;                             //we need to ignore when the price is duplicate
    }
    if (cur == nullptr) {
        return; //do nothing
    }
    pre->nxt = cur->nxt;
    delete cur;
}

ostream &operator<<(ostream &os, const LinkList &linkList) {
    Node *cur = linkList._header->nxt;
    if (cur == nullptr) {
        cout << "Empty";
        return os;
    }
    cout << "List" << endl;
    while (true) {
        os << '(' << cur->_name << "," << cur->_price << ')';
        cur = cur->nxt;
        if (cur != nullptr) {
            os << "->";
        } else {
            break;
        }
    }
    return os;
}

void LinkList::insertAfter(string gift, int price, int priceToInsertAfter) {
    Node *newNode = new Node(price, gift);
    Node *cur = _header->nxt;
    while (cur != nullptr) {
        if (cur->_price == price) {
            delete newNode;
            return;
        }
        cur = cur->nxt;
    }
    cur = _header->nxt;
    while (cur != nullptr && cur->_price != priceToInsertAfter) {
        cur = cur->nxt;
    }
    if (cur == nullptr) {
        delete newNode;
        return;//do nothing
    }
    Node *tem = cur->nxt;
    cur->nxt = newNode;
    newNode->nxt = tem;
}

void LinkList::insertBack(string gift, int price) {
    Node *newNode = new Node(price, gift);
    Node *cur = _header->nxt;
    Node *pre = _header;
    while (cur != nullptr) {
        pre = cur;
        if (cur->_price == price) {
            delete newNode;
            return;
        }
        cur = cur->nxt;
    }
    pre->nxt = newNode;
    newNode->nxt = nullptr;
}

void LinkList::prt() {
    Node *cur = _header->nxt;
    if (cur == nullptr) {
        cout << "Empty" << endl;
        return;
    }
    while (cur != nullptr) {
        cout << "List" << endl;
        while (true) {
            cout << '(' << cur->_name << "," << cur->_price << ')';
            cur = cur->nxt;
            if (cur != nullptr) {
                cout << "->";
            } else {
                cout << endl;
                return;
            }
        }

    }
}

int main() {
    LinkList linkList;
    string line;
    while (getline(cin, line)) {
        stringstream ss;
        ss << line;
        ss >> line;
        if (line == "InsertBack") {
            int price;
            string name;
            ss >> name >> price;
            linkList.insertBack(name, price);
        } else if (line == "InsertAfter") {
            int insertToAfterPrice;
            int price;
            string name;
            ss >> name >> price >> insertToAfterPrice;
            linkList.insertAfter(name, price, insertToAfterPrice);
        } else if (line == "Delete") {
            int price;
            ss >> price;
            linkList.erase(price);
        } else if (line == "Reverse") {
            linkList.reverse();
        } else if (line == "End") {
            linkList.prt();
            break;
        } else {

        }
    }
    return 0;
}


