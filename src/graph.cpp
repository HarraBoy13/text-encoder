#include "graph.hpp"

// Constructors
Node::Node() : value(0), character('\0'), child_1(nullptr), child_2(nullptr) {}
Node::Node(int val, char ch) : value(val), character(ch), child_1(nullptr), child_2(nullptr) {}

// Returns the children as a std::pair
std::pair<Node*, Node*> Node::children() const {
    return std::pair<Node*, Node*>({child_1, child_2});
}

// Returns whether the node has no children
bool Node::is_leaf() const {
    return child_1 == nullptr;
}

// Value (frequency) of the Node
int Node::get_val() const {
    return value;
}

// Changes the value of the node
void Node::set_val(int val) {
    value = val;
}

// Character the node represents
char Node::get_char() const {
    return character;
}

// Change the character in the node
void Node::set_char(char ch) {
    character = ch;
}

// Join two nodes as children to a parent node
Node* Node::join(Node* n2) {
    Node* n = new Node(value + n2->value, 'k');
    n->child_1 = this;
    n->child_2 = n2;
    return n;
}

// Destructor
Node::~Node() {
    if (child_1) delete child_1;
    if (child_2) delete child_2;
}

// Comparison helper for the std::priority_queue
bool compare::operator()(Node* n1, Node* n2) const {
    return n1->get_val() > n2->get_val();
}
