# Use the first FLAGS definition for debugging, the 2nd for optimizing your code
FLAGS = -Wall -Wextra -g
#FLAGS = -Wall -Wextra -O3

CA = 5
LASTNAME = Wang
BU_USERID = gwang23
GITHUB_USERID = kfc-bucket
EXECUTABLE = main

all: main

tar: clean
	cd .. && tar -cvzf CA$(CA)_$(LASTNAME)_$(BU_USERID).tar.gz cs240-spring21-ca$(CA)-$(GITHUB_USERID) && cd -

scrub: clean
	rm ~* *.swp *\#

run: $(EXECUTABLE)
	./$(EXECUTABLE)

# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing

main: main.o Graph.o Heap_Table.o Song.o Library.o
	g++ main.o Graph.o Heap_Table.o Song.o Library.o -o ./$(EXECUTABLE)

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

Graph.o: Graph.cpp
	g++ $(FLAGS) -c Graph.cpp

Heap_Table.o: Heap_Table.cpp
	g++ $(FLAGS) -c Heap_Table.cpp
	
Song.o: Song.cpp
	g++ $(FLAGS) -c Song.cpp

Library.o: Library.cpp
	g++ $(FLAGS) -c Library.cpp

clean:
	rm -f *.o $(EXECUTABLE)
