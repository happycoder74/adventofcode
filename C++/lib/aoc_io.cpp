#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace aoc {

std::string get_input_bare(std::string fn) {
    std::ifstream ifs(fn);
    std::string   line;

    std::getline(ifs, line);

    return line;
}

namespace string {
std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string              token;
    std::istringstream       str_stream(str);

    while (std::getline(str_stream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

} // namespace string

} // namespace aoc
