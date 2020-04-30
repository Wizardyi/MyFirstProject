all:
	g++ -o test.o -c test.cpp -I../src -I../../../proto/isg/ -I../../../proto/db/ -I../../../proto/share/ -I../../ `pkg-config --cflags --libs protobuf` -L../../../proto/isg -lisgproto -L../../../proto/share/ -lshareproto -L../../../proto/online/ -lonlineproto -L../../../proto/db/ -ldbproto -ltaomee -ltaomee++ -g
	##g++ -o do_test do_test.cpp test.o -I../../../proto/share/ -I../src -I../../ `pkg-config --cflags --libs protobuf` -L../../../proto/login/ -lloginproto -L../../../proto/online/ -lonlineproto -L../../../proto/home/ -lhomeproto -lcacheproto -L../../../proto/cache/ -L../../../proto/share/ -lshareproto -L../../../proto/scene/ -lsceneproto -ltaomee -ltaomee++ -g
	g++ -o EncodeDecode.o -c ../../../share/EncodeDecode.cpp -I../src -I../../../proto/isg/ -I../../../proto/db/ -I../../../proto/share/ -I../../ `pkg-config --cflags --libs protobuf` -L../../../proto/isg -lisgproto -L../../../proto/share/ -lshareproto -L../../../proto/online/ -lonlineproto -L../../../proto/db/ -ldbproto -ltaomee -ltaomee++ -g
	g++ -o do_test do_test.cpp test.o EncodeDecode.o -I../../../proto/isg/ -I../../../proto/db/ -I../../../proto/share/ -I../src -I../../ `pkg-config --cflags --libs protobuf` -L../../../proto/login/ -lloginproto -L../../../proto/online/ -lonlineproto -lcacheproto -L../../../proto/cache/ -L../../../proto/share/ -lshareproto -L../../../proto/db/ -ldbproto -L../../../proto/isg -lisgproto  -ltaomee -ltaomee++ -g
# g++ -o test_proto test_proto.cpp test.o -I../src -I../../ `pkg-config --cflags --libs protobuf` -L../../../proto/online/ -lonlineproto -ltaomee -ltaomee++ -g
#	g++ -o test_package test_package.cpp ../src/package.cpp -I../src -I../../ `pkg-config --cflags --libs protobuf` -L../../../proto/online/ -lonlineproto -ltaomee -ltaomee++ -g
clean:
	rm -rf do_test *.o
