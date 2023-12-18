#include <fstream>
#include <string>
#include <vector>

namespace aoc::io {

std::string get_input_bare(std::string fn) {

    std::ifstream ifs(fn);
    std::string   line;

    std::getline(ifs, line);

    return line;
}

std::vector<std::string> get_input(std::string filename) {
    std::vector<std::string> return_vector;
    std::ifstream            ifs(filename);
    std::string              line;

    while (std::getline(ifs, line)) {
        return_vector.push_back(line);
    }

    return return_vector;
}

} // namespace aoc::io
