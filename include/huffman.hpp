#pragma once
#include <fstream>
#include <queue>

#include "graph.hpp"

class HEFile {
    private:
    std::map<char, int> char_freq;
    std::map<char, std::string> code_db;
    std::string code;
    int size;

    public:
    Node* create_graph(std::ifstream& file);
    void construct_code(Node* nd);
    std::map<char, std::string> return_db() const;
    int file_size() const;
    int comp_size() const;
};