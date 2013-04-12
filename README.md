
About IMT3601-project
=====================

IMT3601-project or "Frank Darkhawks Amazing Maze RPG!" is a student/school
project. A lot of the code is messy. This is because it is a first in many areas
for the 4 main authors/contributors.

A word of warning though: there are inconsistencies and stupid designs/decisions
throughout the project.

Dependencies
============

The game is built using SFML 2.0 <http://www.sfml-dev.org/> and either visual
studio or make and gcc.

Installing and Running
======================

Linux
-----

Before running make do 'mkdir Debug' in the IMT3601-project directory.
The makefile is located within 'src/' and when run with 'make' or 'make all'
should produce '../main.bin'.

Windows
-------
TODO: write up this section.
I (thomas) has little to nothing to do with the windows build of the project,
I will try to push one of the other devs into writing up this section.

Mac
---
The 'src/Includes.hpp' file will need to be adjusted for Mac's positioning and
naming of libraries, But once that is fixed it should work fine with gcc and
make. See Linux setup above.

Controls
========
The controls are hardcoded as of now, but there is an issue(#31) up for
making them configurable. They are as follows:

<table>
	<tr>
		<th>Key</th>
		<th>Response</th>
	</tr>
	<tr>
		<td>w,a,s,d</td>
		<td>Move up, left, down, right</td>
	</tr>
	<tr>
		<td>e</td>
		<td>Activate menu item(1)</td>
	</tr>
	<tr>
		<td>escape</td>
		<td>Open main menu</td>
	</tr>
	<tr>
		<td>+,-</td>
		<td>adjust difficulty up and down</td>
	</tr>
</table>

(1): In earlier versions (and likely future ones) this key could be used
to put down mines.

Keys can be modified in code, for in-game controls:
src/classes/Player.cpp:LocalPlayer::characterInput(Character* thisCharacter)
and menu controls:
src/classes/Menu.cpp:Menu::runMenu()

The menu controls are spread around the Menu.cpp file a bit. So if the
behaviour you are trying to change is not in that method, you will have
to search the rest of the file for it.

Music and Sounds
================

Credits go to Circuit soldiers for the songs "Intellectual Property is a Dying 
Whore" and "The Night Before Battle".
Credits go to Mediapaja2009 for the sound "death".

Licensing and Legalese
=======================

IMT3601-project is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

IMT3601-project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with IMT3601-project.  If not, see <http://www.gnu.org/licenses/>.


Contributing To the Project
===========================

If you want to contribute, send us a pull-request on github or mail us a patch
at <thomas.sigurdsen@hig.no>. Doxygen documentation, design document and coding
style(still in the design document for some reason) see the wiki
page <https://github.com/HarNys/IMT3601-project/wiki>.
