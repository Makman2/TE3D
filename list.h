#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef WIN32
	#include <stdbool.h>
#endif

struct ListMemoryBlockHeader
{
	// Pointer to the next memory block.
	struct ListMemoryBlockHeader* next;
	// Pointer to the previous memory block.
	struct ListMemoryBlockHeader* prev;
};

// A linked list.
struct List
{
	// The size of the type. Needed for memory allocation.
	size_t typesize;
	// Start and end pointers to the next / previous memory block.
	struct ListMemoryBlockHeader* first;
	struct ListMemoryBlockHeader* last;
	
	// Number of items in this list.
	int count;
	
	// The last found item. Do not use this value.
	struct ListMemoryBlockHeader* found;
	int foundindex;

};


// Creates and sets up a new list.
struct List List_New(size_t typesize);

// Safely releases the list.
void List_Release(struct List* list);

// Clears all items from the stack.
void List_Clear(struct List* list);

// Adds an item at the end of the list.
// Returns a pointer to added item in the list.
void* List_Add(struct List*, void* item);
// Inserts an item at the specified index.
// item: A pointer to the item to insert.
// index: The index where to insert. (Inserts before element with given index)
void* List_Insert(struct List* list, void* item, int index);
// Removes the first item found.
// item: A pointer to the item to remove.
bool List_Remove(struct List* list, void* item);
// Removes an item at the specified index.
// index: The index of the element to remove.
bool List_RemoveAt(struct List*, int index);
