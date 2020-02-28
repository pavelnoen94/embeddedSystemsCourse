#!/bin/bash

echo "Process ID: $$" | cowsay
rm sanntidAktiveIP.log

echo -n "Lower ping limit? (10.100.23.L): "
read ans 

for ((i = $ans ; i < 255 ; i++)); do
    if sudo ping -c 1 10.100.23.$i -W 1 2>&1 | awk -F'/' 'END{ print (/^rtt/? "OK "$5" ms":"FAIL") }' | grep OK > /dev/null; then
        printf "10.100.23.$i\n" >> sanntidAktiveIP.log
        printf "Response from: 10.100.23.$i\n"
    fi
done
