# Copyright (C) 2013 Thomas SIgurdsen <thomas.sigurdsen@gmail.com>
#
# Copying and distribution of this file, with or without modification,
# are permitted in any medium without royalty provided the copyright
# notice and this notice are preserved.  This file is offered as-is,
# without any warranty

ACLOCAL_AMFLAGS = -I m4 --install
EXTRA_DIST = m4/NOTES

bin_PROGRAMS = neuton
neuton_SOURCES = \
		 src/classes/Character.cpp \
		 src/classes/Character.hpp \
		 src/classes/CharacterFactory.cpp \
		 src/classes/Menu.hpp \
		 src/classes/MineFactory.hpp \
		 src/classes/NonPlayerCharacter.hpp \
		 src/classes/Node.cpp \
		 src/classes/NonPlayerCharacter.cpp \
		 src/classes/Player.cpp \
		 src/classes/StackNode.cpp \
		 src/classes/StackNode.hpp \
		 src/classes/Tile.cpp \
		 src/classes/Scoreboard.hpp \
		 src/classes/World.hpp \
		 src/classes/CharacterFactory.hpp \
		 src/classes/MineFactory.cpp \
		 src/classes/Tile.hpp \
		 src/classes/Scoreboard.cpp \
		 src/classes/World.cpp \
		 src/classes/Menu.cpp \
		 src/classes/Mine.cpp \
		 src/classes/Mine.hpp \
		 src/classes/Node.hpp \
		 src/classes/Player.hpp \
		 src/Includes.hpp \
		 src/main.cpp
neuton_CXXFLAGS = \
	      -ggdb3 \
	      -Wall \
	      -Wextra \
	      -ansi \
	      -pedantic \
	      -O0 \
	      -fopenmp \
	      -Weffc++ \
	      $(SFMLW_CFLAGS)

neuton_LDADD = $(SFML_LIBS)
#	       -lsfml-window \
#	       -lsfml-graphics \
#	       -lsfml-system \
#	       -lsfml-audio

