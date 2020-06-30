#!/bin/bash
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
ps ux | grep isg2_db | grep -v grep | awk '{print $2}' | xargs -I^ kill -9  ^
case "$1" in
    "c" | "C" | "clean" | "Clean" ) rm -rf ../log/* ; rm -f core core.* ;;
    * ) ;;
esac
./isg2_db ../conf/bench.conf ../bin/libdb.so
#cd ../../db1/src/
#./isg2_db ../conf/bench.conf ../bin/libdb.so
#cd ../../db/src/
