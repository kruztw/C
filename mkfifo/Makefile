all:
	gcc reader.c -o reader -g
	gcc writer.c -o writer -g

run:
	./writer &
	./reader

clean:
	- rm copy_file reader writer 
