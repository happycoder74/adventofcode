#include <fstream>
#include <sstream>
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

namespace aoc::string {

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string              token;
    std::istringstream       str_stream(str);

    while (std::getline(str_stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

} // namespace aoc::string
