#include <fstream>
#include <string>
#include <vector>

namespace aoc {
    std::string get_input_bare(std::string fn, int year, int day) {
        std::ifstream ifs(fn);
        std::string line;

        std::getline(ifs, line);

        return line;
    }
}
