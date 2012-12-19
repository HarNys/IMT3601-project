#  makefile
#
#  Copyright 2012 Thomas Sigurdsen <thomas.sigurdsen@gmail.com>
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
#
#

BINARY = ../main.bin
OBJECTS = ../Debug/main.o ../Debug/World.o ../Debug/Character.o ../Debug/MineFactory.o ../Debug/Mine.o ../Debug/Tile.o ../Debug/CharacterFactory.o ../Debug/Player.o ../Debug/Node.o ../Debug/Menu.o ../Debug/NonPlayerCharacter.o ../Debug/StackNode.o
COMPILEFLAGS = -ggdb3 -c	# the debug '-g' flag is given here so that 'LINKFLAGS' has a string
LINKFLAGS = -ggdb3		# ^^
GCC = g++ -Wall -O0 -fopenmp
LIBRARIES = -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio

# syntax for entries:
#target0 target1 : prerequisite0 prerequisite1
#	command
#	command

# productions
all : $(BINARY)
	# probable compilation success

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
