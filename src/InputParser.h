//
// Created by Adrian Murawski on 30/05/2023.
//

#ifndef PROI_PROJEKT_INPUTPARSER_H
#define PROI_PROJEKT_INPUTPARSER_H

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class InputParser{
public:
    InputParser (int &argc, char **argv);
    bool cmdOptionExists(const std::string &option) const;
private:
    vector <string> tokens;
};


#endif //PROI_PROJEKT_INPUTPARSER_H
