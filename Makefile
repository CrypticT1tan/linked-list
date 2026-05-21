CXX = g++
CXXFLAGS = -g -Wall -Werror
EXECS = linked_list

all: $(EXECS)
linked_list: main.o linked_list.o 
	$(CXX) $(CXXFLAGS) -o $@ $^
clean:
	rm -f *.o $(EXECS)