#!/bin/bash

usage() { echo "$0 usage:" && grep " .)\ " $0; exit 0; }

current_day=$(date +%d)
current_year=$(date +%Y)
year=$current_year
day=$current_day
install_path="$HOME/projects/adventofcode"
force=0
templates_only=0
input_only=0
silent=0

declare -a languages=("python" "C" "PHP")

while getopts ":hd:y:i:fl:c:tos" arg; do
    case $arg in
        y) # Specify year to download
            year=${OPTARG}
            ;;
        d) # Specify day to download
			day=$(printf "%02d" $((10#${OPTARG})))
            ;;
        c) # Specify alternative cookie file (with path)
            cookiefile=${OPTARG}
            ;;
        i) # specify install path (default path is $HOME/projects/adventofcode)
            install_path=${OPTARG}
            ;;
        f) # Force download if input data already exists
            force=1
            ;;
        l) # Specify language for template
			langspec=${OPTARG}
			if [[ ! " ${languages[*]} " =~ " $langspec " ]]; then
				echo "Language $langspec not yet supported"
				exit 1
			fi
			;;
        s) # Silent mode. No output
			silent=1
			;;
        t) # Make templates only
			templates_only=1
			;;
        o) # Download input only
			input_only=1
			;;
        h) # Display help.
            usage
            exit 0
            ;;
    esac
done

check_dates() {
	if [ $year -lt 2015 -o $year -gt 2021 ]; then
		if [ $silent -eq 0 ]; then
			echo "year must be between 2015 and 2021"
		fi
		exit 1
	fi
	if [ $day -lt 1 -o $day -gt 25 ]; then
		if [ $silent -eq 0 ]; then
			echo "day must be between 1 and 25"
		fi
		exit 1
	fi
	if [ $year -ge $current_year ]; then
		if [ -a $day -gt $current_day ]; then
			if [ $silent -eq 0 ]; then
				echo "Can not download day $day for $year yet."
			fi
			exit 1
		fi
	fi
}

download_input() {
	data_directory="$install_path/data/$year/$day"
	if [ ! -v cookiefile ]; then
		cookiefile="$install_path/.cookie"
	fi

	# Create directory and data_directory if they do not already exist
	[ -d $directory ] || ( mkdir -p $directory)
	[ -d $data_directory ] || ( mkdir -p $data_directory )

	if [ -e "$data_directory/input.txt" -a $force -eq 0 -a $templates_only -eq 0 ]; then
		if [ $silent -eq 0 ]; then
			echo "Puzzle input exists. Add option -f to force download" 
		fi
		return 
	fi

	if [ ! -e $cookiefile ]; then 
		if [ $silent -eq 0 ]; then
			echo "No cookiefile found, unable to download"
		fi
		exit 1
	fi

	curl --insecure -o "$data_directory/input.txt" --cookie "session=$(cat $cookiefile)" https://adventofcode.com/$year/day/$((10#$day))/input
}


make_templates() {
	language=$1
	case $language in
		python)
			file_ext=py
			;;
		C)
			file_ext=c
			;;
		PHP)
			file_ext=php
			;;
		*)
			if [ $silent -eq 0 ]; then
				echo "Templates for $language is not yet defined"
			fi
			;;
	esac

	[ $silent -eq 0 ] && echo "Creating start templates for $language"

	directory="$install_path/$language/$year/$day"
	template_dir="$install_path/templates/$language"
	if [ ! -e $directory ]; then
		mkdir -p $directory
	fi
	if [ ! -e $directory/aoc_${year}_${day}.${file_ext} ]; then
		sed -e "s/<YEAR>/$year/g" -e "s/<DAY>/$((10#$day))/g" $template_dir/aoc_year_day.${file_ext} > $directory/aoc_${year}_${day}.${file_ext}
	fi

	if [ $language == "python" ]; then
		if [ ! -e $directory/test_aoc_${year}_${day}.$file_ext ]; then
			sed -e "s/<YEAR>/$year/g" -e "s/<CORR_DAY>/$((10#$day))/g" -e "s/<DAY>/$day/g" $template_dir/test_aoc_year_day.${file_ext} > $directory/test_aoc_${year}_${day}.${file_ext}
		fi
	fi
}

check_dates

if [ $templates_only -eq 0 ]; then 
	download_input
fi

if [ $input_only -eq 0 ]; then
	if [ -z $langspec ]; then
		for lang in "${languages[@]}"; do 
			make_templates $lang
		done
	else
		if [[ " ${languages[*]} " =~ " $langspec " ]]; then
			make_templates $langspec
		else
			[ $silent -eq 0 ] && echo "Language $langspec not yet supported"
		fi
	fi
fi
