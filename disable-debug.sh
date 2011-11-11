#!/bin/bash
SED=`which sed`
$SED s/"-D__DEBUG__"/""/ Makefile > Makefile.tmp
mv Makefile.tmp Makefile
make clean
echo "done"
