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

        # TODO :
        # This is not working correctly. Should only be gaps in relation to input range.
        # gaps = list()
        # for z in zip(mapped_range[:-1], mapped_range[1:]):
        #     if z[0][1] != z[1][0]:
        #         gaps.append((z[0][1], z[1][0]))

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

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        locs = self.find_locations(self.data["seeds"])
        return min(locs)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        fr = self.min_location_range()
        keys = list(self.data.keys())
        for key in keys[-2:0:-1]:
            fm = self.filter_maps(key, fr)
            fr = self.filtered_range(fm, fr)

        seeds = self.data["seeds"]
        seed_map = [(seeds[i], (seeds[i], seeds[i + 1])) for i in range(0, len(seeds), 2)]
        seed_range = self.filtered_range(seed_map, fr)
        seed_list = [r[0] for r in seed_range]

        def to_list(v):
            return [v]

        locs = map(self.find_locations, map(to_list, seed_list))

        min_location = min(locs)
        return min_location[0]
