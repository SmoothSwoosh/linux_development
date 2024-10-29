#!/bin/bash

if [ -n "$1" ]; then
    delay=$1
else
    delay=0
fi

mapfile -t array < /dev/stdin

rows=${#array[@]}

tput clear

positions=()
for row in $(seq 0 ${#array[@]}); do
    cols=$(echo -n "${array[$row]}" | wc -c)
    for col in $(seq 0 $cols); do
        positions+=("$row,$col")
    done
done

positions=($(shuf -e "${positions[@]}"))

for position in ${positions[@]}; do
    row=${position%,*}
    col=${position#*,}
    symbol=${array[$row]:$col:1}
    tput cup $row $col
    echo -n $symbol
    sleep $delay
done

tput cup $rows 0