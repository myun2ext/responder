all:
	g++ -O3 test.cpp -I ../../ -o serv
win:
	g++ -O3 test.cpp -l Ws2_32 -I ../../ -o serv
