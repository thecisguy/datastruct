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
// but for now this is good enough.
static size_t nlpo2(size_t x) {
	for (size_t i = 1; i < sizeof(size_t) * 8; i *= 2) {
		x |= (x >> i);
	}
	return(x+1);
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
