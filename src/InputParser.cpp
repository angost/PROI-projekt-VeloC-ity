//
// Created by Adrian Murawski on 30/05/2023.
//

#include "InputParser.h"


InputParser::InputParser(int &argc, char **argv) {
    for (int i=1; i < argc; ++i)
        this->tokens.push_back(string(argv[i]));
}

bool InputParser::cmdOptionExists(const std::string &option) const {
    return find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
}

