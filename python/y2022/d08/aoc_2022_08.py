from common import timer, Puzzle


class Day08(Puzzle, year=2022, day=8):
    @staticmethod
    def clean_input(data):
        return_list = list()
        for row in data:
            return_list.append([int(d) for d in row])
        return return_list

    def look_from_left(self):
        visible = set()
        # looking from left:
        for row_index, row in enumerate(self.data[1:-1]):
            highest = row[0]
            for tree_index, tree in enumerate(row[1:-1]):
                if tree > highest:
                    visible.add((row_index + 1, tree_index + 1))
                    highest = tree
        return visible

    def look_from_right(self):
        visible = set()
        # looking from right
        for row_index, row in enumerate(self.data[1:-1]):
            highest = row[-1]
            for tree_index, tree in enumerate(row[-2:0:-1]):
                if tree > highest:
                    visible.add((row_index + 1, len(row) - tree_index - 2))
                    highest = tree
        return visible

    def look_from_top(self):
        visible = set()
        # looking from top
        for col_index in range(1, len(self.data[0]) - 1):
            highest = self.data[0][col_index]
            for tree_index in range(1, len(self.data) - 1):
                if self.data[tree_index][col_index] > highest:
                    visible.add((tree_index, col_index))
                    highest = self.data[tree_index][col_index]
        return visible

    def look_from_bottom(self):
        # looking from bottom
        visible = set()
        for col_index in range(1, len(self.data[0]) - 1):
            highest = self.data[-1][col_index]
            for tree_index in range(len(self.data) - 2, 0, -1):
                if self.data[tree_index][col_index] > highest:
                    visible.add((tree_index, col_index))
                    highest = self.data[tree_index][col_index]
        return visible

    @timer(part=1)
    def solve_part_1(self):
        """Solution for part 1"""
        visible = self.look_from_top()
        visible = visible.union(self.look_from_bottom())
        visible = visible.union(self.look_from_left())
        visible = visible.union(self.look_from_right())

        return len(visible) + 2*len(self.data[0]) + 2*(len(self.data) - 2)

    @timer(part=2)
    def solve_part_2(self):
        """Solution for part 2"""
        max_scenic_score = 0
        for row_index in range(1, len(self.data) - 1):
            for col_index in range(1, len(self.data[0]) - 1):
                scenic_score_tree = [0, 0, 0, 0]
                tree = self.data[row_index][col_index]
                # left
                for index in range(col_index - 1, -1, -1):
                    scenic_score_tree[0] += 1
                    if tree <= self.data[row_index][index]:
                        break

                # right
                for index in range(col_index + 1, len(self.data[0])):
                    scenic_score_tree[1] += 1
                    if tree <= self.data[row_index][index]:
                        break

                # up
                for index in range(row_index - 1, -1, -1):
                    scenic_score_tree[2] += 1
                    if tree <= self.data[index][col_index]:
                        break

                # down
                for index in range(row_index + 1, len(self.data[0])):
                    scenic_score_tree[3] += 1
                    if tree <= self.data[index][col_index]:
                        break

                max_scenic_score = max(max_scenic_score,
                                       scenic_score_tree[0] *
                                       scenic_score_tree[1] *
                                       scenic_score_tree[2] *
                                       scenic_score_tree[3])
        return max_scenic_score
