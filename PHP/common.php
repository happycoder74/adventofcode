<?php
namespace Common;

$datadir = "../data";

function get_data($fn, $year, $day) {
    $filename = "../data/$year/" . str_pad($day, 2, "0", STR_PAD_LEFT) . "/$fn";
	$fp = fopen($filename, "r");
	$data = array_map('trim', file($filename, FILE_IGNORE_NEW_LINES));

	return $data;
}

function timer($function, $args, $part, $title=NULL, $show_return=True) {
    $starttime = microtime(true);
    $result = call_user_func_array($function, $args);
    $elapsed = microtime(true) - $starttime;
    $unit = "s";
    if ($elapsed < 0.1) {
        $elapsed = $elapsed * 1000;
        $unit = "ms";
    }
    if (! $title) {
        print("Part " . $part . " answer: " . $result);
        printf("\r\033[35C( %6.3f %-2s )\n", $elapsed, $unit);
    }
}

?>
