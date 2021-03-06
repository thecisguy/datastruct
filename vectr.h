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

#include <sys/types.h>

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

// returns the index of the first occurrence
// of the given item in the vectr,
// or -1 if it is not present
ssize_t vc_indexof(VECTR, const void *item);

// adds the given item to the end of the vectr by copying
// its data, increasing the size by 1.
// this function performs in constant time amortized, as it may
// cause the vectr to be resized (iff the new size would exceed
// the vectr's capacity).
//
// if this operation would cause the vector to be resized, but
// additional memory is not available, this function has
// no effect whatsoever on the vectr.
void vc_pushback(VECTR, const void *item);

// returns a pointer to the index-th element of the vector
//
// the main advantage to using this function instead of adding to
// the pointer returned by vc_data is that this function is
// range-checked: it returns NULL if the index is outside of
// the array bounds (i.e. is is greater than or equal to the
// vector's size)
void *vc_get(VECTR, size_t index);

// updates the value of this vector's size.
//
// this can be used to "delete" unwanted items at the end of the array,
// by providing a number smaller than its current size.
//
// alternatively, by providing a larger number, it can be used to notify
// the vectr that you have added new items beyond its current size
// (but, obviously, within its current capacity) by means of writing to
// the block of memory returned by vc_data.
//
// if new_size is greater than the vectr's capacity, the result is undefined.
void vc_updatesize(VECTR, size_t new_size);

// ensures that there is enough space in the vector to store
// at least new_capacity items. the actual capacity the vectr
// ends up with is implementation-defined.
//
// if the new capacity would be the same as the old capacity,
// there is no effect (besides potentially updating size, see below).
// otherwise, a resize is performed. if the resize cannot be performed,
// for example, due to a lack of memory, this function has no effect
// whatsoever on the vectr.
//
// if new_capacity is 0, the effect is to destroy the vector; see vc_destroy.
// if new_capacity is smaller than the current size, the values
// from indices [capacity, size) may be lost permanently, depending
// on the capacity the vectr actually ends up with. size will be set
// to the value of new_capacity.
void vc_updatecapacity(VECTR, size_t new_capacity);

// close c++ support
#ifdef __cplusplus
}
#endif

#endif
