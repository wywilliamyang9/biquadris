CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = biquadris
OBJECTS = block.o level0.o board.o level.o cell.o main.o commandInterpreter.o OBlock.o forceBlockAction.o specialAction.o game.o subject.o graphicDisplay.o textdisplay.o IBlock.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
