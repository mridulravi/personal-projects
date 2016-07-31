#!/bin/bash

for files in test_files/*.cfg
do
	echo "Generating OUR icode for $files"
	./cfglp -program -d $files > "$files"_our
	echo "Generating SIR icode for $files"
	./cfglp64 -program -d $files > "$files"_sir
	echo "Comparing icode for $files"
	diff -bB "$files"_our "$files"_sir
	echo "//////////////////////////////////////////////////////////////////////////////////////////"
done

