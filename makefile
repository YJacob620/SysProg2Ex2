# ID: *****1536
# EMAIL: yairjacob620@gmail.com

FLAGS=-Wall
C_FILES = Graph.cpp Algorithms.cpp

main: $(C_FILES) main.cpp
	clang++ $(FLAGS) $(C_FILES) main.cpp -o main
	./main

test: Graph.o Algorithms.o tests.o
	clang++ $(FLAGS) *.o -o tests
	./tests 

Graph.o: Graph.cpp Graph.hpp
	clang++ $(FLAGS) -c Graph.cpp

Algorithms.o: Algorithms.cpp Algorithms.hpp Graph.o
	clang++ $(FLAGS) -c Algorithms.cpp

tests.o: tests.cpp doctest.h Algorithms.o
	clang++ $(FLAGS) -c tests.cpp

clean:
	rm *.o tests main
