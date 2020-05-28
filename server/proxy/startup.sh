#!/bin/bash
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:../bin
ps ux | grep "./isg2_proxy ./bench.lua" | grep -v grep | awk '{print $2}' | xargs -I^ kill -9 -^
case "$1" in
    "c" | "C" | "clean" | "Clean" ) rm -rf log/* ; rm -rf core.*;;
    * ) ;;
esac
./isg2_proxy ./bench.lua
