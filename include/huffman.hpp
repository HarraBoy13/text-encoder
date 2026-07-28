#pragma once

#include <fstream>
#include <queue>
#include <cstring>
#include <iostream>

#include "graph.hpp"

class Encoder {
    private:
    std::map<char, int> char_freq;
    std::map<char, std::string> code_db;
    std::string code;

    public:
    // Helper functions to create the code
    Node* create_graph(std::fstream& file);
    void construct_code(Node* nd);
    std::map<char, std::string> return_db() const;

    // Various encoding functions
    void encode_into_file(std::fstream& in_file, std::fstream& out_file);
    void encode_as_01(std::fstream& in_file, std::fstream& out_file);
};