

# Name: Maksim Levental

# UF ID: 3186-7826

# Gator ID: mlevental86

# Discussion Section #: 1085


# *****************************************************
# Parameters to control Makefile operation

CXX = g++
CXXFLAGS = -o

# ****************************************************
# Entries to bring the executable up to date

main: main.cpp RatInMaze.o Arraylist.o stack.o queue.o myException.o 
	$(CXX) -o main main.cpp RatInMaze.o Arraylist.o stack.cpp queue.o myException.o

RatInMaze.o: RatInMaze.cpp RatinMaze.h stack.h queue.h
	$(CXX) -c RatInMaze.cpp

Arraylist.o: Arraylist.h Arraylist.cpp
	$(CXX) -c Arraylist.cpp

Arraylist.h: Linearlist.h

stack.o: stack.cpp stack.h Arraylist.h RatinMaze.h
	$(CXX) -c stack.cpp

queue.o: queue.cpp queue.h Arraylist.h RatinMaze.h
	$(CXX) -c queue.cpp

myException.o: myException.h myException.cpp
	$(CXX) -c myException.cpp

tarfile: 
	tar -cf maksim_levental_3186_7826.tar main.cpp RatInMaze.cpp \
			RatinMaze.h Arraylist.h Arraylist.cpp myException.cpp myException.h \
			stack.cpp stack.h queue.cpp queue.h Makefile Linearlist.h

clean:
	rm -rf *.o main maksim_levental_3186_7826.tar

# kill:
# 	find ./ -name '*~' | xargs rm
