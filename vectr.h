/* vectr.h
 * 
 * Copyright (C) 2015 - Blake Lowe
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

#ifndef VECTR_H
#define VECTR_H

#include <stdbool.h>
#include <stdlib.h>

// prepare for c++ support
#ifdef __cplusplus
extern "C" {
#endif

typedef struct VECTR *VECTR;

/* Initialize and Destroy */

// allocates and returns a new vectr with enough initial
// space to store initial_size items of item_size bytes.
// returns NULL if memory could not be allocated
VECTR vc_init(size_t initial_size, size_t item_size);

// destroys and de-allocates memory for a vectr
// after calling this method, it is illegal to
// use the vectr for anything else
void vc_destroy(VECTR);

// returns a copy of a VECTR (including contents)
// returns NULL if memory could not be allocated
VECTR vc_clone(VECTR);

/* Conventional use */

// returns a pointer to the actual memory managed by this vector.
// you can use this pointer as the main way to conveniently access data
// stored in the vector by casting it to a pointer of the appropriate type.
//
// note: if an operation is performed which causes this vectr to be resized,
// this pointer may become stale. it would be wise to update your value
// by re-calling this method after such a resize is made.
void *vc_data(VECTR);

// returns the number of elements currently stored in this vectr.
size_t vc_size(VECTR);

// returns the number of elements this vectr can store without resizing.
size_t vc_capacity(VECTR);

// returns the index of the first occurance
// of the given item in the vectr,
// or -1 if it is not present
ssize_t vc_indexof(VECTR, const void *item);

// adds the given item to the end of the vectr by copying
// its data, increasing the size by 1.
// this function performs in constant time amortized, as it may
// cause the vectr to be resized (iff the new size would exceed
// the vectr's capacity).
void vc_pushback(VECTR, const void *item);

// returns a pointer to the index-th element of the vector
//
// the main advantage to using this function instead of adding to
// the pointer returned by vc_data is that this function is
// range-checked: it returns NULL if the index is outside of
// the array bounds (i.e. is is greater than or equal to the
// vector's size)
void *vc_get(VECTR, size_t index);

// close c++ support
#ifdef __cplusplus
}
#endif

#endif
