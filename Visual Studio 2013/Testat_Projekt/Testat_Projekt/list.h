#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


	#include <stdbool.h>


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
// typesize: The size of the type the list should contain.
struct List List_New(size_t typesize);

// Safely releases the list.
void List_Release(struct List* list);

// Clears all items from the stack.
void List_Clear(struct List* list);

// Adds an item at the end of the list.
// Returns a pointer to the newly added item in the list.
// item: A pointer to the item to add.
void* List_Add(struct List*, void* item);
// Inserts an item at the specified index.
// Returns a pointer to the newly insertet item in the list.
// item: A pointer to the item to insert.
// index: The index where to insert. (Inserts before element with given index)
void* List_Insert(struct List* list, void* item, int index);
// Removes the first item found.
// Returns 'true' on success, 'false' on fail.
// item: A pointer to the item to remove.
bool List_Remove(struct List* list, void* item);
// Removes an item at the specified index.
// Returns 'true' on success, 'false' on fail.
// index: The index of the element to remove.
bool List_RemoveAt(struct List*, int index);
// Removes the given number of elements in the list at the specified index.
// Returns 'true' on success, 'false' on fail.
// index: The index where the removing begins.
// count: The number of items to remove from list.
bool List_RemoveRangeAt(struct List* list, int index, int count);
// Returns the item at the specified index.
// index: The index of the item to get.
void* List_At(struct List* list, int index);
// Returns the index of the first specified item found.
// item: The item to find.
int List_Find(struct List* list, void* item);
