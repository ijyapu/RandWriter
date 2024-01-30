CC = g++
CFLAGS = -Wall -Werror -pedantic --std=c++11 -g
LIB = -lboost_unit_test_framework
DEPS = RandWriter.hpp
OBJECTS = RandWriter.o
PROGRAM = TextWriter test
LIBRARY = TextWriter.a

.PHONY: all clean lint

all: $(PROGRAM) $(LIBRARY)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

TextWriter: $(OBJECTS) TextWriter.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

test: $(OBJECTS) test.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(LIBRARY): $(OBJECTS)
	ar rcs $@ $^

clean:
	rm -f *.o $(PROGRAM) $(LIBRARY)

lint:
	cpplint *.cpp *.hpp
