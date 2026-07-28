#include "huffman.hpp"
#include "graph.hpp"
#include <iostream>

int main() {
    std::ifstream file("files/file.txt");

    HEFile codes;
    Node* root = codes.create_graph(file);
    codes.construct_code(root);

    std::map<char, std::string> code_db = codes.return_db();

    std::cout << "Codes: " << std::endl;
    for(const auto pair: code_db) {
        if (pair.first == 32) std::cout << "Space: ";
        if (pair.first > 32) std::cout << std::string(1, pair.first);
        std::cout << " - " << pair.second << std::endl;
    }

    std::cout << std::endl;
    int fs = codes.file_size(), cs = codes.comp_size();
    std::cout << "File size: " << fs << std::endl;
    std::cout << "Compressed size: " << cs << std::endl;
    std::cout << "Savings: " << fs - cs << std::endl;

    return 0;
}