//
// Created by adam on 06.04.19.
//

#ifndef TKOM_SOURCE_H
#define TKOM_SOURCE_H


#include <string>
#include <fstream>
#include <sstream>

class Position {
    unsigned line;
    int position; // position in line

public:
    explicit Position(unsigned int line = 1, int position = 0);

    Position(const Position& other);

    void incrementPosition();

    void incrementLine();

    unsigned int getLine() const;

    int getPosition() const;
};


class Source {

private:

    std::string fileName;
    std::ifstream inputStream;
    Position* current;
    bool mode; // 0 release, 1 tests
    std::stringstream input; // if mode == 0

public:
    Source(const std::string& fileName, bool mode = 0);

    virtual ~Source();

    int getNextChar();

    int peekNextChar();

    Position* getCurrentPosition() const;

};


#endif //TKOM_SOURCE_H
