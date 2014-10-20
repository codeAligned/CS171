# Makefile for cs171 HW 0
# Just type "make" to compile; if it works right, you should have an
# executable called hw0.

CXX		= g++
# add -g for debugging info
CXXFLAGS	= -Wall -g 

LDFLAGS	= -L/usr/X11R6/lib -framework GLUT -framework OpenGl 

#linux
#LDFLAGS	= -L/usr/X11R6/lib -lglut -lGL -lGLU -lXi -lXmu

SRCS	= *.cpp *.h
OBJS	= main.o matrix.o spline.o vec3.o
PROG	= editSpline

all: $PROG

$PROG: $(OBJS)
	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $(PROG) $^

clean:
	rm *.o $(PROG)

main.o: main.cpp spline.h vec3.h
	$(CXX) $(CXXFLAGS) -c main.cpp

matrix.o: matrix.cpp matrix.h
	$(CXX) $(CXXFLAGS) -c matrix.cpp

spline.o: spline.cpp spline.h vec3.h
	$(CXX) $(CXXFLAGS) -c spline.cpp

vec3.o: vec3.cpp vec3.h
	$(CXX) $(CXXFLAGS) -c vec3.cpp

.cpp.o:
	g++ -c $(CXXFLAGS) -o $@ $<

.PHONY: all clean
