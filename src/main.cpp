#include "encoder.hpp"
#include "graph.hpp"

int main(int argc, char* argv[]) {
    std::fstream in_file("file\\in_file.txt", std::ios::in);
    if (!in_file) {
        std::cerr << "Error 1 - Input file connection issues." << std::endl;
        return -1;
    }
    
    Encoder encoder;
    std::fstream out_file("file\\out_file.bin", std::ios::out | std::ios::binary);

    Node* root = encoder.create_graph(in_file);
    encoder.construct_code(root);
    std::map<char, std::string> code_db = encoder.return_db();

    // Debugging snippet for checking working of the creation of codes
    
    std::cout << "{";
    for(auto& [ch, code]: code_db) {
        std::cout << "{";
        if (ch <= 32) std::cout << std::to_string(ch);
        else std::cout << ch;
        std::cout << ": " << code;
        std::cout << "}";
        if ((code_db.rbegin())->first != ch) std::cout << ", ";
        else std::cout << "}\n";
    }
    
    encoder.encode_into_file(in_file, out_file, root);

    return 0;
}