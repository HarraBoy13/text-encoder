#include "encoder.hpp"
#include "decoder.hpp"
#include "graph.hpp"

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Invalid call, too few arguments." << std::endl;
        return -1;
    }

    if (argc > 4) {
        std::cerr << "Invalid call, too many arguments." << std::endl;
        return -1;
    }

    int mode = std::stoi(argv[1]);
    std::string in_file_path = argv[2];
    std::string out_file_path = argv[3];
    
    if (mode == 0) {        
        Encoder encoder(in_file_path, out_file_path);
        encoder.create_graph();
        encoder.encode_into_file();

        std::cout << "File encoded in path successfully" << std::endl;
    }
    else if (mode == 1) {
        std::fstream in_file(in_file_path, std::ios::in | std::ios::binary);
        if (!in_file) {
            std::cerr << "Error 1 - Input file does not exist." << std::endl;
            return -1;
        }
        
        std::fstream out_file(out_file_path, std::ios::out);

        if (!out_file) {
            std::cerr << "Error 2 - Output file access issues." << std::endl;
            return -1;
        }

        Decoder decoder;

        in_file.close();
        out_file.close();
    }
    else {
        std::cerr << "Invalid call, invalid mode." << std::endl;
        return -1;
    }
    return 0;
}