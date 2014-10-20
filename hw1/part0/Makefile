OBJECTS=main.o matrix.o
SOURCES=*.cpp *.h
CFLAGS=-g
LDFLAGS=

all: testMatrix

testMatrix: $(OBJECTS)
	g++ $(LDFLAGS) $(CFLAGS) -o testMatrix $^

clean:
	rm *.o testMatrix

main.o:	main.cc matrix.h
	g++ -c $(CFLAGS) $<

matrix.o: matrix.cc matrix.h
	g++ -c $(CFLAGS) $<

.cpp.o:
	g++ -c $(CFLAGS) -o $@ $<

.PHONY: all clean
