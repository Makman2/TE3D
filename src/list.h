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


	#include <stdbool.h>


/// The memory block header for list items.
struct ListMemoryBlockHeader
{
	/// Pointer to the next memory block.
	struct ListMemoryBlockHeader* next;
	/// Pointer to the previous memory block.
	struct ListMemoryBlockHeader* prev;
};

/// A double linked list.
struct List
{
	/// The size of the type. Needed for memory allocation.
	size_t typesize;
	/// Points to the next memory block.
	struct ListMemoryBlockHeader* first;
	/// Points to the previous memory block.
	struct ListMemoryBlockHeader* last;

	/// Number of items in this list.
	int count;

	/// The last found item.
	struct ListMemoryBlockHeader* found;
	/// The index of the last found item.
	int foundindex;

};


/// Creates and sets up a new list.
///@param[in] typesize The size of the type the list should contain.
struct List List_New(size_t typesize);

/// Safely releases the list.
void List_Release(struct List* list);

/// Clears all items from the list.
void List_Clear(struct List* list);

// Adds an item at the end of the list.
// Returns a pointer to the newly added item in the list.
///@param[in] item: A pointer to the item to add.
void* List_Add(struct List*, void* item);

/// Inserts an item at the specified index.
/// Returns a pointer to the newly insertet item in the list.
///@param[in] item: A pointer to the item to insert.
///@param[in] index: The index where to insert. (Inserts before element with given index)
void* List_Insert(struct List* list, void* item, int index);

/// Removes the first item found.
/// Returns 'true' on success, 'false' on fail.
///@param[in] item A pointer to the item to remove.
bool List_Remove(struct List* list, void* item);

/// Removes an item at the specified index.
/// Returns 'true' on success, 'false' on fail.
///@param[in] index The index of the element to remove.
bool List_RemoveAt(struct List*, int index);

/// Removes the given number of elements in the list at the specified index.
// Returns 'true' on success, 'false' on fail.
///@param[in] index The index where the removing begins.
///@param[in] count The number of items to remove from list.
bool List_RemoveRangeAt(struct List* list, int index, int count);

/// Returns the item at the specified index.
///@param[in] index The index of the item to get.
void* List_At(struct List* list, int index);

/// Returns the index of the first specified item found.
///@param[in] item The item to find.
int List_Find(struct List* list, void* item);
