#!/bin/bash

eval "sudo apt update";
while read line; do
	eval "(sudo apt install $line -y)";

done < requirements.txt
