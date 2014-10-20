OBJECTS=main.o readpng.o
CFLAGS=-g

# for OSX
LDFLAGS=-L/usr/X11R6/lib -framework GLUT -framework OpenGL -lpng #-lXi -lXmu

# for linux:
#LDFLAGS= -L/usr/lib/nvidia -L/usr/X11R6/lib -lglut -lGL -lGLU -lpng #-lXi -lXmu

glslRenderer: $(OBJECTS)
	g++ $(LDFLAGS) -o glslRenderer $^

.cpp.o:
	g++ $(CFLAGS) -c $<

clean:
	-rm $(OBJECTS) glslRenderer
