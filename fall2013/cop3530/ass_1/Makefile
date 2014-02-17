
# Name: Maksim Levental 

# UF ID: 3186-7826 

# Gator ID: mlevental86

# Discussion Section #: 1085

CC = g++

main: main.o
	$(CC) main.o -o main

main.o: main.cpp header.h
	$(CC) -c main.cpp

tarfile: 
	tar -cf maksim_levental_3186_7826.tar main.cpp header.h Makefile
        
clean:
	rm -rf main main.o maksim_levental_3186_7826.tar
	
kill:
	find ./ -name '*~' | xargs rm

