CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = biquadris
OBJECTS = block.o level0.o board.o level.o level1.o cell.o main.o commandInterpreter.o OBlock.o game.o subject.o textDisplay.o IBlock.o colour.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
