#!/bin/bash
while inotifywait -e modify source/* ;
do clear; make;
done
