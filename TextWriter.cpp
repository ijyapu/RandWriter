// Copyright 2023 Bikash Shrestha
#include <fstream>
#include <iostream>
#include "RandWriter.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " k L" << std::endl;
        return 1;
    }

    int k = std::stoi(argv[1]);
    int L = std::stoi(argv[2]);

    std::string text, line;
    while (getline(std::cin, line)) {
        text += line + " ";
    }

    RandWriter rwriter(text, k);
    auto charSelector = [&rwriter](const std::string& kgram) {
        return rwriter.kRand(kgram);
    };

    std::string generatedText = rwriter.generate(text.substr(0, k), L, charSelector);

    std::cout << generatedText << std::endl;

    std::ofstream file("output.txt");
    if (file.is_open()) {
        file << "Generated Text:\n" << generatedText << "\n\n";
        file << "Markov Model State:\n" << rwriter;
        file.close();
    } else {
        std::cerr << "Unable to open file for writing" << std::endl;
    }

    return 0;
}
