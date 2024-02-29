#include <iostream>

#include "wc.hpp"

int main(int argc, char *argv[]) {
    Wc wc{argv};
    auto out = wc.getWcOutput();
    std::cout << out << '\n';
}