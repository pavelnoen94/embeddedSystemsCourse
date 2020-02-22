#!/bin/bash
while inotifywait -e modify source/* ;
do make;
done
