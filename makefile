OFILES =  source.o
TARGET = exec
COMPILER = g++-10

$(TARGET): $(OFILES)
	$(COMPILER) $(OFILES) -o $@

clean:
	rm $(OFILES)

source.o: source.cpp inc/AVLTree.hpp inc/../src/AVLTree.inl
	g++-10 source.cpp -c