#! /bin/bash

dim=200
strat=3

while [ $dim -le 500 ]; do
    #while [ $strat -le 5 ]; do
	echo -n "$dim " >> "stat/rapide_bis"
	./interface $dim $dim 1 1 <<< "0 $strat" |
	    tail -n1 | cut -d':' -f2 >> "stat/rapide_bis"
	echo -n "$dim " >> "stat/rapide_bis"
	./interface $dim $dim 1 1 <<< "0 $strat" |
	    tail -n2 | head -n1 | cut -d':' -f2 >> "stat/rapide_bis"
	#strat=$((strat+1))
    #done
    #strat=1
    dim=$((dim+50))
    echo $dim
done

#gnuplot < makestat_cpu.txt
#gnuplot < makestat_coups.txt
