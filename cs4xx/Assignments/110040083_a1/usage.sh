#!/bin/bash

PREV_TOTAL=0		# Selecting arbitarily as 0: will neglect the first observation as PREV_TOTAL may not be 0
PREV_IDLE=0			# Selecting arbitarily as 0: will neglect the first row as PREV_TOTAL may not be 0

while true; do

  #  0      1		2		3     4       5     6	   7        8      9       10
  # cpu    user    nice   system  idle   iowait irq   softirq  steal  guest  guest_nic
  
  CPU=(`cat /proc/stat | grep '^cpu '`) # Get the total CPU statistics.
  unset CPU[0]                          # Discard the "cpu" prefix.
  
  
  # Get the idle CPU time = idle + iowait
  IDLE=0					            
  for VALUE in "${CPU[@]:4:5}"; do
    let "IDLE=$IDLE+$VALUE"
  done
  
  
  # Calculate the total CPU time =  user + nice + system + idle + iowait + irq + softirq + steal 
  TOTAL=0
  for VALUE in "${CPU[@]:1:8}"; do
    let "TOTAL=$TOTAL+$VALUE"
  done


  # Calculate the CPU usage since we last checked.
  let "DIFF_IDLE=$IDLE-$PREV_IDLE"
  let "DIFF_TOTAL=$TOTAL-$PREV_TOTAL"
  let "DIFF_USAGE=(1000*($DIFF_TOTAL-$DIFF_IDLE)/$DIFF_TOTAL+5)/10"
  
  echo "$DIFF_USAGE" | awk '{x="'"`date +%H:%M:%S.%N`"'"; printf "%s %s\n",x,$0 }'
  
  # %H - current hour
  # %M - current minute
  # %S - current seconds
  # %S - current seconds(in nanoseconds)

  # Remember the total and idle CPU times for the next check.
  PREV_TOTAL="$TOTAL"
  PREV_IDLE="$IDLE"

  # Wait for 1 second before checking again.
  sleep 1
done
