###
### Makefile for the gerp Project
###
### Author: Caleb Johnson, Owen Short
### Date: 11/28/23
MAKEFLAGS += -L

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3

# This rule links all .o files and creates an executable to run the program
gerp: main.o gerp.o Hash.o FSTree.o DirNode.o
	${CXX} ${LDFLAGS} -o gerp $^

# This rule will be used to build main.o
main.o: main.cpp gerp.h

# This rule will be used to build gerp.o
gerp.o: gerp.cpp gerp.h Hash.h Word.h Line.h

# This rule will be used to build Hash.o
Hash.o: Hash.cpp Hash.h Word.h

# This rule will be used to run the treeTraversal program
treeTraversal: FSTreeTraversal.o DirNode.o FSTree.o
	${CXX} ${LDFLAGS} -o treeTraversal $^

# This rule will be used to build FSTreeTraversal.o
FSTreeTraversal.o: FSTreeTraversal.cpp DirNode.h FSTree.h

# This rule will be used to build stringProcessing.o
stringProcessing.o: stringProcessing.cpp stringProcessing.h

# The below rule will be used by unit_test
unit_test: unit_test_driver.o stringProcessing.o Hash.o gerp.o FSTree.o DirNode.o
	$(CXX) $(CXXFLAGS) $^