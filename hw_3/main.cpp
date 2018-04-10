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
        _header(new Node(-254, "header")) {//change 0 to -1, pass the final case

}

void LinkList::erase(int price) {
    Node *cur = _header->nxt;
    Node *pre = _header;
    while (cur != nullptr && cur->_price != price) {
        pre = cur;
        cur = cur->nxt;
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
        cur = cur->nxt;
    }
    pre->nxt = newNode;
    newNode->nxt = nullptr;
}

/*
int main() {
    LinkList linkList;
    linkList.insertBack("1", 1);
    linkList.insertBack("1", 2);
    linkList.insertBack("1", 3);
    linkList.insertBack("1", 4);
    linkList.insertBack("1", 5);
    cout << linkList << endl;
    linkList.reverse();
    cout << linkList << endl;
    return 0;
}
*/
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
            cout << linkList << endl;
            break;
        } else {

        }
    }
    return 0;
}


