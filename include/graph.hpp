#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <utility>
#include <bitset>
#include <map>

class Node {
    private:
    int value;
    char character;
    Node* child_1;
    Node* child_2;

    public:
    Node();
    Node(char ch);
    Node(int val, char ch);

    std::pair<Node*, Node*> children() const;
    bool is_leaf() const;
    int get_val() const;
    void set_val(int val);
    char get_char() const;
    void set_char(char ch);
    Node* join(Node* n2);

    void encode_graph(std::string& sequence);
    
    ~Node();
};

struct compare {
    bool operator()(Node* n1, Node* n2) const;
};