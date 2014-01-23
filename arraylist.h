#pragma once
/* Copyright (C) 2014 Mischa Krüger, Ammar Al-Qaiser, Frank Zimdars, Gordon Kemsies

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef LINUX
	#include <stdbool.h>
#endif

// A managed array.
struct ArrayList
{
	// The size of the type. Needed for memory allocation.
	size_t typesize;

	// Number of items in this list.
	int count;

	// A pointer to the items of the list.
	void* items;

};


// Creates and sets up a new array list.
// typesize: The size of the type the list should contain.
struct ArrayList ArrayList_New(size_t typesize);

// Safely releases the list.
void ArrayList_Release(struct ArrayList* list);

// Clears all items from the stack.
void ArrayList_Clear(struct ArrayList* list);

// Adds an item at the end of the list.
// Returns a pointer to the newly added item in the list.
// item: A pointer to the item to add.
void* ArrayList_Add(struct ArrayList*, void* item);

// Adds a range of items at the end of the list.
// items: A pointer to the items array to add.
// itemscount: The number of items of the array to add.
void* ArrayList_AddRange(struct ArrayList*, void* items, int itemscount);

// Inserts an item at the specified index.
// Returns a pointer to the newly insertet item in the list.
// item: A pointer to the item to insert.
// index: The index where to insert.
void* ArrayList_Insert(struct ArrayList* list, void* item, int index);

// Inserts a range of items at the specified index.
// items: A pointer to the items array to insert.
// itemscount: The number of items of the array to insert.
// index: The index where to insert.
void* ArrayList_InsertRange(struct ArrayList* list, void* items, int itemscount, int index);

// Removes the first item found.
// Returns 'true' on success, 'false' on fail.
// item: A pointer to the item to remove.
bool ArrayList_Remove(struct ArrayList* list, void* item);

// Removes an item at the specified index.
// Returns 'true' on success, 'false' on fail.
// index: The index of the element to remove.
bool ArrayList_RemoveAt(struct ArrayList*, int index);

// Removes the given number of elements in the list at the specified index.
// Returns 'true' on success, 'false' on fail.
// index: The index where the removing begins.
// count: The number of items to remove from list.
bool ArrayList_RemoveRangeAt(struct ArrayList* list, int index, int count);

// Returns the item at the specified index.
// index: The index of the item to get.
void* ArrayList_At(struct ArrayList* list, int index);

// Returns the index of the first specified item found.
// item: The item to find.
int ArrayList_Find(struct ArrayList* list, void* item);

// Returns the index of the first specified range found.
// items: The item range to find.
// itemscount: The length of the item range.
int ArrayList_FindRange(struct ArrayList* list, void* items, int itemscount);
