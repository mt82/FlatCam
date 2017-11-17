#!/bin/bash

function get_LFSR {

	nreg=${1}

	wget "https://users.ece.cmu.edu/~koopman/lfsr/${nreg}.txt" -O tmp.txt 2> /dev/null

	string="int LSFR_${1}[]={"

	while read p; do
		string="${string}0x$p, "
	done < tmp.txt

	string="${string}}"

	echo ${string}

	rm tmp.txt
}

for i in `seq 4 15`; do
	get_LFSR $i;
done;
