#!/bin/bash

cd /tmp
rm -rf embeddedSystemsCourse
git clone https://github.com/pavelnoen94/embeddedSystemsCourse.git
cd embeddedSystemsCourse/elevator
git checkout elevator
make &> compiler.log
cat compiler.log
