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

#ifdef LINUX
	#include <stdbool.h>
#endif

/// A managed array.
typedef struct
{
	/// The size of the type. Needed for memory allocation.
	size_t typesize;
	/// Number of items in this list.
	int count;
	/// A pointer to the items of the list.
	void* items;
} ArrayList;


/// Creates and sets up a new array list.
/// @param[in]  typesize: The size of the type the list should contain.
ArrayList ArrayList_New(size_t typesize);

/// Safely releases the list.
void ArrayList_Release(ArrayList* list);

/// Clears all items from the stack.
void ArrayList_Clear(ArrayList* list);

/// Adds an item at the end of the list.
/// Returns a pointer to the newly added item in the list.
/// @param[in] item A pointer to the item to add.
void* ArrayList_Add(ArrayList*, void* item);

// Adds a range of items at the end of the list.
/// @param[in]  items: A pointer to the items array to add.
/// @param[in]  itemscount: The number of items of the array to add.
void* ArrayList_AddRange(ArrayList*, void* items, int itemscount);

/// Inserts an item at the specified index.
/// Returns a pointer to the newly insertet item in the list.
/// @param[in]  item A pointer to the item to insert.
/// @param[in]  index The index where to insert.
void* ArrayList_Insert(ArrayList* list, void* item, int index);

/// Inserts a range of items at the specified index.
/// @param[in]  items A pointer to the items array to insert.
/// @param[in]  itemscount The number of items of the array to insert.
/// @param[in]  index The index where to insert.
void* ArrayList_InsertRange(ArrayList* list, void* items, int itemscount, int index);

/// Removes the first item found.
/// Returns 'true' on success, 'false' on fail.
/// @param[in]  item A pointer to the item to remove.
bool ArrayList_Remove(ArrayList* list, void* item);

/// Removes an item at the specified index.
/// Returns 'true' on success, 'false' on fail.
/// @param[in]  index: The index of the element to remove.
bool ArrayList_RemoveAt(ArrayList*, int index);

/// Removes the given number of elements in the list at the specified index.
/// Returns 'true' on success, 'false' on fail.
/// @param[in]  index: The index where the removing begins.
/// @param[in]  count: The number of items to remove from list.
bool ArrayList_RemoveRangeAt(ArrayList* list, int index, int count);

/// Returns the item at the specified index.
/// @param[in]  index The index of the item to get.
void* ArrayList_At(ArrayList* list, int index);

/// Returns the index of the first specified item found.
/// @param[in]  item The item to find.
int ArrayList_Find(ArrayList* list, void* item);

/// Returns the index of the first specified range found.
/// @param[in]  items The item range to find.
/// @param[in]  itemscount The length of the item range.
int ArrayList_FindRange(ArrayList* list, void* items, int itemscount);
