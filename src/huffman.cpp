#include "huffman.hpp"
#include <iostream>

Node* HEFile::create_graph(std::ifstream& file) {
    if (!file.is_open()) {
        return nullptr;
    }

    std::string line;
    char_freq = {};
    while(std::getline(file, line)) {
        for(auto& ch: line) {
            char_freq[ch]++;
            size += 8;
        }
        char_freq['\n']++;
    }
    char_freq['\n']--;

    
    // Creating the queue for the algorithm
    std::priority_queue<Node*, std::vector<Node*>, compare> pq;

    for(const auto& pair: char_freq) {
        Node* nd = new Node(pair.second, pair.first);
        pq.push(nd);
    }

    // The main algorithm

    while(pq.size() > 1) {
        Node* n1 = pq.top();
        pq.pop();
        Node* n2 = pq.top();
        pq.pop();
        Node* nd = n1->join(n2);
        pq.push(nd);
    }

    if(!pq.empty()) return pq.top();
    return nullptr;
}

void HEFile::construct_code(Node* nd) {
    if (!nd) return;

    if (nd->is_leaf()) {
        code_db[nd->get_char()] = code.empty() ? "0" : code;
        return;
    }

    if (nd->children().first) {
        code.push_back('0');
        construct_code(nd->children().first);
        code.pop_back();
    }

    if (nd->children().second) {
        code.push_back('1');
        construct_code(nd->children().second);
        code.pop_back();
    }
}

std::map<char, std::string> HEFile::return_db() const {
    return code_db;
}

int HEFile::file_size() const {
    return size;
}

int HEFile::comp_size() const {
    int size_comp = 0;
    for(auto& p: char_freq) {
        size_comp += code_db.at(p.first).size() * p.second;
    }
    return size_comp;
}