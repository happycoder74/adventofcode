<?php
use \Common\get_data as get_data;

function solve_part_1($data) {
    return NULL;
}

function solve_part_2($data) {
    return NULL;
}

function main($filename) {
    $data = get_data($filename, <YEAR>, <DAY>);
    $part_1 = \Common\timer('solve_part_1', [$data], 1);
    $part_2 = \Common\timer('solve_part_2', [$data], 2);

    return [$part_1, $part_2];
}

if ($argc > 1) {
    $fn = $argv[1];
} else {
    $fn = "input.txt";
}

$result = \Common\timer('main', [$fn], 0);

?>
