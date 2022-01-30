<?php
include_once 'common.php';


function solve_part_1($data) {
    $inc = 0;
    for ($i = 1; $i < count($data); $i++) {
        if ($data[$i] > $data[$i - 1]) {
            $inc++;
        }
    }
    return $inc;
}

function solve_part_2($data) {
    $inc = 0;
    for ($i = 3; $i < count($data); $i++) {
        if ($data[$i] > $data[$i - 3]) {
            $inc++;
        }
    }
    return $inc;
}


function main2($filename) {
    $data = \Common\get_data($filename, 2021, 1);
    \Common\timer('solve_part_1', [$data], 1);
    \Common\timer('solve_part_2', [$data], 2);
}

function main($filename) {

    $data = get_data($filename, 2021, 1);

    $start_time = microtime(true);
    $res_1 = solve_part_1($data);
    $time_1 = microtime(true) - $start_time;
    $unit_1 = "s";
    if ($time_1 < 0.1) {
        $time_1 *= 1000;
        $unit_1 = "ms";
    }

    $start_time = microtime(true);
    $res_2 = solve_part_2($data);
    $time_2 = microtime(true) - $start_time;
    if ($time_2 < 0.1) {
        $time_2 *= 1000;
        $unit_2 = "ms";
    }

    print("Part 1 answer: " . $res_1);
    printf("\033[25C( %6.3f %s )\n", $time_1, $unit_1);
    print("Part 2 answer: " . $res_2);
    printf("\033[25C( %6.3f %s )\n", $time_2, $unit_2);

}

if ($argc > 1) {
    $fn = $argv[1];
} else {
    $fn = "input.txt";
}

main2 ($fn);

?>
