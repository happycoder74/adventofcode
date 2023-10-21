#include <cstdint>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

std::string get_line_data(std::string filename, uint16_t year, uint8_t day) {
    std::string   line_data;
    std::ifstream ifs;
    std::string   fn;
    std::string   path(std::format("/home/yy11510/projects/adventofcode/data/{}/{:02d}/", year, day));
    if (std::string(filename) == "input.txt") {
        fn = path + filename;
    } else {
        fn = filename;
    }
    ifs = std::ifstream(fn);
    std::getline(ifs, line_data);
    return line_data;
}

int main(int argc, char **argv) {
    std::int16_t  level = 0;
    std::uint16_t counter = 0;
    bool          basement_found = false;
    std::string   filename;

    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "input.txt";
    }

    std::string line = get_line_data(filename, 2015, 1);

    for (auto ch : line) {
        ch == '(' ? level++ : level--;
        if (!basement_found) {
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
