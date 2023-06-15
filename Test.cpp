#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include <stdexcept>

using namespace ariel;
using namespace std;


TEST_CASE("Throws checks "){
    CHECK_NOTHROW(MagicalContainer container);
    MagicalContainer container;
    CHECK_NOTHROW(container.addElement(1));
    CHECK(container.size() == 1);
    CHECK_NOTHROW(container.removeElement(1));
    CHECK(container.size() == 0);
    container.addElement(2);
    CHECK_THROWS_AS(container.removeElement(3), runtime_error);
}

// Test case for the AscendingIterator
TEST_CASE("AscendingIterator") {
    MagicalContainer container;
    container.addElement(10);
    container.addElement(20);
    container.addElement(30);
    container.addElement(15);
    container.addElement(25);


    SUBCASE("Iterating over elements") {
        MagicalContainer::AscendingIterator it(container);
        CHECK(*it == 10);
        ++it;
        CHECK(*it == 15);
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 25);
        ++it;
        CHECK(*it == 30);
        ++it;
        CHECK(it == it.end());
    }

    SUBCASE("Iterating over an empty container") {
        MagicalContainer emptyContainer;
        MagicalContainer::AscendingIterator it(emptyContainer);
        CHECK(it == it.end());
    }
}

// Test case for the SideCrossIterator
TEST_CASE("SideCrossIterator") {
    MagicalContainer container;
    container.addElement(10);
    container.addElement(20);
    container.addElement(30);
    container.addElement(40);

    SUBCASE("Iterating over elements") {
        MagicalContainer::SideCrossIterator it(container);
        CHECK(*it == 10);
        ++it;
        CHECK(*it == 40);
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 30);
        ++it;
        CHECK(it == it.end());
    }

    SUBCASE("Iterating over an empty container") {
        MagicalContainer emptyContainer;
        MagicalContainer::SideCrossIterator it(emptyContainer);
        CHECK(it == it.end());
    }
}

// Test case for the PrimeIterator
TEST_CASE("PrimeIterator") {
    MagicalContainer container;
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);
    container.addElement(4);
    container.addElement(5);
    container.addElement(6);

    SUBCASE("Iterating over elements") {
        MagicalContainer::PrimeIterator it(container);
        CHECK(*it == 2);
        ++it;
        CHECK(*it == 3);
        ++it;
        CHECK(*it == 5);
        ++it;
        CHECK(it == it.end());
    }

    SUBCASE("Iterating over an empty container") {
        MagicalContainer emptyContainer;
        MagicalContainer::PrimeIterator it(emptyContainer);
        CHECK(it == it.end());
    }
}

// Test case for comparing iterators from the same container
TEST_CASE("Comparing iterators from the same container") {
    MagicalContainer container;
    for (int i = 1; i <= 10; ++i) {
        container.addElement(i * 10);
    }

    SUBCASE("Comparing AscendingIterator with itself") {
        MagicalContainer::AscendingIterator it1(container);
        MagicalContainer::AscendingIterator it2(container);
        CHECK(it1 == it2);
        CHECK(!(it1 != it2));
        CHECK(!(it1 < it2));
        CHECK(!(it1 > it2));
    }

    SUBCASE("Comparing SideCrossIterator with itself") {
        MagicalContainer::SideCrossIterator it1(container);
        MagicalContainer::SideCrossIterator it2(container);
        CHECK(it1 == it2);
        CHECK(!(it1 != it2));
        CHECK(!(it1 < it2));
        CHECK(!(it1 > it2));
    }

    SUBCASE("Comparing PrimeIterator with itself") {
        MagicalContainer::PrimeIterator it1(container);
        MagicalContainer::PrimeIterator it2(container);
        CHECK(it1 == it2);
        CHECK(!(it1 != it2));
        CHECK(!(it1 < it2));
        CHECK(!(it1 > it2));
    }
}



