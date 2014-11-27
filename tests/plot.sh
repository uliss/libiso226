#!/bin/bash

PHON2SPL='@CMAKE_BINARY_DIR@/phon2spl'

function gen_data() {
	seq 20 2 12500 | while read freq
	do
                if [[ $1 -gt 80 && $freq -gt 4000 ]]
                then
                    break
                fi

                printf "%i " $freq
                spl=`$PHON2SPL $1 $freq`
		echo $spl
	done 
}

seq 20 10 90 | while read phon
do
        fname="phon_$phon.txt"
        echo "Writing to $fname"
        rm -rf $fname
        gen_data $phon >> $fname
done

cat "@CMAKE_CURRENT_SOURCE_DIR@/equal_loudness.plot" | gnuplot

