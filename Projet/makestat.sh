#! /bin/bash

dim=10
strat=1

while [ $dim -le 200 ]; do
    while [ $strat -le 5 ]; do
	echo -n "$dim " >> "stat/0${strat}_cpu"
	./interface $dim $dim 1 1 <<< "0 $strat" |
	    tail -n1 | cut -d':' -f2 >> "stat/0${strat}_cpu"
	echo -n "$dim " >> "stat/0${strat}_coups"
	./interface $dim $dim 1 1 <<< "0 $strat" |
	    tail -n2 | head -n1 | cut -d':' -f2 >> "stat/0${strat}_coups"
	strat=$((strat+1))
    done
    strat=1
    dim=$((dim+10))
    echo $dim
done

cd stat
mv 01_cpu 01_rec_cpu.txt
mv 01_coups 01_rec_coups.txt
mv 02_cpu 02_imp_cpu.txt
mv 02_coups 02_imp_coups.txt
mv 03_cpu 03_rapide_cpu.txt
mv 03_coups 03_rapide_coups.txt
mv 04_cpu 04_maxbordure_cpu.txt
mv 04_coups 04_maxbordure_coups.txt
mv 05_cpu 05_diagonale_cpu.txt
mv 05_coups 05_diagonale_coups.txt

gnuplot < makestat_cpu.txt
gnuplot < makestat_coups.txt
