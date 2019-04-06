//
// Created by adam on 06.04.19.
//

#include "Source.h"
#include <iostream>

Source::Source(const std::string& fileName) : fileName(fileName) {
    current = new Position();
    inputStream.open(fileName.c_str());
    if(!inputStream)
        throw std::runtime_error ("File not found.");
}

Position::Position(unsigned int line, unsigned int position) : line(line), position(position) {}
