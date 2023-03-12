from common import timer, Puzzle


class Day03(Puzzle, year=2021, day=3):
    @staticmethod
    def common_value(data, position, method):
        sum = 0
        for bits in data:
            sum += int(bits[position])
        check = sum / len(data)
        if method == 'most':
            return_value = str(int(check < 0.5))
        else:
            return_value = str(int(check >= 0.5))

        return return_value

    @staticmethod
    def reduce_list(data, value, position):
        d = []
        for item in data:
            if item[position] != value:
                d.append(item)
        return d

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        sum1 = [0] * len(self.data[0])
        sum2 = sum1.copy()
        for bits in self.data:
            for i in range(0, len(bits)):
                sum1[i] += int(bits[i])

        for i, s in enumerate(sum1):
            s = s / len(self.data)
            sum2[i] = s

        gamma = list(map(lambda x: '1' if x > 0.5 else '0', sum2))
        epsilon = list(map(lambda x: '1' if x < 0.5 else '0', sum2))

        return int(''.join(gamma), 2) * int(''.join(epsilon), 2)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        data2 = self.data.copy()

        position = 0
        while (len(self.data) > 1):
            value = Day03.common_value(self.data, position, method='most')
            self.data = Day03.reduce_list(self.data, value, position)
            position += 1

        position = 0
        while (len(data2) > 1):
            value = Day03.common_value(data2, position, method='least')
            data2 = Day03.reduce_list(data2, value, position)
            position += 1

        oxygen_generator_rating = int(''.join(self.data), 2)
        co2_scrubber_rating = int(''.join(data2), 2)

        return oxygen_generator_rating * co2_scrubber_rating
