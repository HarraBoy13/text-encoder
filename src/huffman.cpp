#include "huffman.hpp"
#include <iostream>

// Creates the Huffman Tree from a text file.
Node* Encoder::create_graph(std::fstream& file) {
    // Parsing the file into an std::string, and creating the frequency map of the characters
    std::string line;
    char_freq = {};
    while(std::getline(file, line)) {
        for(auto& ch: line) {
            char_freq[ch]++;
        }
        char_freq['\n']++;
    }
    char_freq['\n']--;

    file.clear();
    file.seekg(0);
    
    // Creating the queue for the algorithm
    std::priority_queue<Node*, std::vector<Node*>, compare> pq;

    for(const auto& pair: char_freq) {
        Node* nd = new Node(pair.second, pair.first);
        pq.push(nd);
    }

    // The main algorithm - creating the binary tree
    while(pq.size() > 1) {
        Node* n1 = pq.top();
        pq.pop();
        Node* n2 = pq.top();
        pq.pop();
        Node* nd = n1->join(n2);
        pq.push(nd);
    }

    // Returning the tree
    if(!pq.empty()) return pq.top();
    return nullptr;
}

// Constructs the code for each letter using a similar algorithm to DFS
void Encoder::construct_code(Node* nd) {
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

// Gives the database of codes
std::map<char, std::string> Encoder::return_db() const {
    return code_db;
}

// Encodes into the file
void Encoder::encode_into_file(std::fstream& in_file, std::fstream& out_file) {
    std::string bin_string, line;
    while(std::getline(in_file, line)) {
        for(auto& ch: line) bin_string.append(code_db[ch]);
    }

    while (bin_string.size() % 8) bin_string.push_back('0');

    int n = bin_string.size();
    for(int i = 0; i < n/8; i++) {
        unsigned char ch = 0;
        for(int j = 0; j < 8; j++) {
            ch = 2 * ch + bin_string[i*8 + j] - '0';
        }
        out_file.put(ch);        
    }

    in_file.clear();
    in_file.seekg(0);
    out_file.clear();
    out_file.seekg(0);
}

// Encodes as 0s and 1s into a plain text file (bloats a lot of space)
void Encoder::encode_as_01(std::fstream& in_file, std::fstream& out_file) {
    std::string line;
    while(std::getline(in_file, line)) {
        for(auto& ch: line) out_file << code_db[ch];
    }

    in_file.clear();
    in_file.seekg(0);
    out_file.clear();
    out_file.seekg(0);
}
