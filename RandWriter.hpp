// Copyright 2023 Bikash Shrestha
#ifndef RANDWRITER_H
#define RANDWRITER_H

#include <iostream>
#include <string>
#include <map>
#include <random>
#include <functional>

class RandWriter {
 public:
    RandWriter(std::string text, int k);
    int orderK() const;
    int freq(std::string kgram) const;
    int freq(std::string kgram, char c) const;
    char kRand(std::string kgram);
    std::string generate(std::string kgram, int L);
    std::string generate(std::string kgram, int L, std::
    function<char(const std::string&)> charSelector);

    friend std::ostream& operator<<(std::ostream& os, const RandWriter& rw);

 private:
    std::string text;
    int K;
    std::map<std::string, std::map<char, int>> _map;
    void addToModel(const std::string& kgram, char nextChar);
};

#endif
