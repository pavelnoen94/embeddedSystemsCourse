#!/bin/bash

eval "sudo apt update";
while read line; do
	eval "(sudo apt install $line -y)";

done < requirements.txt

# Whitelist this repository. Makes gdb read .gdbinit file in this directory
echo -e -n 'add-auto-load-safe-path ' >> ~/.gdbinit
pwd >> ~/.gdbinit
echo -e -n "/../" >> ~/.gdbinit
