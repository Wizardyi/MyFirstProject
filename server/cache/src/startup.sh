export LD_LIBRARY_PATH=./bin:$LD_LIBRARY_PATH
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
ps ux | grep yzxa_cache | grep -v grep | awk '{print $2}' | xargs -I^ kill -9 ^
case "$1" in
    "c" | "C" | "clean" | "Clean" ) rm -rf ../log/* ; rm -rf core.*;;
    * ) ;;
esac
./yzxa_cache ../conf/bench.conf
