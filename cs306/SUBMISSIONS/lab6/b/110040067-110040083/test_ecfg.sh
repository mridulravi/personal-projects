#!/bin/bash

for files in test_files/*.ecfg
do
	echo "Generating OUR icode for $files"
	./cfglp -icode -lra $files 
	echo "Generating SIR icode for $files"
	./cfglp64 -icode -lra $files 
	echo "//////////////////////////////////////////////////////////////////////////////////////////"
done

