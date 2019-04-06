//
// Created by adam on 06.04.19.
//

#ifndef TKOM_SOURCE_H
#define TKOM_SOURCE_H


#include <string>
#include <fstream>

class Position {
    unsigned line;
    unsigned position; // position in line

public:
    explicit Position(unsigned int line = 0, unsigned int position = 0);
};


class Source {

private:

    const std::string& fileName;
    std::ifstream inputStream;
    Position* current;

public:
    Source(const std::string& fileName);
};


#endif //TKOM_SOURCE_H
