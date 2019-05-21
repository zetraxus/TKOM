//
// Created by adam on 05.05.19.
//

#include "For.h"

For::For(Token::Type type, const std::string& itName, const std::string& container) : type(type), itName(itName),
                                                                                      container(container) {}

void For::setBody(std::unique_ptr <Block> body) {
    For::body = std::move(body);
}
