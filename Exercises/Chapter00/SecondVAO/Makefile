BIN = secondvao
CC = clang
FLAGS = -std=c99 -DAPPLE -Wall -pedantic -Wextra
INC = -I/sw/include -I/usr/local/include
LIBS = -lGLEW -lglfw
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit
SRC = ${BIN}.c

all:
	${CC} ${FLAGS} ${FRAMEWORKS} -o ${BIN} ${SRC} ${INC} ${LIBS}

.PHONY:

clean:
	rm $(BIN)
