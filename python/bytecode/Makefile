# platform: MacOS

all:
	g++ -fpie `python3-config --cflags --embed` -o simple simple.cpp `python3-config --embed --ldflags` --std=c++11

clean:
	rm -rf ./simple ./simple.dSYM || true
