#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <fmt/core.h>

std::string get_line_data(const char *filename, uint16_t year, uint8_t day) {
    std::string line_data;
    std::string inputfile;
    std::ifstream ifs;
    inputfile = fmt::format("/home/yy11510/projects/adventofcode/data/{}/{:02d}/{}",
            year, day, filename);
    std::cout << "Reading from '" << inputfile << "'" << "\n";
    ifs = std::ifstream(inputfile);
    std::getline(ifs, line_data);
    return line_data;
}


int main(int argc, char **argv) {
    int16_t level = 0;
    uint16_t counter = 0;
    bool basement_found = false;


    std::string line = get_line_data("input.txt", 2015, 1);

    for (auto ch: line) {
        ch == '(' ? level++ : level--;
        if(!basement_found) {
            counter++;
            if (level == -1) {
                basement_found = true;
            }
        }
    }

    std::cout << level << std::endl;
    std::cout << counter << std::endl;
    return 0;
}

