// Copyright 2023 Bikash Shrestha
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RandWriterTest
#include <stdexcept>
#include <string>
#include <boost/test/unit_test.hpp>
#include "RandWriter.hpp"

BOOST_AUTO_TEST_CASE(constructor_test) {
    // Empty text
    BOOST_REQUIRE_THROW(RandWriter rw("", 2), std::logic_error);
    // valid case
    BOOST_REQUIRE_NO_THROW(RandWriter rw("gagggagaggcgagaaa", 2));
}

BOOST_AUTO_TEST_CASE(orderK_test) {
    RandWriter rw("gagggagaggcgagaaa", 2);
    BOOST_REQUIRE(rw.orderK() == 2);
}

BOOST_AUTO_TEST_CASE(freq_test) {
    RandWriter rw("gagggagaggcgagaaa", 2);
    BOOST_REQUIRE(rw.freq("ga") == 5);  // Valid kgram
    // Invalid kgram length
    BOOST_REQUIRE_THROW(rw.freq("gag"), std::logic_error);
}

BOOST_AUTO_TEST_CASE(kRand_test) {
    RandWriter rw("gagggagaggcgagaaa", 2);
    BOOST_REQUIRE_NO_THROW(rw.kRand("ga"));  // Valid kgram
    // Invalid kgram length
    BOOST_REQUIRE_THROW(rw.kRand("gag"), std::logic_error);
}

BOOST_AUTO_TEST_CASE(generate_test) {
    RandWriter rw("gagggagaggcgagaaa", 2);
    std::string generated = rw.generate("ga", 5);
    BOOST_REQUIRE(generated.size() == 5);  // Check generated text length
    // Invalid kgram length
    BOOST_REQUIRE_THROW(rw.generate("gag", 5), std::logic_error);
}
