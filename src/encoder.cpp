#include "encoder.hpp"

/*
    Dev Notes:
    1. Line 84 for changing how much info the size of the graph should take (rn 4 bytes)
*/

Encoder::Encoder(std::string ifile, std::string ofile) : in_file(ifile, std::ios::in), out_file(ofile, std::ios::out | std::ios::binary) {
    if (!in_file) {
        std::cerr << "Error 1 - Input file does not exist." << std::endl;
        return;
    }

    if (!out_file) {
        std::cerr << "Error 2 - Output file access issues." << std::endl;
        return;
    }

    datatree = nullptr;
}

// Creates the Huffman Tree from a text file.
void Encoder::create_graph() {
    // Parsing the file into an std::string, and creating the frequency map of the characters
    std::string line;
    char_freq = {};
    while(std::getline(in_file, line)) {
        for(auto& ch: line) {
            char_freq[ch]++;
        }
        char_freq['\n']++;
    }
    char_freq['\n']--;

    reset_files();
    
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
    if(!pq.empty()) {
        datatree = pq.top();
        construct_code(datatree);
        return;
    }
    
    datatree = nullptr;
    std::cerr << "Empty file detected" << std::endl;
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
void Encoder::encode_into_file() {
    std::string bin_string, line;

    // Encoding the graph
    datatree->encode_graph(bin_string);
    while (bin_string.size() % 8) bin_string.push_back('0');
    
    std::string sz = std::bitset<32>(bin_string.size()/8).to_string();
    bin_string = sz + bin_string;

    while(std::getline(in_file, line))for(auto& ch: line) bin_string.append(code_db[ch]);

    while (bin_string.size() % 8) bin_string.push_back('0');

    int n = bin_string.size();

    for(int i = 0; i < n/8; i++) {
        unsigned char ch = 0;
        for(int j = 0; j < 8; j++) {
            ch = 2 * ch + bin_string[i*8 + j] - '0';
        }
        out_file.put(ch);   
    }
    
    reset_files();
}

void Encoder::reset_files() {
    in_file.clear();
    in_file.seekg(0);
    out_file.clear();
    out_file.seekg(0);
}

// Generate a random key
int Encoder::generate(int bits) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distb(1 << (bits - 1), (1 << bits) - 1);

    return distb(gen);
}

Encoder::~Encoder() {
    in_file.close();
    out_file.close();
}