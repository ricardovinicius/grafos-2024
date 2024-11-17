#!/bin/bash

fw=./fw

echo "Testando algoritmo de Floyd Warshall"
for i in instances/*.txt
do
	echo -e "\e[33mInstância $i\e[0m";
	$fw -f $i > temp;

	j=$(basename $i);
	diff -w temp ./solutions/$j > /dev/null ;
	if [ $? -eq 0 ]; then
		echo -e "\e[32mOK\e[0m"
	else
		echo -e "\e[31mErro\e[0m";
	fi
	rm temp;

done