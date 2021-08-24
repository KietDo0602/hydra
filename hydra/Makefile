CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = Main.o Card.o GameDriver.o Head.o Player.o Utils.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = hydra

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
