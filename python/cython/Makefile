EXTRA_CFLAGS=$(shell python3-config --cflags --ldflags) -lpython3.8 -fPIE

all:
	python3 setup.py build_ext --inplace
	gcc main.c simple.c -o main $(EXTRA_CFLAGS)

init:
	pip3 install cython

run:
	./main

clean:
	rm ./main *.so build __pycache__ simple.h simple.c -rf
