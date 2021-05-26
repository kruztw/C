all:
	gcc -fPIC -shared hook.c -ldl -o hook.so
	gcc simple.c -o simple

run:
	LD_PRELOAD=./hook.so ./simple

clean:
	- rm ./simple ./hook.so

