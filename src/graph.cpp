#include "graph.hpp"

Node::Node() : value(0), character('\0'), child_1(nullptr), child_2(nullptr) {}

Node::Node(int val, char ch) : value(val), character(ch), child_1(nullptr), child_2(nullptr) {}

std::pair<Node*, Node*> Node::children() const {
    return std::pair<Node*, Node*>({child_1, child_2});
}

bool Node::is_leaf() const {
    return child_1 == nullptr;
}

int Node::get_val() const {
    return value;
}

void Node::set_val(int val) {
    value = val;
}

char Node::get_char() const {
    return character;
}

void Node::set_char(char ch) {
    character = ch;
}

Node* Node::join(Node* n2) {
    Node* n = new Node(value + n2->value, 'k');
    n->child_1 = this;
    n->child_2 = n2;
    return n;
}

Node::~Node() {
    if (child_1) delete child_1;
    if (child_2) delete child_2;
}

bool compare::operator()(Node* n1, Node* n2) const {
    return n1->get_val() > n2->get_val();
}
