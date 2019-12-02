CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = biquadris
OBJECTS = block.o level0.o board.o window.o DotBlock.o graphicalDisplay.o level.o level2.o level3.o level1.o level4.o cell.o main.o commandInterpreter.o OBlock.o JBlock.o LBlock.o SBlock.o ZBlock.o TBlock.o game.o subject.o textDisplay.o IBlock.o colour.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
