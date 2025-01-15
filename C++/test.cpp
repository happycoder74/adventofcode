#include <fstream>
#include <iostream>
#include <ranges>
#include <vector>

struct FileLine {
  private:
    std::string line;

  public:
    size_t           line_number = 0;
    std::vector<int> values;

    // clang-format off
    friend std::istream &operator>>(std::istream &s, FileLine &fl) {
        std::getline(s, fl.line);
        ++fl.line_number;

        fl.values = fl.line
            | std::views::split(' ')
            | std::views::transform([](auto &&c) {
                    return std::stoi(std::string(c.begin(), c.end()));
                    })
            | std::ranges::to<std::vector<int>>();
        return s;
        // clang-format on
    }
};

int main(void) {
    std::ifstream input{"testinput.txt"};
    std::string   line = "1 2 3 4";

    auto lines = std::views::istream<FileLine>(input);
    for (auto c : lines) {
        std::cout << "Line " << c.line_number << ": (" << c.values.size() << ")";
        for (auto val : c.values) {
            std::cout << "'" << val << "'";
        }
        std::cout << std::endl;
    }
}
