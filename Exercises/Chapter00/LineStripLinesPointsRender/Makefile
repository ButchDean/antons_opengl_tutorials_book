BINLS = line_strip
BINL = lines
BINP = points
CC = clang
FLAGS = -std=c99 -DAPPLE -Wall -pedantic
INC = -I/sw/include -I/usr/local/include
LIBS = -lGLEW -lglfw
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit
SRCLS = ${BINLS}.c
SRCL = ${BINL}.c
SRCP = ${BINP}.c

all:
	${CC} ${FLAGS} ${FRAMEWORKS} -o ${BINLS} ${SRCLS} ${INC} ${LIBS}
	${CC} ${FLAGS} ${FRAMEWORKS} -o ${BINL} ${SRCL} ${INC} ${LIBS}
	${CC} ${FLAGS} ${FRAMEWORKS} -o ${BINP} ${SRCP} ${INC} ${LIBS}

.PHONY:

clean:
	rm ${BINLS} ${BINL} ${BINP}
