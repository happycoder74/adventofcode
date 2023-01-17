#!/usr/bin/env bash

YEARS=$(ls -d 2*)
DAY_START=1
DAY_END=25
current_day=$(date +%d)
current_year=$(date +%Y)
year=$current_year
day=$current_day

usage() {
    echo "Runner script for C-based AdventOfCode solutions"
    echo ""
    echo "Usage runner [ -t | --test ]
             [ -h | --help ]
             [ -y | --year YEAR ] 
             [ -d | --day DAY ]
             [ -f | --file FILENAME]"
    echo ""
    echo "   -h, --help                  Display this help text"
    echo "   -t, --test                  Run test case (default input file = test_input.txt)"
    echo "   -f, --file FILENAME         Run using FILENAME as input file"
    echo "   -y, --year YEAR[,YEAR2,...] Run YEAR or multiple years as comma separated list"
    echo "   -d, --day DAY[,DAY2,...]    Run DAY or multiple days as comma separated list"
    echo ""
    echo "If no options are specified, current day and current year is run using problem input (input.txt)"
    echo "If -y YEAR is specifed but not -d, all available days in YEAR will be processed."
    exit 2
}

run_case() {
    if [ x$YEAR == "x" ]; then
        YEARS=$current_year
    else
        YEARS=($(echo $YEAR|tr "," " "))
    fi

    if [ x$DAY == "x" ]; then
        DAYS=$current_day
    else
        DAYS=($(echo $DAY|tr "," " "))
    fi

    for year in ${YEARS[@]}
    do
        for day in ${DAYS[@]}
        do
            day_zero_pad=$(printf "%02d" $day)
            make run YEAR=$year DAY=$day_zero_pad
        done
    done
}

check_platform() {
    [ $(uname) == "FreeBSD" ]
}


get_arguments() {
    PARSED_ARGUMENTS=$(getopt -a -n runner -o -:d:f:hty --long test,help,year:,day:,file: -- "$@")
    VALID_ARGUMENTS=$?
    if [ "$VALID_ARGUMENTS" != "0" ]; then
        usage
    fi

    #echo "PARSED_ARGUMENTS is $PARSED_ARGUMENTS"
    eval set -- "$PARSED_ARGUMENTS"

    while :
    do
    case $1 in
        -h | --help)
            usage
            break;;
        -d | --day)
            DAY=$2
            shift 2
            ;;
        -y | --year)
            YEAR=$2
            shift 2
            ;;
        --)
            shift
            break
            ;;
        *) 
            echo "Unknown option $1!"
            echo ""
            usage
            ;;
    esac
    done
}

if [ check_platform ]
then
    get_arguments $@
    run_case
else
    echo "Runner script is not supported on $(uname)"
    echo "Use make run YEAR=<YEAR> DAY=<DAY> instead"
fi


