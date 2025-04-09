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

constexpr int n_deltas = 9;

namespace aoc {
template <typename T>
class Grid {
  private:
    int x{0};
    int y{0};

    std::unordered_map<std::pair<int, int>, T> grid;
    std::array<std::pair<int, int>, n_deltas>  delta_array = {
        {{-1, -1}, {0, -1}, {1, -1}, {-1, 0}, {0, 0}, {1, 0}, {-1, 1}, {0, 1}, {1, 1}}
    };

  public:
    [[nodiscard]] const auto &deltas() const {
        return delta_array;
    }

    Grid() {
        grid[{x, y}] = 0;
    }

    void insert(const std::pair<int, int> &pos, T val) {
        grid[pos] = val;
    }

    [[nodiscard]] T get_value(const std::pair<int, int> &position) {
        return grid[position];
    }
};
} // namespace aoc

#endif // !AOC_TYPES_HPP
