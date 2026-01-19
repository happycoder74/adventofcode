#include "aoc_io.hpp"
#include "aoc_timer.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <functional>
#include <iterator>
#include <optional>
#include <ranges>
#include <sys/types.h>
#include <unordered_map>
#include <vector>

struct Time {
    uint32_t year;
    uint32_t month;
    uint32_t day;
    uint32_t hour;
    uint32_t minute;

    Time() = default;

    Time(const std::string &s) {
        year   = std::stoi(s.substr(1, 4));
        month  = std::stoi(s.substr(6, 2));
        day    = std::stoi(s.substr(9, 2));
        hour   = std::stoi(s.substr(12, 2));
        minute = std::stoi(s.substr(15, 2));
    }

    auto operator<=>(const Time &other) const -> auto = default;
    auto operator==(const Time &other) const -> bool  = default;

    [[nodiscard]] auto to_string() const -> std::string {
        return std::format("{}-{:02}-{:02} {:02}:{:02}", year, month, day, hour, minute);
    }
};

enum struct EventType : uint8_t {
    ShiftBegin,
    FellAsleep,
    WakesUp
};

struct Log {
    uint32_t  id{};
    EventType type{};
    Time      time{};

    Log() = default;

    explicit Log(const std::string &s) : id(std::uint32_t{}) {
        auto index = s.find_first_of(']') + 2;
        time       = Time(s);
        switch (s[index]) {
            case 'G':
                {
                    auto part    = s | std::views::split('#') | std::views::drop(1);
                    auto sv_part = std::string(std::string_view(part.front()));
                    id           = std::stoi(sv_part);
                    type         = EventType::ShiftBegin;
                    break;
                }
            case 'f':
                {
                    type = EventType::FellAsleep;
                    break;
                }
            case 'w':
                {
                    type = EventType::WakesUp;
                    break;
                }
            default:
                std::println("Error in Log - '{}'", s[index]);
                std::exit(EXIT_FAILURE);
        }
    }

    [[nodiscard]] auto to_string() const -> std::string {
        std::string event_str{};

        if (type == EventType::FellAsleep) {
            event_str = "FellAsleep";
        } else if (type == EventType::WakesUp) {
            event_str = "WakesUp";
        } else {
            event_str = std::format("Guard {} begins shift", id);
        }

        return std::format("{} => {}", time.to_string(), event_str);
    }
};

struct Guard {
    uint32_t                 id{};
    uint32_t                 minutes_asleep{};
    std::array<uint32_t, 60> frequency{};

    void register_sleep_time(auto start, auto end) {
        minutes_asleep += end - start;
        for (auto i = start; i < end; ++i) {
            frequency[i] += 1;
        }
    }

    auto operator<=>(const auto &other) const {
        if (minutes_asleep < other.minutes_asleep) {
            return -1;
        } else if (minutes_asleep > other.minutes_asleep) {
            return 1;
        }
        return 0;
    }

    auto operator==(const auto &other) const {
        return minutes_asleep == other.minutes_asleep;
    }

    [[nodiscard]] auto to_string() const -> std::string {
        return std::format("id: {}, minutes_asleep: {}\nfreq: {}", id, minutes_asleep, frequency);
    }
};

auto parse_data(const std::vector<std::string> &input) -> std::vector<Log> {
    auto result = input | std::views::transform([](const auto &s) {
                      return Log{s};
                  }) |
                  std::ranges::to<std::vector>();

    std::ranges::stable_sort(result, [](const auto &a, const auto &b) {
        return a.time < b.time;
    });

    return result;
}

auto calculate_stats(const auto &logs) {
    auto guards     = std::unordered_map<uint32_t, Guard>{};
    auto last_guard = std::uint32_t{};

    std::optional<Time> fell_asleep = std::nullopt;

    for (const auto &log_entry : logs) {
        if (log_entry.type == EventType::ShiftBegin) {
            if (!guards.contains(log_entry.id)) {
                auto guard = Guard{log_entry.id};
                guards.insert({log_entry.id, guard});
            }
            last_guard = log_entry.id;
        } else if (log_entry.type == EventType::FellAsleep) {
            fell_asleep = std::optional<Time>(log_entry.time);
        } else if (log_entry.type == EventType::WakesUp) {
            auto   start = fell_asleep.value();
            Guard &guard = guards[last_guard];
            guard.register_sleep_time(start.minute, log_entry.time.minute);
            fell_asleep = std::nullopt;
        }
    }

    auto values = guards | std::views::transform([](const auto &kv) {
                      return kv.second;
                  }) |
                  std::ranges::to<std::vector>();
    return values;
}

auto solve_part_1(const std::vector<Guard> &guards) -> size_t {
    auto max_guard = std::ranges::max(guards);
    auto max_freq  = std::ranges::distance(max_guard.frequency.begin(), std::ranges::max_element(max_guard.frequency));
    return max_guard.id * max_freq;
}

auto solve_part_2(const std::vector<Guard> &guards) -> size_t {
    auto max_guard  = std::ranges::max(guards, std::ranges::less{}, [](const auto &g) {
        return std::ranges::max(g.frequency);
    });
    auto max_minute = std::ranges::distance(max_guard.frequency.begin(), std::ranges::max_element(max_guard.frequency));
    return max_guard.id * max_minute;
}

void solve_all(const std::vector<std::string> &data) {
    std::vector<Log> parsed_data = parse_data(data);
    auto             guards      = calculate_stats(parsed_data);

    aoc::timer(1, solve_part_1, guards);
    aoc::timer(2, solve_part_2, guards);
}

auto main(int argc, char **argv) -> int {
    std::filesystem::path filepath(std::getenv("AOC_DATA_LOCATION"));

    std::string filename;
    const int   year = 2018;
    const int   day  = 4;

    auto args = std::span(argv, std::size_t(argv));
    if (argc > 1) {
        if (std::string(args[1]) == "--test") {
            filename = "test_input.txt";
        } else {
            filename = args[1];
        }
    } else {
        filename = "input.txt";
    }

    filepath = filepath / std::to_string(year) / std::format("{:02}", day) / filename;
    std::ifstream ifs(filepath);
    std::string   line;

    std::vector<std::string> data;

    while (std::getline(ifs, line)) {
        data.push_back(line);
    }

    aoc::io::header(year, day);
    aoc::timer(solve_all, data);
    return 0;
}
