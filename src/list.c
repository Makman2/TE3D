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

#include "list.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#define ABS(x) (x < 0 ? -x : x)

// The allocator routine.
// header: Returns a reference to the header of the newly created memory block.
void Allocator(struct List* list, struct ListMemoryBlockHeader** header)
{
	struct ListMemoryBlockHeader* block;
	block = (struct ListMemoryBlockHeader*)malloc(sizeof(struct ListMemoryBlockHeader) + list->typesize);

	// memset(block, 0, sizeof(struct ListMemoryBlockHeader));

	// If there are no memory blocks in the list, set the initial first and last pointers.
	if (list->count == 0)
	{
		list->first = block;
		list->last = block;
	}

	// Return the memory block header for further manipulation.
	*header = block;

	return;
}

// The release routine.
// addr: The address of the memory block to release.
void Releasor(struct List* list, struct ListMemoryBlockHeader* addr)
{
	// Set new pointers.
	if (addr == list->last)
	{
		list->last = list->last->prev;
		list->last->next = list->first;
		list->first->prev = list->last;
	}
	else if (addr == list->first)
	{
		list->first = list->first->next;
		list->first->prev = list->last;
		list->last->next = list->first;
	}
	else
	{
		addr->prev->next = addr->next;
		addr->next->prev = addr->prev;
	}

	// Now free memory.
	free(addr);

	// Decrease counter.
	list->count--;

	// If the last found item was this item, set the last found pointer to NULL.
	if (list->found == addr)
	{
		list->found = NULL;
		list->foundindex = -1;
	}

	// If the list is empty, set the first and last parameters to NULL.
	if(list->count == 0)
	{
		list->first = NULL;
		list->last = NULL;
	}

}

// Creates and sets up a new list.
struct List List_New(size_t typesize)
{
	struct List thislist;

	thislist.typesize = typesize;
	thislist.first = NULL;
	thislist.last = NULL;
	thislist.count = 0;
	thislist.found = NULL;
	thislist.foundindex = -1;

	return thislist;
}

// Safely releases the list.
void List_Release(struct List* list)
{
	// Only release if we have something to release.
	if (list->count == 0)
		return;

	struct ListMemoryBlockHeader* before;
	struct ListMemoryBlockHeader* next = list->first;
	for(int i = 0; i < list->count; i++)
	{
		before = next;
		next = next->next;
		free(before);
	}

}

// Adds an item at the end of the list.
void* List_Add(struct List* list, void* item)
{
	struct ListMemoryBlockHeader* header;
	Allocator(list, &header);

	// Copy to the newly created memory block after the header.
	memcpy(header + 1, item, list->typesize);

	// Link the pointers.
	list->last->next = header;
	list->first->prev = header;
	header->prev = list->last;
	header->next = list->first;
	list->last = header;

	// Increase count.
	list->count++;

	return header + 1;
}

// Inserts an item at the specified index.
void* List_Insert(struct List* list, void* item, int index)
{
	// If index is out of bounds, return.
	if (index > list->count)
		return NULL;

	struct ListMemoryBlockHeader* header;
	Allocator(list, &header);

	// Copy to the newly created memory memory block after the header.
	memcpy(header + 1, item, list->typesize);

	// Find the element at the specified index.
	struct ListMemoryBlockHeader* element;

	// Handling for special cases like 0 and list->count:
	if (index == 0 && list->count == 0)
	{
		header->next = header;
		header->prev = header;
		list->first = header;
		list->last = header;

		// Increase count.
		list->count++;

		return header + 1;
	}
	else if (index == 0)
	{
		element = list->first;
		list->first = header;
	}
	else if (index == list->count)
	{
		// Like adding at the end of the list.
		element = list->first;
		list->last = header;
	}
	else
	{
		// Check whether the index is near the end, the beginning or the last found item of the list.
		if (index < list->count - index - 1 && index < ABS(index - list->foundindex))
		{
			// The index is near the beginning.
			element = list->first;
			for (int i = 0; i != index; i++)
			{
				element = element->next;
			}

		}
		else if (index >= list->count - index - 1 && list->count - index - 1 < ABS(index - list->foundindex))
		{
			// The index is near the end.
			element = list->last;
			for (int i = list->count - 1; i != index; i--)
			{
				element = element->prev;
			}

		}
		else
		{
			// The index is near the last found element.
			element = list->found;

			// Determine iteration direction.
			if (index > list->foundindex)
			{
				// Iterate forward.
				for (int i = list->foundindex; i != index; i++)
				{
					element = element->next;
				}
			}
			else if(index < list->foundindex)
			{
				// Iterate backward.
				for ( int i = list->foundindex; i != index; i--)
				{
					element = element->prev;
				}
			}
		}
	}

	// Now adjust pointers (element contains item behind insertion).
	element->prev->next = header;
	header->prev = element->prev;
	element->prev = header;
	header->next = element;

	// And adjust (if neccessary) the last found index.
	if (index <= list->foundindex)
		list->foundindex++;


	// Increase count.
	list->count++;

	return header + 1;
}

// Removes an item at the specified index.
bool List_RemoveAt(struct List* list, int index)
{
	// If index is out of bounds, return.
	if (index >= list->count || index < 0)
		return false;

	struct ListMemoryBlockHeader* element;

	// Check whether the index is near the end, the beginning or the last found item of the list.
	if (index < list->count - index - 1 && index < ABS(index - list->foundindex))
	{
		// The index is near the beginning.
		element = list->first;
		for (int i = 0; i != index; i++)
		{
			element = element->next;
		}

	}
	else if (index >= list->count - index - 1 && list->count - index - 1 < ABS(index - list->foundindex))
	{
		// The index is near the end.
		element = list->last;
		for (int i = list->count - 1; i != index; i--)
		{
			element = element->prev;
		}

	}
	else
	{
		// The index is near the last found element.
		element = list->found;

		// Determine iteration direction.
		if (index > list->foundindex)
		{
			// Iterate forward.
			for (int i = list->foundindex; i != index; i++)
			{
				element = element->next;
			}
		}
		else if(index < list->foundindex)
		{
			// Iterate backward.
			for (int i = list->foundindex; i != index; i--)
			{
				element = element->prev;
			}
		}
	}

	// Remove item.
	Releasor(list, element);

	// Adjust last found index, if removed index was smaller.
	if (index < list->foundindex)
		list->foundindex--;

	return true;
}

// Removes the first item found.
bool List_Remove(struct List* list, void* item)
{
	struct ListMemoryBlockHeader* element;
	element = list->first;

	for(int i = 0; i < list->count; i++)
	{
		// If the compare indicates the memory blocks are equal, we found our searched item.
		if (!memcmp(item, element + 1, list->typesize))
		{
			Releasor(list, element);
			// Adjust last found index.
			if (i < list->foundindex)
				list->foundindex--;

			return true;
		}

		element = element->next;
	}

	// Not found.
	return false;
}

// Removes the given number of elements in the list at the specified index.
bool List_RemoveRangeAt(struct List* list, int index, int count)
{
	// If index with count is out of bounds, return.
	if (index < 0 || count < 1 || index + count > list->count)
		return false;

	// If range is the entire list, just call List_Clear().
	if (index == 0 && index + count == list->count)
	{
		List_Clear(list);
		return true;
	}

	struct ListMemoryBlockHeader* element;

	// Check whether the index is near the end, the beginning or the last found item of the list.
	if (index < list->count - index - 1 && index < ABS(index - list->foundindex))
	{
		// The index is near the beginning.

		element = list->first;
		for (int i = 0; i != index; i++)
		{
			element = element->next;
		}

	}
	else if (index >= list->count - index - 1 && list->count - index - 1 < ABS(index - list->foundindex))
	{
		// The index is near the end.
		element = list->last;
		for (int i = list->count - 1; i != index; i--)
		{
			element = element->prev;
		}

	}
	else
	{
		// The index is near the last found element.
		element = list->found;

		// Determine iteration direction.
		if (index > list->foundindex)
		{
			// Iterate forward.
			for (int i = list->foundindex; i != index; i++)
			{
				element = element->next;
			}
		}
		else if(index < list->foundindex)
		{
			// Iterate backward.
			for (int i = list->foundindex; i != index; i--)
			{
				element = element->prev;
			}
		}
	}


	struct ListMemoryBlockHeader* rangestart = element->prev;

	// If the last item gets deleted, link the 'last'-pointer to the element before our current found, because everythin after it gets removed.
	if (index + count == list->count)
		list->last = rangestart;

	// free() elements.
	struct ListMemoryBlockHeader* before;
	for(int i = 0; i < count; i++)
	{
		before = element;
		element = element->next;
		free(before);
	}

	// If the first item gets deleted, link the 'first'-pointer to the range end.
	if (index == 0)
		list->first = element;

	// Relink pointers.
	rangestart->next = element;
	element->prev = rangestart;


	// Adjust last found index, if removed index was smaller or the last found element was inside removing-range.
	if (list->foundindex >= index && list->foundindex < index + count)
	{
		list->foundindex = -1;
		list->found = NULL;
	}
	else if (index < list->foundindex)
		list->foundindex -= count;

	// At least decrement pointer by count.
	list->count -= count;

	return true;
}

// Returns the item at the specified index.
void* List_At(struct List* list, int index)
{
	// If index is out of bounds, return.
	if (index >= list->count || index < 0)
		return NULL;

	struct ListMemoryBlockHeader* element;

	// Check whether the index is near the end, the beginning or the last found item of the list.
	if (index < list->count - index - 1 && index < ABS(index - list->foundindex))
	{
		// The index is near the beginning.
		element = list->first;
		for (int i = 0; i != index; i++)
		{
			element = element->next;
		}

	}
	else if (index >= list->count - index - 1 && list->count - index - 1 < ABS(index - list->foundindex))
	{
		// The index is near the end.
		element = list->last;
		for (int i = list->count - 1; i != index; i--)
		{
			element = element->prev;
		}

	}
	else
	{
		// The index is near the last found element.
		element = list->found;

		// Determine iteration direction.
		if (index > list->foundindex)
		{
			// Iterate forward.
			for (int i = list->foundindex; i != index; i++)
			{
				element = element->next;
			}
		}
		else if(index < list->foundindex)
		{
			// Iterate backward.
			for (int i = list->foundindex; i != index; i--)
			{
				element = element->prev;
			}
		}
	}

	// Set new last found index and pointer.
	list->foundindex = index;
	list->found = element;

	return element + 1;
}

// Returns the index of the first specified item found.
int List_Find(struct List* list, void* item)
{
	struct ListMemoryBlockHeader* element;
	element = list->first;

	for(int i = 0; i < list->count; i++)
	{
		// If the compare indicates the memory blocks are equal, we found our searched item.
		if (!memcmp(item, element + 1, list->typesize))
		{
			// Adjust last found index, if removed index was smaller.
			list->foundindex = i;
			list->found = element;

			return i;
		}

		element = element->next;
	}

	// Not found.
	return -1;
}

// Clears all items from the list.
void List_Clear(struct List* list)
{

	// You can release the list and set the members to default values, like we have a new list.
	List_Release(list);

	list->first = NULL;
	list->last = NULL;
	list->count = 0;
	list->found = NULL;
	list->foundindex = -1;

	return;
}
