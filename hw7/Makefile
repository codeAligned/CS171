# Makefile for cs171 HW 7
# Just type "make" to compile; if it works right, you should have an
# executable called oglTexRenderer.

CXX		= g++
# add -g for debugging info
CXXFLAGS	= -Wall -g

LDFLAGS	= -L/usr/X11R6/lib -framework GLUT -framework OpenGl -L/usr/local/lib 

# for linux use these instead of the above:
#CXXFLAGS	= -Wall -g
#LDFLAGS	= -L/usr/X11R6/lib -lglut -lGL -lGLU -lXi -lXmu

SRCS	= *.cpp *.h
OBJS	= parser.tab.o lexer.yy.o main.o matrix.o vec3.o
PROG	= keyframe

all: $PROG

$PROG: $(OBJS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $(PROG) $^

clean:
	rm *.o lexer.yy.cpp parser.tab.cpp parser.tab.hpp $(PROG)

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d parser.ypp

lexer.yy.cpp: lexer.lex data.h
	flex -+ -olexer.yy.cpp lexer.lex

main.o: main.cpp data.h
	$(CXX) $(CXXFLAGS) -c main.cpp

matrix.o: matrix.cpp matrix.h
	$(CXX) $(CXXFLAGS) -c matrix.cpp

vec3.o: vec3.cpp vec3.h
	$(CXX) $(CXXFLAGS) -c vec3.cpp
    
.cpp.o:
	g++ -c $(CXXFLAGS) -o $@ $<

.PHONY: all clean
