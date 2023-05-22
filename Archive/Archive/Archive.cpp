#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <string>

void compress(const std::string& input, std::string& output) {
    std::unordered_map<std::string, int> dictionary;
    for (int i = 0; i < 256; ++i) {
        dictionary[std::string(1, i)] = i;
    }

    std::string current_string;
    int next_code = 256;

    for (char c : input) {
        current_string += c;
        if (dictionary.find(current_string) == dictionary.end()) {
            dictionary[current_string] = next_code++;
            current_string.pop_back();
            output += std::to_string(dictionary[current_string]) + " ";
            current_string = c;
        }
    }

    if (!current_string.empty()) {
        output += std::to_string(dictionary[current_string]) + " ";
    }
}

void decompress(const std::string& input, std::string& output) {
    std::unordered_map<int, std::string> dictionary;
    for (int i = 0; i < 256; ++i) {
        dictionary[i] = std::string(1, i);
    }

    int next_code = 256;
    int code;
    std::istringstream input_stream(input);

    while (input_stream >> code) {
        std::string entry = dictionary[code];
        if (entry.empty()) {
            entry = dictionary[next_code - 1] + dictionary[next_code - 1][0];
        }

        output += entry;
        dictionary[next_code++] = dictionary[next_code - 1] + entry[0];
    }
}

//void decompress(const std::string& input, const std::string& path) {
//    std::unordered_map<int, std::string> dictionary;
//    for (int i = 0; i < 256; ++i) {
//        dictionary[i] = std::string(1, i);
//    }
//
//    int next_code = 256;
//    int code;
//    std::istringstream input_stream(input);
//
//    std::ofstream outputFile(path);
//    if (!outputFile.is_open()) {
//        std::cout << "Failed to open file" << std::endl;
//        exit(1);
//    }
//
//    while (input_stream >> code) {
//        std::string entry = dictionary[code];
//        if (entry.empty()) {
//            entry = dictionary[next_code - 1] + dictionary[next_code - 1][0];
//        }
//
////        std::cout << "sym " << entry;
//        outputFile << entry;
//        dictionary[next_code++] = dictionary[next_code - 1] + entry[0];
//    }
//
//    outputFile.close();
//}

void checkInput(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Usage:" << std::endl;
        std::cout << "FILE_INPUT {C or D} NAME_OUTPUT" << std::endl;
        exit(1);
    }
}

int main(int argc, char** argv) {

    checkInput(argc, argv);

    std::string inputCommand(argv[2]);
    
    if (inputCommand == "C") {
        std::cout << "Compressing... please wait" << std::endl;

        std::ifstream inputFile(argv[1]);
        if (!inputFile.is_open()) {
            std::cout << "Failed to open file" << std::endl;
            return 1;
        }
        std::string input;
        std::string str;
        while (std::getline(inputFile, str)) {
            input += str;
        }
        inputFile.close();

        //std::cout << "Input: " << input << std::endl;
        std::string compressed;

        compress(input, compressed);
        //std::cout << "Compressed: " << compressed << std::endl;

        std::string output = argv[3];
        output += ".myarch";
        std::ofstream outFile(output);
        if (!outFile.is_open()) {
            std::cout << "Failed to open file" << std::endl;
            return 1;
        }
        outFile << compressed;
        outFile.close();

        std::cout << "Done!" << std::endl;
    }
    else if (inputCommand == "D") {
        std::cout << "Decompressing... please wait" << std::endl;

        std::ifstream inputFile(argv[1]);
        if (!inputFile.is_open()) {
            std::cout << "Failed to open file" << std::endl;
            return 1;
        }
        std::string compressed;
        std::getline(inputFile, compressed);
        inputFile.close();

        //std::cout << "Compressed: " << compressed << std::endl;

        std::string decompressed;
        decompress(compressed, decompressed);
        //decompress(compressed, argv[3]); For commented variant.
        //std::cout << "Decompressed: " << decompressed << std::endl;

        std::ofstream file(argv[3]);
        file << decompressed;
        file.close();

        std::cout << "Done!" << std::endl;
    }
    else {
        std::cout << "Usage:" << std::endl;
        std::cout << "FILE_INPUT {C or D} NAME_OUTPUT" << std::endl;
        return 1;
    }

    return 0;
}