# template makefile
BINARY = mainbin
OBJECTS = ../Debug/main.o ../Debug/World.o ../Debug/Character.o ../Debug/MineFactory.o ../Debug/Mine.o
COMPILEFLAGS = -ggdb3 -c	# the debug '-g' flag is given here so that 'LINKFLAGS' has a string
LINKFLAGS = -ggdb3		# ^^
GCC = g++ -Wall
LIBRARIES = -lsfml-window -lsfml-graphics

# syntax for entries:
#target0 target1 : prerequisite0 prerequisite1
#	command
#	command

# productions
all : $(BINARY)
	# no commands here

clean :
	rm $(OBJECTS) $(BINARY)

# link main binary executable
$(BINARY) : $(OBJECTS)
	$(GCC) $(LINKFLAGS) $(LIBRARIES) $(OBJECTS) -o $(BINARY)

# compile main
../Debug/main.o : main.cpp Includes.hpp ../Debug/Character.o
	$(GCC) $(COMPILEFLAGS) main.cpp -o ../Debug/main.o

# compile all 'OBJECTS'
../Debug/World.o : classes/World.hpp classes/World.cpp
	$(GCC) $(COMPILEFLAGS) classes/World.cpp -o ../Debug/World.o

../Debug/Character.o : classes/Character.cpp classes/Character.hpp Includes.hpp
	$(GCC) $(COMPILEFLAGS) classes/Character.cpp -o ../Debug/Character.o

../Debug/MineFactory.o : classes/MineFactory.hpp classes/MineFactory.cpp
	$(GCC) $(COMPILEFLAGS) classes/MineFactory.cpp -o ../Debug/MineFactory.o

../Debug/Mine.o : classes/Mine.hpp classes/Mine.cpp
	$(GCC) $(COMPILEFLAGS) classes/Mine.cpp -o ../Debug/Mine.o
