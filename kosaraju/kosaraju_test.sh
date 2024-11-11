#!/bin/bash

kosaraju=./kosaraju.bin

echo "Testando algoritmo de Kosaraju"
for i in instances_scc/*.dat
do
	echo -e "\e[33mInstância $i\e[0m";
	$kosaraju -f $i | ./ordena.sh > temp;

	j=$(basename $i);
	diff -w temp ./scc/$j > /dev/null ;
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mErro\e[0m";
	fi
	rm temp;

done