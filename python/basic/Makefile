EXTRA_CFLAGS=$(shell python3-config --cflags --ldflags) -lpython3.8 -fPIE

all:
	gcc main.c -o main $(EXTRA_CFLAGS)

run:
	./main

clean:
	rm ./main
