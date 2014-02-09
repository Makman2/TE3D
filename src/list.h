/*
 * Copyright (C) 2014 Mischa Krüger
 * Copyright (C) 2014 Ammar Al-Qaiser
 * Copyright (C) 2014 Frank Zimdars
 * Copyright (C) 2014 Gordon Kemsies
 * Copyright (C) 2014 Lasse Schuirmann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


	#include <stdbool.h>


/**
 * The memory block header for list items.
 * 
 * A nonanonymous declaration is needed since it's recursive.
 */
typedef struct ListMemoryBlockHeader_struct
{
	/// Pointer to the next memory block.
	struct ListMemoryBlockHeader_struct* next;
	/// Pointer to the previous memory block.
	struct ListMemoryBlockHeader_struct* prev;
} ListMemoryBlockHeader;

/// A double linked list.
typedef struct
{
	/// The size of the type. Needed for memory allocation.
	size_t typesize;
	/// Points to the next memory block.
	ListMemoryBlockHeader* first;
	/// Points to the previous memory block.
	ListMemoryBlockHeader* last;

	/// Number of items in this list.
	int count;

	/// The last found item.
	ListMemoryBlockHeader* found;
	/// The index of the last found item.
	int foundindex;

} List;


/// Creates and sets up a new list.
///@param[in] typesize The size of the type the list should contain.
List List_New(size_t typesize);

/// Safely releases the list.
void List_Release(List* list);

/// Clears all items from the list.
void List_Clear(List* list);

// Adds an item at the end of the list.
// Returns a pointer to the newly added item in the list.
///@param[in] item: A pointer to the item to add.
void* List_Add(List*, void* item);

/// Inserts an item at the specified index.
/// Returns a pointer to the newly insertet item in the list.
///@param[in] item: A pointer to the item to insert.
///@param[in] index: The index where to insert. (Inserts before element with given index)
void* List_Insert(List* list, void* item, int index);

/// Removes the first item found.
/// Returns 'true' on success, 'false' on fail.
///@param[in] item A pointer to the item to remove.
bool List_Remove(List* list, void* item);

/// Removes an item at the specified index.
/// Returns 'true' on success, 'false' on fail.
///@param[in] index The index of the element to remove.
bool List_RemoveAt(List*, int index);

/// Removes the given number of elements in the list at the specified index.
// Returns 'true' on success, 'false' on fail.
///@param[in] index The index where the removing begins.
///@param[in] count The number of items to remove from list.
bool List_RemoveRangeAt(List* list, int index, int count);

/// Returns the item at the specified index.
///@param[in] index The index of the item to get.
void* List_At(List* list, int index);

/// Returns the index of the first specified item found.
///@param[in] item The item to find.
int List_Find(List* list, void* item);
