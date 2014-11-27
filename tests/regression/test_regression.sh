#!/bin/bash

SAMPLE_DATA='@CMAKE_CURRENT_SOURCE_DIR@/sample_phon2spl.txt'

echo "GENERATING data"

NEW_DATA="@CMAKE_CURRENT_BINARY_DIR@/new_phon2spl.txt"
sh "@CMAKE_CURRENT_BINARY_DIR@/gen_regression_data.sh" $NEW_DATA

diff $SAMPLE_DATA $NEW_DATA


