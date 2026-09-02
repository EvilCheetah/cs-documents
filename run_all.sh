#!/usr/bin/bash

# Reference: https://stackoverflow.com/questions/8880603

directories=(
    Example
    Merge
    Quick
    Bubble
    Insertion
    Selection
    Statistics
    Transpose
    Histogram
)

for directory in "${directories[@]}"; do
    (
        cd "${directory}"
        ./run-tests.sh
    ) &
done

wait

