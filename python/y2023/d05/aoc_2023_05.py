from multiprocessing import Pool
from common import timer, Puzzle


class Day05(Puzzle, year=2023, day=5):
    @staticmethod
    def clean_input(data):
        maps = dict()
        for i in range(0, len(data)):
            line = data[i]
            match (line[0:5]):
                case "seeds":
                    maps["seeds"] = [int(num) for num in line[6:].split()]
                case "seed-":
                    sts = dict()
                    i += 1
                    line = data[i]
                    while line != "":
                        ranges = [int(num) for num in line.split()]
                        sts[ranges[1]] = (ranges[0], ranges[2])
                        i += 1
                        line = data[i]
                    maps["seed-to-soil"] = sts
                case "soil-":
                    sts = dict()
                    i += 1
                    line = data[i]
                    while line != "":
                        ranges = [int(num) for num in line.split()]
                        sts[ranges[1]] = (ranges[0], ranges[2])
                        i += 1
                        line = data[i]
                    maps["soil-to-fertilizer"] = sts
                case "ferti":
                    sts = dict()
                    i += 1
                    line = data[i]
                    while line != "":
                        ranges = [int(num) for num in line.split()]
                        sts[ranges[1]] = (ranges[0], ranges[2])
                        i += 1
                        line = data[i]
                    maps["fertilizer-to-water"] = sts
                case "water":
                    sts = dict()
                    i += 1
                    line = data[i]
                    while line != "":
                        ranges = [int(num) for num in line.split()]
                        sts[ranges[1]] = (ranges[0], ranges[2])
                        i += 1
                        line = data[i]
                    maps["water-to-light"] = sts
                case "light":
                    sts = dict()
                    i += 1
                    line = data[i]
                    while line != "":
                        ranges = [int(num) for num in line.split()]
                        sts[ranges[1]] = (ranges[0], ranges[2])
                        i += 1
                        line = data[i]
                    maps["light-to-temperature"] = sts
                case "tempe":
                    sts = dict()
                    i += 1
                    line = data[i]
                    while line != "":
                        ranges = [int(num) for num in line.split()]
                        sts[ranges[1]] = (ranges[0], ranges[2])
                        i += 1
                        line = data[i]
                    maps["temperature-to-humidity"] = sts
                case "humid":
                    sts = dict()
                    i += 1
                    line = data[i]
                    while line != "":
                        ranges = [int(num) for num in line.split()]
                        sts[ranges[1]] = (ranges[0], ranges[2])
                        i += 1
                        if i < len(data):
                            line = data[i]
                        else:
                            line = ""
                    maps["humidity-to-location"] = sts
        return maps

    def get_mapped(self, key, mapvar):
        for k, v in mapvar.items():
            if k <= key < k + v[1]:
                return key + (v[0] - k)
        return key

    def filter_maps(self, key: str, input_range: list) -> list:
        vm_sorted = sorted(self.data[key].items(), key=lambda item: item[1][0])
        filtered_map = []
        for r in input_range:
            filtered_map.extend(
                [
                    t
                    for t in vm_sorted
                    if (t[1][0] <= r[0] < t[1][0] + t[1][1])
                    or (t[1][0] <= r[1] <= t[1][0] + t[1][1])
                ]
            )
        return filtered_map

    @staticmethod
    def filtered_range(filtered_map, input_range):
        mapped_range = []
        for r in input_range:
            for t in filtered_map:
                start = max(t[1][0], r[0])
                end = min(t[1][0] + t[1][1], r[1])
                if (start < end) and ((start, end) not in mapped_range):
                    mapped_range.append((start, end))

        output_range = []

        for hh, rr in zip(mapped_range, filtered_map):
            output_range.append((rr[0] + hh[0] - rr[1][0], rr[0] + hh[1] - rr[1][0]))

        gaps = list()
        for z in zip(mapped_range[:-1], mapped_range[1:]):
            if z[0][1] != z[1][0]:
                gaps.append((z[0][1], z[1][0]))

        return output_range

    def min_location_range(self):
        locs = sorted(self.data["humidity-to-location"].items(), key=lambda item: item[1][0])
        if locs[0][1][0] > 0:
            locs.insert(0, (0, (0, locs[0][1][0])))

        return [(locs[0][0], locs[0][0] + locs[0][1][1])]

    def find_locations(self, seeds):
        soils = [self.get_mapped(seed, self.data["seed-to-soil"]) for seed in seeds]
        fertilizers = [self.get_mapped(soil, self.data["soil-to-fertilizer"]) for soil in soils]
        waters = [
            self.get_mapped(fertilizer, self.data["fertilizer-to-water"])
            for fertilizer in fertilizers
        ]
        lights = [self.get_mapped(water, self.data["water-to-light"]) for water in waters]
        temps = [self.get_mapped(light, self.data["light-to-temperature"]) for light in lights]
        humids = [self.get_mapped(temp, self.data["temperature-to-humidity"]) for temp in temps]
        locs = [self.get_mapped(humid, self.data["humidity-to-location"]) for humid in humids]
        return locs

    @staticmethod
    def lookup(point: int, lookup_range: dict) -> int | None:
        for k, v in lookup_range.items():
            if k[0] <= point < k[1]:
                return v[0] + point - k[0]
        return point

    @staticmethod
    def transform_source_range(source_range, destination_range):
        source = []
        dl = list()
        for s, t in destination_range:
            dl.append(s)
            dl.append(t)

        for s in source_range:
            arr = []
            dest_list = sorted(list(set(dl)))
            arr.append(s[0])
            value = s[0]
            if dest_list:
                while dest_list[0] < s[0]:
                    value = dest_list.pop(0)
                    if not dest_list:
                        break
                if dest_list:
                    value = dest_list.pop(0)
                if s[0] < value < s[1]:
                    arr.append(value)
            if dest_list:
                while dest_list[0] < s[1]:
                    arr.append(dest_list.pop(0))
                    if not dest_list:
                        break
            arr.append(s[1])
            source += [(s, t) for s, t in zip(arr[:-1], arr[1:])]

        return source

    @staticmethod
    def match_range(destination_map, source_range):
        destination_range = dict()

        dst_rg1 = {
            (m[1][0], m[1][0] + m[1][1]): ((m[0], m[0] + m[1][1])) for m in destination_map.items()
        }
        sr = Day05.transform_source_range(source_range, dst_rg1)

        for rng in sr:
            if rng[0] > max(max(dst_rg1.keys())):
                destination_range[rng] = rng
            else:
                for s_r, d_r in dst_rg1.items():
                    if (s_r[0] <= rng[0]) and (rng[1] <= s_r[1]):
                        destination_range[rng] = (
                            rng[0] + d_r[0] - s_r[0],
                            rng[1] + d_r[0] - s_r[0],
                        )
                    else:
                        destination_range.setdefault(rng, rng)

        return destination_range

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        locs = self.find_locations(self.data["seeds"])
        return min(locs)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        seeds = self.data["seeds"]
        seed_map = [(seeds[i], (seeds[i], seeds[i + 1])) for i in range(0, len(seeds), 2)]
        seed_range = [(seed[0], seed[0] + seed[1][1]) for seed in seed_map]
        soils_range = self.match_range(
            {s[1][0]: (s[0], s[1][1]) for s in self.data["seed-to-soil"].items()}, seed_range
        )
        fertilizer_range = self.match_range(
            {s[1][0]: (s[0], s[1][1]) for s in self.data["soil-to-fertilizer"].items()},
            soils_range.values(),
        )
        water_range = self.match_range(
            {s[1][0]: (s[0], s[1][1]) for s in self.data["fertilizer-to-water"].items()},
            fertilizer_range.values(),
        )
        light_range = self.match_range(
            {s[1][0]: (s[0], s[1][1]) for s in self.data["water-to-light"].items()},
            water_range.values(),
        )
        temperature_range = self.match_range(
            {s[1][0]: (s[0], s[1][1]) for s in self.data["light-to-temperature"].items()},
            light_range.values(),
        )
        humidity_range = self.match_range(
            {s[1][0]: (s[0], s[1][1]) for s in self.data["temperature-to-humidity"].items()},
            temperature_range.values(),
        )
        location_range = self.match_range(
            {s[1][0]: (s[0], s[1][1]) for s in self.data["humidity-to-location"].items()},
            humidity_range.values(),
        )

        min_location = min(min(location_range.values()))
        return min_location
