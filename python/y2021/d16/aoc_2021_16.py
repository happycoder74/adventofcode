import sys
from common import timer, get_input


def clean_input(data):
    return data[0]


def read_packet(packet, debug=False):
    version = int(packet[0:3], 2)
    packet = packet[3:]
    packet_type = packet[:3]
    if debug:
        print(f"{version=}")
        print(f"{packet_type=}")
    packet = packet[3:]
    if packet_type != '100':
        lenid = packet[:1]
        if debug:
            print(f"{lenid=}")
        packet = packet[1:]
        if lenid == '0':
            packet_length = int(packet[:15], 2)
            if debug:
                print(f"{packet_length=}")
            packet = packet[15:]
            vers, pack = read_packet(packet[:packet_length])
            version += vers
            if debug:
                print(f"{len(pack)=}")
            while (len(pack) > 4):
                vers, pack = read_packet(pack)
                version += vers
            packet = packet[packet_length:]
        elif lenid == '1':
            npackets = packet[:11]
            packet = packet[11:]
            for n in range(int(npackets, 2)):
                vers, packet = read_packet(packet)
                version += vers
    if packet_type == '100':
        group = packet[:5]
        packet = packet[5:]
        while (group[0] == '1'):
            group = packet[:5]
            packet = packet[5:]
    return version, packet


@timer(part=1)
def solve_part_1(data):
    """Solution for part 1"""
    packet = bin(int(data, 16))[2:]
    if len(packet) % 4 > 0:
        packet = '0'*(4 - len(packet) % 4) + packet
    version, packet = read_packet(packet)
    return version


@timer(part=2)
def solve_part_2(data):
    """Solution for part 2"""
    return None


@timer(part='main', title='Total elapsed', show_return=False)
def main(filename):
    data = clean_input(get_input(filename, 2021, 16))

    part1 = solve_part_1(data)
    part2 = solve_part_2(data)

    return part1, part2


if __name__ == "__main__":
    filename = "input.txt"
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    main(filename)
