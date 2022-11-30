import sys
from common import timer, Puzzle


class Day04(Puzzle, year=2020, day=4):
    @staticmethod
    def clean_input(data):
        result = list()
        start = 0
        try:
            while end := data.index(''):
                result.append(" ".join(data[start:end]))
                _ = data.pop(end)
                start = end
        except ValueError:
            result.append(" ".join(data[start:]))

        passports = []
        for row in result:
            passport = {item.split(":")[0]: item.split(":")[1] for item in row.split(' ')}
            passports.append(passport)

        return passports

    @staticmethod
    def validate(passport):
        required_keys = ['ecl', 'pid', 'eyr', 'hcl', 'byr', 'iyr', 'hgt']
        for key in required_keys:
            if key not in passport.keys():
                return False
        # test ecl
        if passport['ecl'] not in ["amb", "blu", "brn", "gry", "grn", "hzl", "oth"]:
            return False

        # test pid
        if (len(passport['pid']) != 9) | (not passport['pid'].isnumeric()):
            return False

        # test eyr
        if (len(passport['eyr']) != 4) | (not passport['eyr'].isnumeric()):
            return False
        if (passport['eyr'] < "2020") | (passport['eyr'] > "2030"):
            return False

        # test byr
        if (len(passport['byr']) != 4) | (not passport['byr'].isnumeric()):
            return False
        if (passport['byr'] < "1920") | (passport['byr'] > "2002"):
            return False

        # test iyr
        if (len(passport['iyr']) != 4) | (not passport['iyr'].isnumeric()):
            return False
        if (passport['iyr'] < "2010") | (passport['iyr'] > "2020"):
            return False

        # test hcl
        if (len(passport['hcl']) != 7) | (passport['hcl'][0] != '#'):
            return False
        for c in passport['hcl'][1:]:
            if c not in "0123456789abcdef":
                return False

        # test hgt
        hgt = passport['hgt']
        hgt_unit = hgt[-2:]
        if (hgt_unit not in ["cm", "in"]) | (not hgt[:-2].isnumeric()):
            return False
        if hgt_unit == "cm":
            return ((hgt[:-2] >= "150") & (hgt[:-2] <= "193"))
        else:
            return ((hgt[:-2] >= "59") & (hgt[:-2] <= "76"))

        return True

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        valid = 0

        for passport in self.data:
            if len(passport.keys()) == 7 and ("cid" not in passport.keys()):
                valid += 1
            elif len(passport.keys()) == 8:
                valid += 1

        return valid

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        valid = 0

        for passport in self.data:
            if(self.validate(passport)):
                valid += 1

        return valid

    @timer(part="main", title="Total elapsed", show_return=False)
    def solve_all(self):
        part1 = self.solve_part_1()
        part2 = self.solve_part_2()

        return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    Day04(filename=filename).solve_all()
