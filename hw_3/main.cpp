#include <iostream>
#include <string>
#include <set>

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

    void insert(Node *newNode);

    void erase(int price);

    void reverse();

    friend ostream &operator<<(ostream &os, const LinkList &linkList);

private:
    Node *_header;
};

void LinkList::reverse() {
    Node *cur = _header;
    Node *pre = nullptr;
    Node *nxt = nullptr;
    while (cur->nxt != nullptr) {
        nxt = cur->nxt;
        cur->nxt = pre;
        pre = cur;
        cur = nxt;
    }
}

LinkList::LinkList() : _header(new Node(0, "header")) {

}

void LinkList::insert(Node *newNode) {
    Node *cur = _header;
    Node *pre = _header;
    while (cur != nullptr && newNode->_price > cur->_price) {
        pre = cur;
        cur = cur->nxt;
    }
    pre->nxt = newNode;
    newNode->nxt = cur;
}

void LinkList::erase(int price) {
    Node *cur = _header;
    Node *pre = _header;
    while (cur != nullptr && cur->_price != price) {
        pre = cur;
        cur = cur->nxt;
    }
    if (cur == nullptr) {
        throw ("there isn't have the price");
    }

    pre->nxt = cur->nxt;
    delete cur;
}

ostream &operator<<(ostream &os, const LinkList &linkList) {
    Node *cur = linkList._header->nxt;
    if (cur == nullptr) {
        return os;
    }
    while (cur->nxt != nullptr) {
        os << cur->_name << ":" << cur->_price << "->";
        cur = cur->nxt;
    }
    os << cur->_name << ":" << cur->_price << endl;
    return os;
}

int main() {
    LinkList mylinklist;
    mylinklist.insert(new Node(10, "myname"));
    mylinklist.insert(new Node(12, "my"));
    mylinklist.insert(new Node(11, "m"));
    cout << mylinklist << endl;
    return 0;

}


