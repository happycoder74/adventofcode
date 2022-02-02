import sys
import pandas as pd
from common import timer, get_input


def clean_input(data):
    data = [[int(n) for n in line] for line in data]
    return data


def extend_map(df):
    df = pd.concat([df, df.iloc[-2].to_frame().T])
    df.insert(len(df.columns), len(df.columns), df.iloc[:, -2])
    df.insert(0, -1, df.loc[:, 1])
    df.reset_index(inplace=True, drop=True)
    df.loc[-1] = df.loc[1]
    df.index += 1
    df = df.sort_index()
    return df


def get_left(df):
    left = df - df.shift(-1, axis=1)
    return left


def get_right(df):
    right = df - df.shift(1, axis=1)
    return right


def get_up(df):
    up = df - df.shift(-1)
    return up


def get_down(df):
    down = df - df.shift(1)
    return down


def get_low_points(df):
    df2 = extend_map(df)
    left = get_left(df2)
    right = get_right(df2)
    up = get_up(df2)
    down = get_down(df2)
    mask = (left < 0) & (right < 0) & (up < 0) & (down < 0)
    df_result = df2[mask].iloc[1:-1, 1:-1].reset_index(drop=True)

    low_points = []
    for index, row in df_result.iterrows():
        for col_index, value in enumerate(row):
            if pd.notna(value):
                low_points.append((index, col_index))

    return low_points


def find_basin(point, df, v_list):
    basin_size = 1

    for neighbour in neighbours(point, df):
        if neighbour not in v_list:
            v_list.append(neighbour)

            if df.iloc[neighbour[0], neighbour[1]] != 9:
                basin_size += find_basin(neighbour, df, v_list)

    return basin_size


def neighbours(point, df):
    row = point[0]
    col = point[1]

    neighbour_list = []
    if row - 1 >= 0:
        neighbour_list.append((row - 1, col))
    if row + 1 < len(df.index):
        neighbour_list.append((row + 1, col))
    if col - 1 >= 0:
        neighbour_list.append((row, col - 1))
    if col + 1 < len(df.columns):
        neighbour_list.append((row, col + 1))

    return neighbour_list


def print_map(df, low_points=None):
    print("".join(["\u2593" for i in range(-1, df.shape[1] + 1)]))
    for row in range(0, df.shape[0]):
        line = ["#" for i in range(0, df.shape[1])]
        for col in range(0, df.shape[1]):
            tup = (row, col)
            if df.iloc[row, col] != 9:
                line[col] = " "
            if low_points is not None:
                if tup in low_points:
                    line[col] = "O"
        print("".join(["\u2593"] + line + ["\u2593"]))
    print("".join(["\u2593" for i in range(-1, df.shape[1] + 1)]))
    print()


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    df = pd.DataFrame(data)

    df = pd.concat([df, df.iloc[-2].to_frame().T])
    df.insert(len(df.columns), len(df.columns), df.iloc[:, -2])
    df.insert(0, -1, df.loc[:, 1])
    df.reset_index(inplace=True, drop=True)
    df.loc[-1] = df.loc[1]
    df.index += 1
    df = df.sort_index()

    left = (df - df.shift(-1, axis=1)) < 0
    right = (df - df.shift(1, axis=1)) < 0
    up = (df - df.shift(-1)) < 0
    down = (df - df.shift(1)) < 0

    mask = left & right & up & down

    df_result = (df[mask] + 1)
    return df_result.sum().sum()


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    df = pd.DataFrame(data)
    visited = []
    basin_list = []

    lp = get_low_points(df)
    print_map(df, lp)

    for index, point in enumerate(lp):
        visited.append(point)
        basin_list.append(find_basin(point, df, visited))

    basin_list.sort(reverse=True)
    return basin_list[0] * basin_list[1] * basin_list[2]


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2021, 9))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
