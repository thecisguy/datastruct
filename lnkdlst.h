#ifndef LNKDLST_H
#define LNKDLST_H

#include <stdbool.h>

// prepare for c++ support
#ifdef __cplusplus
extern "C" {
#endif

typedef struct LNKDLST *LNKDLST;

/* Initialize and Destroy */

// allocates and returns a new, empty lnkdlst
// returns null if memory could not be allocated
LNKDLST ll_init(void);

// destroys and de-allocates memory for a lnkdlst
// after calling this method, it is illegal to
// use the lnkdlst for anything else
// this method does not free the data stored
// in the list
//
void ll_destroy(LNKDLST);

// like ll_destroy, but also calls free
// (from stdlib.h) on each non-null datem
// in the lnkdlst
void ll_autodestroy(LNKDLST);

// returns a shallow copy of a LNKDLST
LNKDLST ll_clone(LNKDLST);

// returns a deep copy of a LNKDLST,
// by calling clone on each item.
// clone should take a pointer to an item
// stored in the list and return a pointer to
// a copy of that item.
LNKDLST ll_deepclone(LNKDLST, void *(*clone)(void *));

/* Conventional use */

// add item at specified index
void ll_addnum(LNKDLST, void *, int index);

// add item at beginning of list
void ll_addfirst(LNKDLST, void *);

// add item at end of list
void ll_addlast(LNKDLST, void *);

// remove item at specified index
void *ll_removenum(LNKDLST, int index);

// remove first item in list
void *ll_removefirst(LNKDLST);

// remove last item in list
void *ll_removelast(LNKDLST);

// removes first occurance of an item in a list
// returns true if it was present,
// false if it wasn't
bool ll_removeitem(LNKDLST, void *);

// retrieves, but does not remove, the item at
// the specified index
void *ll_getnum(LNKDLST, int index);

// retrieves, but does not remove, the first
// item in the list
void *ll_getfirst(LNKDLST);

// retrieves, but does not remove, the last
// item in the list
void *ll_getlast(LNKDLST);

// tests if item is present in list
bool ll_contains(LNKDLST, void *);

// returns the index of the first occurance
// of the given item in the list,
// or -1 if it is not present
int ll_indexof(LNKDLST, void *);

// returns the number of data in the list
int ll_size(LNKDLST);

/* LIFO-style use */

// equivalent to ll_addfirst
void ll_push(LNKDLST, void *);

// equivalent to ll_removefirst
void *ll_pop(LNKDLST);

// equivalent to ll_getfirst
void *ll_peek(LNKDLST);

/* FIFO-style use */

// equivalent to ll_addlast
void ll_add(LNKDLST, void *);

// equivalent to ll_removefirst
void *ll_remove(LNKDLST);

// ll_peek is also a FIFO-style function

/* Iteration
 * 
 * Note: If a call is made to a remove function such that
 * it would remove the node which the list's internal iterator
 * would return upon the next call to ll_next(),
 * the iterator will be automatically advanced.
 */

// initializes this list's internal iterator
// at the specified index
// the bool sets the direction of iteration
// true for forward iteration, false for backward
void ll_setitr(LNKDLST, int index, bool forward);


// initializes this list's internal iterator
// at the beginning of the list, iterating forwards
// equivalent to ll_setitr(lnkdlst, 0, true);
void ll_setitrF(LNKDLST);


// initializes this list's internal iterator
// at the end of the list, iterating backwards
// equivalent to:
// ll_setitr(lnkdlst, ll_size(lnkdlst) - 1, false);
void ll_setitrB(LNKDLST);

// reverses the direction of this list's internal iterator
void ll_itrreverse(LNKDLST);

// checks if the list's internal iterator
// has items left to return
// useful for loop termination conditions
// must have made a call to a setitr function
// before using -- returns false if this is
// not the case
bool ll_hasnext(LNKDLST);

// retrieves and returnes the data at the position
// of the list's internal iterator, and advances it
// returns NULL if there are no items left to return
// of course, it would naturally return NULLs if you have
// stored NULLs in the list -- if you are doing this,
// you should use ll_hasnext to check if the iterator
// is at the end of the list
// must have made a call to a setitr function
// before using
void *ll_next(LNKDLST);

// exchanges the value at the position of the list's
// internal iterator with the given one, returning
// the old value
void *ll_exchange(LNKDLST, void *);

// close c++ support
#ifdef __cplusplus
}
#endif

#endif
