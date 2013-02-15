/*
 * Scoreboard.cpp
 *
 * Copyright 2012 Ørjan Røkkum Brandtzæg <orokkum@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 *
 *
 */
#include "../Includes.hpp"



bool Scoreboard::setNewElement(int charNumber, int charScore)
{
	for (int i=0; i>=0; i++)//brain derp, made ugly for
	{
		if (!allNeededInfo[i])
		{
			allNeededInfo[i] = (charNumber*1000+charScore);
			i=-10;
		}
	}
	return true;
}


bool Scoreboard::printList()
{
	quickSort(allNeededInfo);
	//write out all the info remains, as well as starting the function in World::Update
	return true;
}

bool Scoreboard::quickSort(int *toSort)
{

	int * less;
	int * equal;
	int * greater;
	int pivot;

	if ((pivot = sizeof(toSort) / sizeof(toSort[0] / 2)) >= 1)
	{

		for (int i =0; !toSort[i]; i++)
		{
			if (i < toSort[pivot])
			{
				for (int j=0; j>=0; j++)//brain derp, made ugly for
				{
					if (!less[j])
					{
						less[j] = toSort[pivot];
						i= -10;
					}
				}
			}
			if (i == toSort[pivot])
			{
				for (int j=0; j>=0; j++)//brain derp, made ugly for
				{
					if (!equal[j])
					{
						equal[j] = toSort[pivot];
						i= -10;
					}
				}
			}

			if (i > toSort[pivot])
			{
				for (int j=0; j>=0; j++)//brain derp, made ugly for, haha, copypaster
				{
					if (!greater[j])
					{
						greater[j] = toSort[pivot];
						i= -10;
					}
				}
			}
		}
		quickSort(less);
		quickSort(greater);

		for (int i = 0; i>=0; i++)
		{
			if (less[i])
			{
				for (int j=0; j>=0; j++)//brain derp, made ugly for, haha, copypaster
				{
					if (!greater[j])
					{
						greater[j] = less[i];
						i= -10;
					}
				}
			}
		}

		for (int i = 0; i>=0; i++)
		{
			if (equal[i])
			{
				for (int j=0; j>=0; j++)//brain derp, made ugly for, haha, copypaster
				{
					if (!greater[j])
					{
						greater[j] = equal[i];
						i= -10;
					}
				}
			}
		}
		for (int i = 0; i>=0; i++)
		{
			if (equal[i])
			{
				for (int j=0; j>=0; j++)//brain derp, made ugly for, haha, copypaster
				{
					if (!greater[j])
					{
						greater[j] = greater[i];
						i= -10;
					}
				}
			}
		}
	}

	return true;
}
