#ifndef AOC_TYPES_HPP
#define AOC_TYPES_HPP

#include <array>
#include <unordered_map>

template <class A, class B>
struct std::hash<std::pair<A, B>> {
    std::size_t operator()(const std::pair<A, B> &p) const {
        return std::size_t(p.first) << 32 | p.second;
    }
};

namespace aoc {
class Grid {
  private:
    int x{0};
    int y{0};

    std::unordered_map<std::pair<int, int>, unsigned> grid;

  public:
    std::array<std::pair<int, int>, 9> deltas = {
        {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {0, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}}
    };

    Grid() {
        grid[{x, y}] = 0;
    }

    void insert(const std::pair<int, int> &pos, unsigned val) {
        grid[pos] = val;
    }

    unsigned get_value(const std::pair<int, int> &position) {
        return grid[position];
    }
};
} // namespace aoc

#endif // !AOC_TYPES_HPP
