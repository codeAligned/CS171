OBJECTS=parser.tab.o lexer.yy.o main.o matrix.o raster.o vec3.o
SOURCES=*.cpp *.h
CFLAGS=-g
LDFLAGS=

all: shaded

shaded: $(OBJECTS)
	g++ $(LDFLAGS) $(CFLAGS) -o shaded $^

clean:
	rm *.o lexer.yy.cpp parser.tab.cpp parser.tab.hpp shaded

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d parser.ypp

lexer.yy.cpp: lexer.lex data.h
	flex -+ -olexer.yy.cpp lexer.lex

main.o: main.cpp data.h
	g++ $(CFLAGS) -c main.cpp

matrix.o: matrix.cpp matrix.h
	g++ $(CFLAGS) -c matrix.cpp

raster.o: raster.cpp raster.h
	g++ $(CFLAGS) -c raster.cpp

vec3.o: vec3.cpp vec3.h
	g++ $(CFLAGS) -c vec3.cpp
    
.cpp.o:
	g++ -c $(CFLAGS) -o $@ $<

.PHONY: all clean
