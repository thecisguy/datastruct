/* priqueue.h
 * 
 * Copyright (C) 2014 - Blake Lowe
 *
 * This file is part of datastruct.
 * 
 * datastruct is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * datastruct is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with datastruct. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PRIQUEUE_H
#define PRIQUEUE_H

#include <stdbool.h>

// prepare for c++ support
#ifdef __cplusplus
extern "C" {
#endif

typedef struct PRIQUEUE *PRIQUEUE;
typedef struct PRIQUEUENODE *PRIQUEUENODE;

/* Initialize and Destroy */

// allocates and returns a new, empty priqueue
// returns null if memory could not be allocated
// compar is as in stdlib.h's qsort, and is used
// by the priqueue to perform comparisons.
// positive return value -> arg1 is higher priority than arg2
// negative return value -> arg1 is lower priority than arg2
PRIQUEUE pq_init(int (*compar)(const void *, const void *));

// destroys and de-allocates memory for a priqueue
// after calling this method, it is illegal to
// use the priqueue for anything else
// this method does not free the data stored
// in the list
//
void pq_destroy(PRIQUEUE);

// like pq_destroy, but also calls free
// (from stdlib.h) on each non-null datem
// in the priqueue
void pq_autodestroy(PRIQUEUE);

// returns a shallow copy of a PRIQUEUE
PRIQUEUE pq_clone(PRIQUEUE);

// returns a deep copy of a PRIQUEUE,
// by calling clone on each item.
// clone should take a pointer to an item
// stored in the list and return a pointer to
// a copy of that item.
PRIQUEUE pq_deepclone(PRIQUEUE, void *(*clone)(void *));

/* Utility Methods */

// inserts an item into the priqueue
// returns a link to its node
PRIQUEUENODE pq_insert(PRIQUEUE, void *);

// removes and returns the highest-priority item
// in the priqueue
void *pq_remove(PRIQUEUE);

// retrieves, but does not remove, the
// highest-priority item in the priqueue
void *pq_get(PRIQUEUE);

// replaces the stored item with a new one
void pq_change(PRIQUEUE, PRIQUEUENODE, void *);

// removes the item at the specified node from
// the priqueue
void pq_removenode(PRIQUEUE, PRIQUEUENODE);

// merges the second priqueue into the first one
// invalidates and frees the second priqueue, but
// nodes pointing to items from that priqueue will
// remain valid, now safely inside the first priqueue
void pq_join(PRIQUEUE dest, PRIQUEUE src);

// tests if item is present in list
bool pq_contains(PRIQUEUE, void *);

// returns the number of data in the list
int pq_size(PRIQUEUE);

// retrieves the datem stored in the given node
void *pq_getnode(PRIQUEUENODE);

// close c++ support
#ifdef __cplusplus
}
#endif

#endif
