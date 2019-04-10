//
// Created by adam on 07.04.19.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE LexerTests
#include <boost/test/unit_test.hpp>
#include "../lexer/Scanner.h"
#include "../lexer/Source.h"

BOOST_AUTO_TEST_CASE(test1){
    BOOST_CHECK(2 + 2 == 4);
}