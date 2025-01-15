#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <string>

int main(void) {
    std::ifstream ifs("/home/christian/projects/adventofcode/data/2015/01/input.txt");
    std::string   input;
    std::getline(ifs, input);

    auto rng = input | std::views::transform([](auto &c) { return c == ')' ? -1 : 1; }) | std::views::common;
    std::cout << std::reduce(rng.begin(), rng.end()) << std::endl;

    return 0;
}
