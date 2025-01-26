CXX = g++
CXXFLAGS = -std=c++14 -Werror -Wsign-conversion -g
LDFLAGS = -lpthread

OBJS = board.o catan.o player.o  devcard.o Demo.o


demo: $(OBJS)
	$(CXX) $(CXXFLAGS) -o demo $(OBJS) $(LDFLAGS)

run: demo
	./demo

board.o: board.cpp board.hpp
	$(CXX) $(CXXFLAGS) -c board.cpp

catan.o: catan.cpp catan.hpp board.hpp player.hpp devcard.hpp
	$(CXX) $(CXXFLAGS) -c catan.cpp

player.o: player.cpp player.hpp
	$(CXX) $(CXXFLAGS) -c player.cpp

devcard.o: devcard.cpp devcard.hpp player.hpp catan.hpp
	$(CXX) $(CXXFLAGS) -c devcard.cpp

Demo.o: Demo.cpp catan.hpp player.hpp board.hpp devcard.hpp
	$(CXX) $(CXXFLAGS) -c Demo.cpp


.PHONY: clean run

clean:
	rm -f *.o demo

valgrind: demo
	valgrind --leak-check=full --track-origins=yes ./demo


#///////////////////////////////////////////////////////////////////////////////////////

# CXX = g++
# CXXFLAGS = -std=c++11 -Werror -Wsign-conversion
# LDFLAGS = -L. -lpthread

# SRCS = board.cpp catan.cpp player.cpp 
# OBJS = $(SRCS:.cpp=.o)


# INCLUDES = board.hpp catan.hpp player.hpp doctest.h

# all: demo


# demo: $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# catan: $(OBJS)
# 	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)



# %.o: %.cpp $(INCLUDES)
# 	$(CXX) $(CXXFLAGS) -c $<

# .PHONY: clean run test valgrind


# valgrind: startgame
# 	valgrind --leak-check=full --track-origins=yes ./startgame

# clean:
# 	rm -f $(OBJS) 


#///////////////////////////////////////////////////////////////////////////////
# CC=g++
# FLAGS=-std=c++14 -Werror -Wsign-conversion

# CPP_FILES = board.cpp player.cpp catan.cpp
# OBJ_FILES := $(CPP_FILES:.cpp=.o)



# run:demo
# 	./demo

# catan: $(OBJ_FILES)
# 	$(CC) $(FLAGS) -o catan $(OBJ_FILES)	

# %.o: %.cpp
# 	$(CC) $(FLAGS) -c -o $@ $<




# run:demo
# 	./demo



# demo:demos.o
# 	$(CC) $(FLAGS) -o demo demo.o


# test:


# clean:
# 	rm -f *.o demo test