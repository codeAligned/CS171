OBJECTS=parser.tab.o lexer.yy.o main.o matrix.o
SOURCES=*.cpp *.h
CFLAGS=-g
LDFLAGS=

all: draw2d

draw2d: $(OBJECTS)
	g++ $(LDFLAGS) $(CFLAGS) -o draw2d $^

clean:
	rm *.o lexer.yy.cpp parser.tab.cpp parser.tab.hpp draw2d

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d parser.ypp

lexer.yy.cpp: lexer.lex data.h
	flex -+ -olexer.yy.cpp lexer.lex

main.o: main.cpp data.h
	g++ $(CFLAGS) -c main.cpp

matrix.o: matrix.cpp matrix.h
	g++ $(CFLAGS) -c matrix.cpp

.cpp.o:
	g++ -c $(CFLAGS) -o $@ $<

.PHONY: all clean
