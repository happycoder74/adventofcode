<?php
require ('common.php');
use function \Common\get_data; 

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


function main($filename) {
    $data = get_data($filename, 2021, 1);
    $part_1 = \Common\timer('solve_part_1', [$data], 1);
    $part_2 = \Common\timer('solve_part_2', [$data], 2);

    return [$part_1, $part_2];
}


if ($argc > 1) {
    $fn = $argv[1];
} else {
    $fn = "input.txt";
}

$result = \Common\timer('main',  [$fn], 0);

?>
