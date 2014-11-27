#!/bin/bash

PHON2SPL='@CMAKE_BINARY_DIR@/phon2spl'
SPL2PHON='@CMAKE_BINARY_DIR@/spl2phon'

function gen_phon2spl_data() {
        seq 20 50 12000 | while read freq
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

function gen_spl2phon_data() {
        seq 20 2 12500 | while read freq
        do
                seq 20 3 120 | while read spl
                do
                    printf "%i " $freq
                    phon=`$SPL2PHON $1 $freq`
                    echo $phon
                done
        done
}

spl_fname="@CMAKE_CURRENT_SOURCE_DIR@/sample_phon2spl.txt"
rm -rf $spl_fname

seq 20 4 90 | while read phon
do
        echo "$phon phon"
        echo "# $phon phon" >> $spl_fname
        gen_phon2spl_data $phon >> $spl_fname
done


