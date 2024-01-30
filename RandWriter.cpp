// Copyright 2023 Bikash Shrestha
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include "RandWriter.hpp"

// constructor
RandWriter::RandWriter(std::string text, int k) : text(text), K(k) {
    if (k < 0 || text.length() < static_cast<std::string::size_type>(k)) {
        throw std::logic_error("Invalid order or text length for Markov model");
    }

    if (k == 0) {
        for (char c : text) {
            _map[""][c]++;
        }
    } else {
        for (size_t i = 0; i < text.length(); ++i) {
            std::string kgram = text.substr(i, K);
            if (kgram.length() < static_cast<std::string::size_type>(K)) {
                kgram += text.substr(0, static_cast<std::string::size_type>(K) - kgram.length());
            }
            char nextChar = text[(i + K) % text.length()];
            addToModel(kgram, nextChar);
        }
    }
}

// add a kgram and the next character to the Markov model
void RandWriter::addToModel(const std::string& kgram, char nextChar) {
    _map[kgram][nextChar]++;
}

// order of the Markov model
int RandWriter::orderK() const {
    return K;
}

// frequency of a kgram
int RandWriter::freq(std::string kgram) const {
    if (kgram.length() != static_cast<size_t>(K)) {
        throw std::logic_error("kgram length must match Markov model order");
    }
    auto it = _map.find(kgram);
    if (it == _map.end()) {
        return 0;
    }
    int count = 0;
    for (const auto& pair : it->second) {
        count += pair.second;
    }
    return count;
}

// frequency of a specific character following a kgram
int RandWriter::freq(std::string kgram, char c) const {
    if (K == 0) {
        int count = 0;
        for (char ch : text) {
            if (ch == c) count++;
        }
        return count;
    }
    if (kgram.length() != static_cast<size_t>(K)) {
        throw std::logic_error("kgram length must match Markov model order");
    }
    auto it = _map.find(kgram);
    if (it == _map.end() || it->second.find(c) == it->second.end()) {
        return 0;
    }
    return it->second.at(c);
}

// select a random character from the possible characters for the given kgram
char RandWriter::kRand(std::string kgram) {
    static std::random_device rd;
    static std::mt19937 gen(rd());

    if (K == 0) {
        std::vector<char> characters;
        for (const auto& pair : _map[""]) {
            characters.insert(characters.end(), pair.second, pair.first);
        }
        std::uniform_int_distribution<> dist(0, characters.size() - 1);
        return characters[dist(gen)];
    }

    if (kgram.length() != static_cast<size_t>(K) || _map.find(kgram) == _map.end()) {
        throw std::logic_error("Invalid kgram");
    }

    std::vector<char> possibleChars;
    for (const auto& pair : _map[kgram]) {
        possibleChars.insert(possibleChars.end(), pair.second, pair.first);
    }

    std::uniform_int_distribution<> dist(0, possibleChars.size() - 1);
    return possibleChars[dist(gen)];
}


// generate text using the default character selection function
std::string RandWriter::generate(std::string kgram, int L) {
    if (kgram.length() != static_cast<size_t>(K)) {
        throw std::logic_error("Starting kgram length must match Markov model order");
    }

    std::string generatedText = kgram;
    for (int i = K; i < L; ++i) {
        char nextChar = kRand(generatedText.substr(i - K, K));
        generatedText += nextChar;
    }

    return generatedText;
}

// generate text using a custom character selection function
std::string RandWriter::generate(std::string kgram, int L, std::function<char
(const std::string&)> charSelector) {
    std::string generatedText = kgram;
    for (int i = K; i < L; ++i) {
        char nextChar = charSelector(generatedText.substr(i - K, K));
        generatedText += nextChar;
    }

    return generatedText;
}

// output the Markov model state
std::ostream& operator<<(std::ostream& os, const RandWriter& rw) {
    os << "Order: " << rw.K << "\n";
    for (const auto& kgram : rw._map) {
        for (const auto& entry : kgram.second) {
            os << "k-gram: " << kgram.first << ", Next char: " <<
            entry.first << ", Freq: " << entry.second << "\n";
        }
    }
    return os;
}
