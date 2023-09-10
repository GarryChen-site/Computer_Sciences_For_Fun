#! /bin/bash

# make 
# cd ../
make clean
make
mytsh_result="./tshres/tshmy.txt"   
tshref_result="./tshres/tshref.txt"
truncate $mytsh_result --size 0 
truncate $tshref_result --size 0 
echo -e "testing...\n"

for i in {9..9}; do
    t=""
    if [ $i -ge 10 ]; then t="$i"
    else t="0$i"
    fi
    # echo -e "./sdriver.pl  -t trace$t.txt -s ./tsh -a \"-p\"" >> mytsh_result
    ./sdriver.pl  -t trace$t.txt -s ./tsh -a "-p" >> "$mytsh_result"
    ./sdriver.pl  -t trace$t.txt -s ./tshref -a "-p" >> $tshref_result
done

diff $tshref_result $mytsh_result   > ./tshres/tshdiff