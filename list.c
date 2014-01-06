#include "list.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef WIN32
	#include <stdbool.h>
#endif

#define ABS(x) (x < 0 ? -x : x)

// The allocator routine.
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
	
	// Increase count.
	list->count++;

	// Return the memory block header for further manipulation.
	*header = block;

	return;
}

// The release routine.
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
	
	// If the list is empty, set the first and last parameters to Null.
	if(list->count == 0)
	{
		list->first = NULL;
		list->last = NULL;
	}
	
}

// Creates and sets up a new list.
struct List List_New(unsigned int typesize)
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
	// Release all allocated memory blocks.
	// Iterate over each block and obtain it's address. Create a dynamic array and after iteration free all blocks.
	struct ListMemoryBlockHeader** ptrs = malloc(list->count * sizeof(struct ListMemoryBlockHeader*));
	struct ListMemoryBlockHeader* next = list->first;
	int i;
	for(i = 0; next != list->last; i++)
	{
		ptrs[i] = next;
		next = next->next;
	}
	// Obtain the last address.
	ptrs[i + 1] = next;
	
	// Now release.
	for(i = 0; i < list->count; i++)
	{
		free(ptrs[i]);
	}
	
	// And free the pointer array.
	free(ptrs);
}

// Adds an item at the end of the list.
// Returns a pointer to added item in the list.
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
	
	// Find the element at and before the specified index.
	struct ListMemoryBlockHeader* element;
	
	// Handling for special cases like 0 and list->count:
	if (index == 0)
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
	
	return header + 1;
}

// Removes an item at the specified index.
bool List_RemoveAt(struct List* list, int index)
{
	// If index is out of bounds, return.
	if (index >= list->count)
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
			// Adjust last found index, if removed index was smaller.
			if (i < list->foundindex)
				list->foundindex--;
			
			return true;
		}
		
		element = element->next;
	}
	
	// Not found.
	return false;
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
	list->foundindex = 0;
	
	return;
}
