CC = gcc
COMMON_FLAGS = -Wall -Wextra -Wpedantic
LINKER_FLAGS =
ifdef DEBUG
	CFLAGS = ${COMMON_FLAGS} -g -O0
else
	CFLAGS = ${COMMON_FLAGS} -O3 -DNDEBUG
endif

all: 2Max

2Max: src/main.o
	${CC} ${COMMON_FLAGS} ${LINKER_FLAGS} -o 2Max $^

clean:
	rm -f 2Max
	rm -f src/*.o
