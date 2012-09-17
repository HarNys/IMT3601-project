# template makefile
BINARY = mainbin
OBJECTS = main.o # World.o Character.o MineFactory.o Mine.o
COMPILEFLAGS = -ggdb3 -c	# the debug '-g' flag is given here so that 'LINKFLAGS' has a string
LINKFLAGS = -ggdb3		# ^^
GCC = g++ -Wall
LIBRARIES = -lsfml-window -lsfml-graphics

# productions
all : $(BINARY)
	# no commands here

clean :
	rm $(OBJECTS) $(BINARY)

# link main binary executable
$(BINARY) : $(OBJECTS)
	$(GCC) $(LINKFLAGS) $(LIBRARIES) $(OBJECTS) -o $(BINARY)

# compile main
main.o : source/main.cpp source/Includes.hpp
	$(GCC) $(COMPILEFLAGS) source/main.cpp

# compile all 'OBJECTS'
#World.o : source/World.hpp source/World.cpp
#	$(GCC) $(COMPILEFLAGS) source/World.cpp

#Character.o : source/Character.hpp source/Character.cpp
#	$(GCC) $(COMPILEFLAGS) source/Character.cpp

#MineFactory.o : source/MineFactory.hpp source/MineFactory.cpp
#	$(GCC) $(COMPILEFLAGS) source/MineFactory.cpp

#Mine.o : source/Mine.hpp source/Mine.cpp
#	$(GCC) $(COMPILEFLAGS) source/Mine.cpp
