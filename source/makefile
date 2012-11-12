# template makefile
BINARY = ../main.bin
OBJECTS = ../Debug/main.o ../Debug/World.o ../Debug/Character.o ../Debug/MineFactory.o ../Debug/Mine.o ../Debug/Tile.o ../Debug/CharacterFactory.o ../Debug/Player.o ../Debug/Node.o ../Debug/Menu.o ../Debug/NonPlayerCharacter.o ../Debug/StackNode.o
COMPILEFLAGS = -ggdb3 -c	# the debug '-g' flag is given here so that 'LINKFLAGS' has a string
LINKFLAGS = -ggdb3		# ^^
GCC = g++ -Wall -O0 #-fopenmp
LIBRARIES = -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -lboost_program_options

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
../Debug/World.o : classes/World.cpp classes/World.hpp Includes.hpp
	$(GCC) $(COMPILEFLAGS) classes/World.cpp -o ../Debug/World.o

../Debug/Character.o : classes/Character.cpp classes/Character.hpp Includes.hpp
	$(GCC) $(COMPILEFLAGS) classes/Character.cpp -o ../Debug/Character.o

../Debug/MineFactory.o : classes/MineFactory.cpp classes/MineFactory.hpp Includes.hpp
	$(GCC) $(COMPILEFLAGS) classes/MineFactory.cpp -o ../Debug/MineFactory.o

../Debug/Mine.o : classes/Mine.cpp classes/Mine.hpp
	$(GCC) $(COMPILEFLAGS) classes/Mine.cpp -o ../Debug/Mine.o

../Debug/Tile.o : classes/Tile.cpp classes/Tile.hpp Includes.hpp
	$(GCC) $(COMPILEFLAGS) classes/Tile.cpp -o ../Debug/Tile.o

../Debug/CharacterFactory.o : classes/CharacterFactory.cpp classes/CharacterFactory.hpp Includes.hpp
	$(GCC) $(COMPILEFLAGS) classes/CharacterFactory.cpp -o ../Debug/CharacterFactory.o

../Debug/NonPlayerCharacter.o : classes/NonPlayerCharacter.cpp classes/NonPlayerCharacter.hpp Includes.hpp
	$(GCC) $(COMPILEFLAGS) classes/NonPlayerCharacter.cpp -o ../Debug/NonPlayerCharacter.o

../Debug/Player.o : classes/Player.cpp classes/Player.hpp Includes.hpp
	$(GCC) $(COMPILEFLAGS) classes/Player.cpp -o ../Debug/Player.o

../Debug/Node.o : classes/Node.cpp classes/Node.hpp Includes.hpp
	$(GCC) $(COMPILEFLAGS) classes/Node.cpp -o ../Debug/Node.o

../Debug/Menu.o : classes/Menu.cpp classes/Menu.hpp Includes.hpp
	$(GCC) $(COMPILEFLAGS) classes/Menu.cpp -o ../Debug/Menu.o

../Debug/StackNode.o : classes/StackNode.cpp classes/StackNode.hpp Includes.hpp
	$(GCC) $(COMPILEFLAGS) classes/StackNode.cpp -o ../Debug/StackNode.o
