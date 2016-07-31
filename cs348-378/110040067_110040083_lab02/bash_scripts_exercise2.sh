#!/bin/bash

# This is for exercise 2 all parts

sum=$(grep '^+.*0 [0-9].*-.*' udp-160k.tr | awk '{sum+=$6} END {print sum}') 
time1=$(grep '^+.*0 [0-9].*-.*' udp-160k.tr | head -1 | awk '{time1=$2} END {print time1}')
time2=$(grep '^+.*0 [0-9].*-.*' udp-160k.tr | tail -1 | awk '{time2=$2} END {print time2}')

a=$(echo "($time2 - $time1)" | bc)
b=$(echo "($sum/$a)" | bc -l)
c=$(echo "($b/1000.0)" | bc -l )
d=$(echo "($c*8)" | bc -l)

echo "The data rate is $d kbps"

################### Part (a) is complete 

abhi=$(grep '^+.*0 [0-9].*-.*' udp-160k.tr | wc -l | awk '{print $1}')
abhishek=$(grep '^d .*' udp-160k.tr | wc -l | awk '{print $1}')

e=$(echo "($abhishek*100.0/$abhi)" | bc -l)
echo "The packet loss in percentage is $e"

################### Part (b) is complete

grep '^+.*0 [0-9].*-.*' udp-160k.tr > temp_enqueue
grep '^r.*[0-9] 2.*-.*' udp-160k.tr > temp_received

#line_no=$(grep '^r.*[0-9] 2.*-.*' udp-160k.tr | wc -l | awk '{print $1}')

while read line
do
	#echo $line
	var=$(echo $line | awk '{print $11}')
	array[$var]=$(echo $line | awk '{print $2}')
	#echo ${array[$var]}
done < temp_received

while read line1
do
	var=$(echo $line1 | awk '{print $11}')
	if [ -z "${array[$var]}" ]
	then
		continue
	else
		var1=$(echo $line1 | awk '{print $2}')
		array[$var]=$(echo "(${array[$var]}-$var1)" | bc -l)
#		echo ${array[$var]}
	fi
done < temp_enqueue

sum=0
j=0

for i in "${array[@]}"
do
	sum=$(echo "($sum+$i)" | bc -l)
	j=$(echo "($j+1)" | bc -l)
done

value=$(echo "($sum*1000/$j)" | bc -l)

echo "The average delay is $value ms"

##########################part (C) is completed

time_through1=$(cat temp_received | head -1 | awk ' {print $2} ')
time_through2=$(cat temp_received | tail -1 | awk ' {print $2} ')
sum_through=$(cat temp_received | awk '{summ+=$6} END {print summ} ')

temp1=$(echo "($time_through2-$time_through1)" | bc -l)
temp2=$(echo "($temp1*1000)" | bc -l)
throughput=$(echo "($sum_through*8/$temp2)" | bc -l)

#throughput=$(echo "($sum_through*0.001*8/($time_through2-$time_through1))" | bc -l)

echo "The throughput is $throughput kbps"

rm -f temp_received temp_enqueue

exit 0
