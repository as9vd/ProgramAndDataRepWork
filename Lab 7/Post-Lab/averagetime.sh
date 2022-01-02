#!/bin/bash

# averagetime.sh
# October 27th, 2021
# Asadbek Shamsiev, as9vd@virginia.edu    

# 1. Take in an input; if it's "quit", then terminate.
# 2. Execute program 5 times.
# 3. Take the average of each iteration and print it.

size=5
i=0
array=(1 2 3 4 5)
sum=0

echo "enter the exponent for counter.cpp:"  
read input

if [ "$input" == "quit" ]; then 
	exit 1
fi;

while [[ "$i" -lt size ]]; do 
	((i++))
	echo 'Running iteration' "$i" '...'
	RUNNING_TIME=`./a.out "$input" | tail -1`
	array[i]="$RUNNING_TIME"
	echo 'time taken:' "$RUNNING_TIME" 'ms'
done

arraylength=${#array[@]}

for i in ${array[@]}; do
  let sum+=$i
done

avg=$((sum/size))

echo '5 iterations took' "$sum" 'ms'
echo 'Average time was' "$avg" 'ms'