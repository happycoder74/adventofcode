#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

namespace aoc::string {

// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}

inline std::string trim(std::string &s) {
    ltrim(s);
    rtrim(s);

    return s;
}

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::string              token;
    std::istringstream       str_stream(str);

    while (std::getline(str_stream, token, delimiter)) {
        trim(token);
        if (token.size() > 0) {
            tokens.push_back(token);
        }
    }
    return tokens;
}

} // namespace aoc::string
