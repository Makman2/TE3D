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

#include "arraylist.h"

#include <stdlib.h>
#include <string.h>

// Creates and sets up a new array list.
ArrayList ArrayList_New(size_t typesize)
{
	ArrayList result;
	
	result.typesize = typesize;
	result.count = 0;
	// Reserve memory at least for one item because of performance reasons.
	result.items = malloc(typesize);
	
	return result;
}

// Safely releases the list.
void ArrayList_Release(ArrayList* list)
{
	// Only free memory.
	free(list->items);
}

// Clears all items from the stack.
void ArrayList_Clear(ArrayList* list)
{
	// Reallocate memory and reset count.
	list->items = realloc(list->items, list->typesize);
	list->count = 0;
}

// Adds an item at the end of the list.
void* ArrayList_Add(ArrayList* list, void* item)
{
	// Realloc and copy.
	list->count++;
	list->items = realloc(list->items, list->count * list->typesize);
	memcpy((char*)list->items + list->typesize * (list->count - 1), item, list->typesize);
	return (char*)list->items + list->typesize * (list->count - 1);
}

// Adds a range of items at the end of the list.
void* ArrayList_AddRange(ArrayList* list, void* items, int itemscount)
{
	if (itemscount <= 0)
		return NULL;

	list->count += itemscount;
	list->items = realloc(list->items, list->count * list->typesize);
	memcpy((char*)list->items + list->typesize * (list->count - itemscount), items, list->typesize * itemscount);
	return (char*)list->items + list->typesize * (list->count - itemscount);
}

// Inserts an item at the specified index.
void* ArrayList_Insert(ArrayList* list, void* item, int index)
{
	// If index out of range, exit.
	if (index < 0 || index >= list->count)
		return NULL;

	// Realloc, copy behind and copy element.
	list->count++;
	list->items = realloc(list->items, list->count * list->typesize);
	memmove((char*)list->items + list->typesize * (index + 1), (char*)list->items + list->typesize * index, list->typesize * (list->count - index - 1));
	memcpy((char*)list->items + list->typesize * index, item, list->typesize);
	return (char*)list->items + list->typesize * index;
}

// Inserts a range of items at the specified index.
void* ArrayList_InsertRange(ArrayList* list, void* items, int itemscount, int index)
{
	// If index out of range, exit.
	if (index < 0 || index >= list->count || itemscount <= 0)
		return NULL;

	// Realloc, copy behind and copy element.
	list->count += itemscount;
	list->items = realloc(list->items, list->count * list->typesize);
	memmove((char*)list->items + list->typesize * (index + itemscount), (char*)list->items + list->typesize * index, list->typesize * (list->count - index - 1));
	memcpy((char*)list->items + list->typesize * index, items, list->typesize * itemscount);
	return (char*)list->items + list->typesize * index;
}

// Removes the first item found.
bool ArrayList_Remove(ArrayList* list, void* item)
{
	// Search, remove with copy-back.
	for(int i = 0; i < list->count; i++)
	{
		if(memcmp(item, (char*)list->items + list->typesize * i, list->typesize))
		{
			// Found.
			memmove((char*)list->items + list->typesize * i, (char*)list->items + list->typesize * (i + 1), list->typesize * (list->count - i - 1));
			list->count--;
			if (list->count == 0)
				list->items = realloc(list->items, list->typesize);
			else
				list->items = realloc(list->items, list->count * list->typesize);
			
			return true;
		}
	}
	
	return false;
}

// Removes an item at the specified index.
bool ArrayList_RemoveAt(ArrayList* list, int index)
{
	// If index out of range, exit.
	if (index < 0 || index >= list->count)
		return false;
	
	// Just remove with copy-back.
	memmove((char*)list->items + list->typesize * index, (char*)list->items + list->typesize * (index + 1), list->typesize * (list->count - index - 1));
	list->count--;
	if (list->count == 0)
		list->items = realloc(list->items, list->typesize);
	else
		list->items = realloc(list->items, list->count * list->typesize);
			
	return true;
}

// Removes the given number of elements in the list at the specified index.
bool ArrayList_RemoveRangeAt(ArrayList* list, int index, int count)
{
	// If index out of range, exit.
	if (index < 0 || index + count > list->count || count <= 0)
		return false;
	
	// Just remove with copy-back.
	memmove((char*)list->items + list->typesize * index, (char*)list->items + list->typesize * (index + count), list->typesize * (list->count - index - count - 1));
	list->count -= count;
	if (list->count == 0)
		list->items = realloc(list->items, list->typesize);
	else
		list->items = realloc(list->items, list->count * list->typesize);
			
	return true;
}

// Returns the item at the specified index.
void* ArrayList_At(ArrayList* list, int index)
{
	return (char*)list->items + list->typesize * index;
}

// Returns the index of the first specified item found.
int ArrayList_Find(ArrayList* list, void* item)
{
	for (int i = 0; i < list->count; i++)
	{
		if (memcmp((char*)list->items + list->typesize * i, item, list->typesize))
		{
			// Found.
			return i;			
		}
	}
	
	return -1;
}

// Returns the index of the first specified range found.
int ArrayList_FindRange(ArrayList* list, void* items, int itemscount)
{
	for (int i = 0; i < list->count; i++)
	{
		if (memcmp((char*)list->items + list->typesize * i, items, list->typesize * itemscount))
		{
			// Found.
			return i;			
		}
	}
	
	return -1;
}
