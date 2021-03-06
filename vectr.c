/* vectr.c
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

#include <stdlib.h>
#include <string.h>

#include "vectr.h"

struct VECTR {
	void *data;
	size_t size;
	size_t capacity;
	size_t item_size;
};

static size_t nlpo2(size_t x);

VECTR vc_init(size_t initial_size, size_t item_size) {
	VECTR newvc;
	if ((newvc = malloc(sizeof(struct VECTR))) == NULL)
		goto out;

	newvc->size = 0;
	newvc->capacity = nlpo2(initial_size);
	newvc->item_size = item_size;

	if ((newvc->data = malloc(newvc->capacity * item_size)) == NULL) {
		free(newvc);
		goto out;
	}

	out:
		return newvc;
}

// computes the next largest power of 2 of x
// this is a fairly well-known algorithm,
// modified to work on size_t values of any wordsize.
//
// later we may want to create a _Generic version with
// hardcoded calculations for 32- and 64- bit size_ts,
// but for now this is good enough, as sizeof() values
// are known at compile-time, and therefore optimizing compilers
// that can unroll loops will very likely generate the fastest
// possible code anyway.
static size_t nlpo2(size_t x) {
	if (x == 1)
		goto out;

	x--;
	for (size_t i = 1; i < sizeof(size_t) * 8; i *= 2) {
		x |= (x >> i);
	}
	x++;

	out:
	return x;
}

void vc_destroy(VECTR vc) {
	free(vc->data);
	free(vc);
}

VECTR vc_clone(VECTR vc) {
	VECTR clone;
	if ((clone = vc_init(vc->size, vc->item_size)) == NULL)
			goto out;

	memcpy(clone->data, vc->data, vc->size * vc->item_size);

	out:
	return clone;
}

size_t vc_size(VECTR vc) {
	return vc->size;
}

size_t vc_capacity(VECTR vc) {
	return vc->capacity;
}

ssize_t vc_indexof(VECTR vc, const void *item) {
	ssize_t index = 0;
	while (index < vc->size &&
			memcmp(vc->data + index * vc->item_size, item, vc->item_size) != 0)
		index++;
	return index == vc->size ? -1 : index;
}

void vc_pushback(VECTR vc, const void *item) {
	if (vc->size == vc->capacity) {
		size_t newcap = nlpo2(vc->size + 1);
		void *newdata;
		if ((newdata = realloc(vc->data, newcap * vc->item_size)) == NULL)
			goto out;
		vc->data = newdata;
		vc->capacity = newcap;
	}

	memcpy(vc->data + vc->size++ * vc->item_size, item, vc->item_size);

	out:
	return;
}

void *vc_get(VECTR vc, size_t index) {
	void *val = NULL;
	if (index >= vc->size)
		goto out;

	val = vc->data + index * vc->item_size;

	out:
	return val;
}

void vc_updatesize(VECTR vc, size_t new_size) {
	vc->size = new_size;
}

void vc_updatecapacity(VECTR vc, size_t new_capacity) {
	if (new_capacity == 0) {
		vc_destroy(vc);
	}

	size_t realnewcap = nlpo2(new_capacity);
	if (realnewcap != vc->capacity) {
		void *newdata;
		if ((newdata = realloc(vc->data, realnewcap * vc->item_size)) == NULL)
			goto out;
		vc->data = newdata;
		vc->capacity = realnewcap;
	}

	if (new_capacity < vc->size)
		vc->size = new_capacity;

	out:
	return;
}
