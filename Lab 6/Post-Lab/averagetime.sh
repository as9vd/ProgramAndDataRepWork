#!/bin/bash

# averagetime.sh
# October 19th, 2021
# Asadbek Shamsiev, as9vd@virginia.edu    

# Take in dictionary and grid names. 
# Then run program 5 times, and capture the last line (total time taken).

echo "Enter the dictionary name: "  
read dictionary # https://www.javatpoint.com/bash-read-user-input: very useful resource.
echo "Enter the grid name: "  
read grid

# ./a.out "$dictionary" "$grid"
RUNNING_TIME1=`./a.out "$dictionary" "$grid" | tail -1`

# ./a.out "$dictionary" "$grid"
RUNNING_TIME2=`./a.out "$dictionary" "$grid" | tail -1`

# ./a.out "$dictionary" "$grid"
RUNNING_TIME3=`./a.out "$dictionary" "$grid" | tail -1`

# ./a.out "$dictionary" "$grid"
RUNNING_TIME4=`./a.out "$dictionary" "$grid" | tail -1`

# ./a.out "$dictionary" "$grid"
RUNNING_TIME5=`./a.out "$dictionary" "$grid" | tail -1`

AVERAGE=$((		($RUNNING_TIME1 + $RUNNING_TIME2 + $RUNNING_TIME3 + $RUNNING_TIME4 + $RUNNING_TIME5) / 5		))

echo 'Average is' "$AVERAGE"