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

// like ll_destroy, but also calls free()
// (from stdlib.h) on each non-null datem
// in the lnkdlst
void ll_autodestroy(LNKDLST);

// returns a shallow copy of a LNKDLST
LNKDLST ll_clone(LNKDLST);

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

// close c++ support
#ifdef __cplusplus
}
#endif

#endif
