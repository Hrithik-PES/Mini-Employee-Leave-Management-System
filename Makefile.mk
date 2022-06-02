output: CLIENT.o SERVER.o
	gcc CLIENT.o SERVER.o -o  output
CLIENT.o: CLIENT.c
	gcc -c CLIENT.c
SERVER.o: SERVER.c SERVER.h
	gcc -c SERVER.c 
clean:
	rm *.o output

