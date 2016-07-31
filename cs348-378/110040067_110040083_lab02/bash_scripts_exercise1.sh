#!/bin/bash

# This is for Exercise1
# for determining the throughput for cbr

sum_cbr=$(grep '^r.*[0-9] 3 cbr.*-.*' simple.tr | awk '{sum_cbr+=$6} END {print sum_cbr}')
time_cbr1=$(grep '^r.*[0-9] 3 cbr.*-.*' simple.tr | head -1 | awk '{time_cbr1=$2} END {print time_cbr1}')
time_cbr2=$(grep '^r.*[0-9] 3 cbr.*-.*' simple.tr | tail -1 | awk '{time_cbr2=$2} END {print time_cbr2}')

# for determining the throughput for tcp

sum_tcp=$(grep '^r.*[0-9] 3 tcp.*-.*' simple.tr | awk '{sum_tcp+=$6} END {print sum_tcp}')
time_tcp1=$(grep '^r.*[0-9] 3 tcp.*-.*' simple.tr | head -1 | awk '{time_tcp1=$2} END {print time_tcp1}')
time_tcp2=$(grep '^r.*[0-9] 3 tcp.*-.*' simple.tr | tail -1 | awk '{time_tcp2=$2} END {print time_tcp2}')


# Printing the output
a=$(echo "($time_cbr2 - $time_cbr1)*1000.0" | bc -l)

echo "The throughput for cbr is :-"
echo "($sum_cbr/$a)" | bc -l
echo

b=$(echo "($time_tcp2 - $time_tcp1)*1000.0" | bc)
echo "The throughput for tcp is :-"
echo "($sum_tcp/$b)" | bc -l
echo

exit 0
