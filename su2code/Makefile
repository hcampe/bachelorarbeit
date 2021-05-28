CXX = g++
CXXFLAGS = -Wall -Wpedantic
# add -pg for analysis w/ gprof -> execute -> gprof main

# syntax:
# target: prerequisites
#	command

sourceFiles = $(wildcard *.cpp)
objectFiles = $(patsubst %.cpp,%.o,${sourceFiles})


all: analysisTest GaugeconfigTest getStapleTest\
		SU2Test vector_operationsTest main

# all test executables w/ their corr. dependencies
# $^ references all prerequisites
analysisTest: analysis.o analysisTest.o Gaugeconfig.o SU2.o
	${CXX} ${CXXFLAGS} $^ -o $@

GaugeconfigTest: Gaugeconfig.o GaugeconfigTest.o SU2.o
	${CXX} ${CXXFLAGS} $^ -o $@

getStapleTest: getStaple.o getStapleTest.o Gaugeconfig.o SU2.o
	${CXX} ${CXXFLAGS} $^ -o $@

SU2Test: SU2.o SU2Test.o
	${CXX} ${CXXFLAGS} $^ -o $@

vector_operationsTest: vector_operations.o vector_operationsTest.o
	${CXX} ${CXXFLAGS} $^ -o $@


# build the main executable -- the object files for testing will 
# not be taken into account.
main: $(filter-out %Test.o, ${objectFiles})
	${CXX} ${CXXFLAGS} $^ -o $@

# build the object files for the tests
%Test.o: %Test.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

# build the object files:
# $< references the first prerequisite
%.o: %.cpp %.h
	${CXX} ${CXXFLAGS} -c $< -o $@

clean:
	rm *Test main
	rm *.o