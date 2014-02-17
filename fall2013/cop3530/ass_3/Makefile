

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

main1: main1.o Arraylist.o IOcode.o Myexception.o
	$(CXX) -o main1 main1.o Arraylist.o IOcode.o Myexception.o

main2: main2.o Chain.o IOcode.o Myexception.o ChainNode.o
	$(CXX) -o main2 main2.o Chain.o IOcode.o Myexception.o ChainNode.o

main1.o: main1.cpp
	$(CXX) -c main1.cpp
main2.o: main2.cpp
	$(CXX) -c main2.cpp
Arraylist.o: Arraylist.h Myexception.h Arraylist.cpp
	$(CXX) -c Arraylist.cpp
Arraylist.h: Linearlist.h

Chain.o: Chain.h Myexception.h Chain.cpp
	$(CXX) -c Chain.cpp
Chain.h: Linearlist.h ChainNode.h

ChainNode.o: ChainNode.h ChainNode.cpp
	$(CXX) -c ChainNode.cpp
IOcode.o: Linearlist.h IOcode.cpp IOcode.cpp
	$(CXX) -c IOcode.cpp
Myexception.o: Myexception.h Myexception.cpp
	$(CXX) -c Myexception.cpp

tarfile: 
	tar -cf maksim_levental_3186_7826.tar main1.cpp main2.cpp \
			Arraylist.cpp Arraylist.h Myexception.cpp Myexception.h \
			IOcode.cpp IOcode.h Chain.cpp Chain.h ChainNode.cpp \
			ChainNode.h Makefile Linearlist.h

clean:
	rm -rf *.o main1 main2 maksim_levental_3186_7826.tar

kill:
	find ./ -name '*~' | xargs rm
