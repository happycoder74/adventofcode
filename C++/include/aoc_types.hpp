#ifndef AOC_TYPES_HPP
#define AOC_TYPES_HPP

#include <array>
#include <map>

namespace aoc {
class Grid {
  private:
    int                                     x;
    int                                     y;
    std::map<std::pair<int, int>, unsigned> grid;

  public:
    std::array<std::pair<int, int>, 9> deltas = {
        {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {0, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}}
    };

    Grid() {
        x = 0;
        y = 0;
        grid[{x, y}] = 0;
    }

    void insert(std::pair<int, int> pos, unsigned val) {
        grid[pos] = val;
    }

    unsigned get_value(std::pair<int, int> position) {
        return grid[position];
    }
};
} // namespace aoc

#endif // !AOC_TYPES_HPP
