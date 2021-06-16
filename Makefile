CXX = g++
CXXFLAGS = -Wall -Wpedantic -O3
# -Wall & -Wpedantic for additional warnings
# -fopenmp for openmp (multi threading)
# -O3 for automatic (black box) optimisation by the compiler
# add -pg for analysis w/ gprof -> execute -> gprof main

# syntax:
# target: prerequisites
#	command

obj = objectFiles
src = su2code
bin = bin
sourceFiles = $(wildcard ${src}/*.cpp)
objectFiles = $(patsubst ${src}/%.cpp, ${obj}/%.o, ${sourceFiles})


all: ${bin}/analysisTest ${bin}/GaugeconfigTest ${bin}/getStapleTest\
		${bin}/SU2Test ${bin}/vector_operationsTest ${bin}/main

# all test executables w/ their corr. dependencies
# $^ references all prerequisites
${bin}/analysisTest: ${obj}/analysis.o ${obj}/analysisTest.o ${obj}/Gaugeconfig.o ${obj}/SU2.o
	${CXX} ${CXXFLAGS} $^ -o $@

${bin}/GaugeconfigTest: ${obj}/Gaugeconfig.o ${obj}/GaugeconfigTest.o ${obj}/SU2.o
	${CXX} ${CXXFLAGS} $^ -o $@

${bin}/getStapleTest: ${obj}/getStaple.o ${obj}/getStapleTest.o ${obj}/Gaugeconfig.o ${obj}/SU2.o
	${CXX} ${CXXFLAGS} $^ -o $@

${bin}/SU2Test: ${obj}/SU2.o ${obj}/SU2Test.o
	${CXX} ${CXXFLAGS} $^ -o $@

${bin}/vector_operationsTest: ${obj}/vector_operations.o ${obj}/vector_operationsTest.o
	${CXX} ${CXXFLAGS} $^ -o $@


# build the main executable -- the object files for testing will 
# not be taken into account.
${bin}/main: $(filter-out ${obj}/%Test.o, ${objectFiles})
	${CXX} ${CXXFLAGS} $^ -o $@

# build the object files for the tests
${obj}/%Test.o: ${src}/%Test.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@

# build the object files:
# $< references the first prerequisite

${obj}/SU2.o: ${src}/SU2.cpp ${src}/SU2.h ${src}/randomSU2implementation.h
	${CXX} ${CXXFLAGS} -c $< -o $@

${obj}/Gaugeconfig.o: ${src}/Gaugeconfig.cpp ${src}/Gaugeconfig.h ${src}/hotstartImplementation.h
	${CXX} ${CXXFLAGS} -c $< -o $@

${obj}/%.o: ${src}/%.cpp ${src}/%.h
	${CXX} ${CXXFLAGS} -c $< -o $@

${obj}/%.o: ${src}/%.cpp
	${CXX} ${CXXFLAGS} -c $< -o $@


clean:
	rm ${obj}/*
	rm ${bin}/*
