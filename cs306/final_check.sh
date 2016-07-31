#!/bin/bash
# untar the file and change to respective directory
tar xf $1
dir_name=`echo $1 | cut -d'.' -f1`
cd ./$dir_name/


#Check whether CodeOfHonour and MYCHANGES file exist or not
test -f CodeOfHonour && echo "CodeOfHonour file Found" || echo "CodeOfHonour file Not found"

test -f MYCHANGES && echo "MYCHANGES file Found" || echo "MYCHANGES file Not found"

#make the cfglp executable
echo "making the cfglp executable"
make -f Makefile.cfglp

#removing already existing files in test_files directory
#echo "removing already existing files in test_files directory"
#cd ./test_files/
#rm *
#cd ..

#copy the .cfg and .ecfg files available in test_files directory provided with script intest_files directory of submision.
#These are the actual test cases which we have to grade
#echo "copying actual test files"
#cd ..
#cp -r ./test_files/*.*cfg ./$dir_name/test_files
#cd ./$dir_name

echo "Generating .toks files"
#now genrate the .toks file for each test case
cd ./test_files/
rm output.txt

shopt -s nullglob
for f in *.cfg
do
../cfglp64 -tokens $f
done

#Find the diff of .toks file generated in previous step with respective .toks file provided with script
#and store the output of diff command in output.txt file.
echo "finding diff of tokes files"
for f in *.toks
do
sed -i 's/Token Code: -\?[0-9][0-9]*/Token Code: /g' $f
file_name=`echo $f | cut -d'.' -f 1`
echo "diff for file name "$file_name>> output.txt
diff -b -B -d ../../test_files/$f $f >>output.txt
echo "" >>output.txt
echo "" >>output.txt
done

#see the content of output.txt for the diff
gedit output.txt &

#echo "************************************"
#echo "Executing cglp for invalid input"
#echo "If for a file, output is PASS that means succefully found error in input code"
#echo "If output is FAIL, error in finding error"

#if error message for an invalid test case contains "error" word, parsing is correct
#shopt -s nullglob
#for f in *.ecfg
#do
#op_msg=`../cfglp $f 2>&1` 
#echo ""
#echo "file name is:" $f
#echo $op_msg | grep "error" > /dev/null
#op=`echo $?`
#if [ $op -eq 0 ]
#then
#	echo "PASS"
#else
#	echo "FAIL"
#fi
#done

