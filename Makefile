CC = g++
EXECUTABLE = bin/main.exe
CFLAGS = -Wall -Werror -c -MD
SOURCES = $(wildcard $(addprefix src/,*.cpp))
OBJECTS = $(patsubst $(addprefix src/, %.cpp),$(addprefix build/src/, %.o),$(wildcard $(addprefix src/, *.cpp)))
DEPENDENCIES = $(patsubst $(addprefix build/src/, %.o), $(addprefix build/src/, %.d), $(wildcard $(addprefix build/src/, *.o)))

all : $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $^ -o $@ -std=c++11

build/src/%.o : src/%.cpp
	$(CC) $(CFLAGS) $< -o $@ -std=c++11

.PHONY : test

test: bin/tests

bin/bin/tests: build/test/main.o build/test/EndlessTape.o build/test/Program.o
	gcc -Wall -Werror build/test/main.o build/test/EndlessTape.o build/test/Program.o -o bin/bin/tests

build/test/main.o: test/main.c
	gcc -Wall -Werror -c -I CTest -I src test/main.c -o build/test/main.o

build/test/area.o: TuringMashine/EndlessTape.c TuringMashine/EndlessTape.h
	gcc -Wall -Werror -c -I CTest -I src src/area.c -o build/test/EndlessTape.o

build/test/area.o: TuringMashine/Program.c TuringMashine/Program.h
	gcc -Wall -Werror -c -I CTest -I src src/area.c -o build/test/Program.o