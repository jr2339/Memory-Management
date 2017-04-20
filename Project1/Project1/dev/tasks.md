# Custom Memory Management

This project is designed to reduce the amount of memory necessary to reference
memory in a C/C++ environment.  It does not change the size of a pointer
allocated by a malloc/calloc, but is intended to reference pre-allocated memory
pages through the use of a series of page arrays and offets.

## Backlog

    Instructions:
    1. Only the project owners may add items in the backlog.
    2. Items may be moved from the Backlog to Tasks at the
       weekly meeting.

* Prototype date 04/26/2017
* Final version due date 05/28/2017 (?)
* Presentation date 05/01/2017 (?)
 -------------------------------------------------------------------------------


## Tasks

    Instructions:
    1. Subitems may only be added at meetings.
    2. Subsubitems may only be added by developers.
    3. Items without initials are not being worked on.
    4. Items with initials are being worked on.
    5. Items may be moved to the Changelog iff the task
       has been completed.

* Implementation
	* Page
		* Determine size of each item (as size_t in constructor, probably)
		* Find next free space
		* Get empty / not empty status (easy!)
		* Handle deletions / frees
	* Memory Allocator (Array of pages)
		* Add new pages
	* Trie
		* Convert Node pointers from OS style pointer to our own style (page / offset)
	* Pointer (struct? class?)
		* Determine size of page array / offset (position within page) array
		* Convert array of chars to integer index
* Testing
	* Benchmarks
		* Size (our pointers vs OS pointers)
		* Speed (our pointers vs OS pointers)


## Changelog

April 15, 2017
* JR: Initialized repository

## People

* CB: Caitlyn Barrett <cb2693@nau.edu>
* AS: Austin Sanders <as2544@nau.edu>
* JR: Jun Rao <jr2339@nau.edu>