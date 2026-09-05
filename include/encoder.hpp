#pragma once

#include <queue>
#include <cstring>
#include <random>

#include "graph.hpp"

class Encoder {
    private:
    std::fstream in_file, out_file;
    Node* datatree;

    std::map<char, int> char_freq;
    std::map<char, std::string> code_db;
    std::string code;

    public:
    Encoder(std::string ifile, std::string ofile);
    // Helper functions to create the code
    void create_graph();
    void construct_code(Node* nd);
    std::map<char, std::string> return_db() const;

    // Various encoding functions
    void encode_into_file();
    void reset_files();

    // Random key generator
    int generate(int bits);

    ~Encoder();
};