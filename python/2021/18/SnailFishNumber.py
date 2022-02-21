class SnailfishNumber:
    def __init__(self, number):
        if isinstance(number, str):
            self.number = self.from_string(number)
        else:
            self.number = number.copy()

    def __add__(self, number):
        sf = SnailfishNumber(
            [(num, depth + 1) for num, depth in self.number + number.number]
        )
        return sf.reduce()

    def explode(self):
        for i, (num, depth) in enumerate(self.number):
            if depth >= 5:
                right, _ = self.number.pop(i + 1)
                if i > 0:
                    l_num, l_depth = self.number[i - 1]
                    self.number[i - 1] = (l_num + num, l_depth)
                self.number[i] = (0, depth - 1)
                if i < len(self.number) - 1:
                    r_num, r_depth = self.number[i + 1]
                    self.number[i + 1] = (r_num + right, r_depth)
                break

        return self

    def split(self):
        for i, (num, depth) in enumerate(self.number):
            if num >= 10:
                self.number[i] = (num // 2, depth + 1)
                self.number.insert(i + 1, ((num + 1) // 2, depth + 1))
                break
        return self

    def reduce(self):
        changed = True
        while changed:
            old = SnailfishNumber(self.number)
            if not old == self.explode():
                continue
            changed = False
            if not old == self.split():
                changed = True
                continue

        return self

    def __str__(self):
        return str(self.number)

    def __repr__(self):
        return f"<SnailFish {str(self)}>"

    def __eq__(self, other):
        return self.number == other.number

    def __ne__(self, other):
        return not self == other

    @staticmethod
    def to_string(num):
        nlist = list(num.number)
        max_level = max([d for (n, d) in num.number])
        for level in range(max_level, 0, -1):
            for i, (number, depth) in enumerate(nlist):
                if depth == level:
                    nlist[i] = (
                        f"[{nlist[i][0]},{nlist[i + 1][0]}]",
                        depth - 1,
                    )
                    _ = nlist.pop(i + 1)
        return nlist[0][0]

    @staticmethod
    def magnitude(num):
        nlist = list(num.number)
        for level in range(4, 0, -1):
            for i, (number, depth) in enumerate(nlist):
                if depth == level:
                    nlist[i] = (
                        nlist[i][0] * 3 + nlist[i + 1][0] * 2,
                        depth - 1,
                    )
                    _ = nlist.pop(i + 1)
        return nlist[0][0]

    @staticmethod
    def from_string(number):
        numlist = [
            (int(c), number[:i].count("[") - number[:i].count("]"))
            for i, c in enumerate(number)
            if c.isnumeric()
        ]
        return numlist
