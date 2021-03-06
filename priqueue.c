/* priqueue.h
 * 
 * Copyright (C) 2014-2015 - Blake Lowe
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
#include <stdbool.h>
#include "lnkdlst.h"
#include "priqueue.h"

struct PRIQUEUENODE {
	void *data;
	PRIQUEUENODE left, right;
};

struct PRIQUEUE {
	LNKDLST binqueue;
	int (*compar)(const void *, const void *);
};

static PRIQUEUENODE pair(PRIQUEUENODE p, PRIQUEUENODE q,
		int (*compar)(const void *, const void *));
static PRIQUEUENODE new_priqueuenode(void *data);

static PRIQUEUENODE new_priqueuenode(void *data) {
	PRIQUEUENODE npqn = (PRIQUEUENODE)
		malloc(sizeof(struct PRIQUEUENODE));
	if (!npqn)
		goto out;

	npqn->left = NULL;
	npqn->right = NULL;
	npqn->data = data;

out:
	return npqn;
}

PRIQUEUE pq_init(int (*compar)(const void *, const void *)) {
	PRIQUEUE npq = (PRIQUEUE) malloc(sizeof(struct PRIQUEUE));
	if (!npq)
		goto out;

	npq->binqueue = ll_init();
	if (!npq->binqueue)
		goto out_bq;
	npq->compar = compar;

	goto out;

out_bq:
	free(npq);
	npq = NULL;
out:
	return npq;
}

static PRIQUEUENODE pair(PRIQUEUENODE p, PRIQUEUENODE q,
		int (*compar)(const void *, const void *)) {
	if (compar(p->data, q->data) < 0) {
		p->right = q->left;
		q->left = p;
		return q;
	} else {
		q->right = p->left;
		p->left = q;
		return p;
	}
}

PRIQUEUENODE pq_insert(PRIQUEUE pq, void *v) {
	PRIQUEUENODE c, t;
	c = t = new_priqueuenode(v);
	if (!t)
		goto out;
	
	ll_setitrF(pq->binqueue);
	while (ll_hasnext(pq->binqueue)) {
		if (ll_itrpeek(pq->binqueue) == NULL) {
			(void) ll_exchange(pq->binqueue, c);
			break;
		}
		c = pair(c, ll_itrpeek(pq->binqueue), pq->compar);
		(void) ll_exchange(pq->binqueue, NULL);
		(void) ll_next(pq->binqueue);
	}
	if (!ll_hasnext(pq->binqueue)) {
		ll_add(pq->binqueue, c);
	}

out:
	return t;
}

void *pq_remove(PRIQUEUE pq) {
	void *v = NULL;
	PRIQUEUE temp = pq_init(pq->compar);
	if (!temp)
		goto out;

	int i = 0, max = -1;
	ll_setitrF(pq->binqueue);
	while (ll_hasnext(pq->binqueue)) {
		PRIQUEUENODE w = ll_next(pq->binqueue);
		if (w != NULL)
			if ((max == -1) || (pq->compar(w->data, v) > 0)) {
				max = i;
				v = w->data;
			}
		i++;
	}
	if (max == -1)
		goto out;

	ll_setitr(pq->binqueue, max, true);
	PRIQUEUENODE x = ((PRIQUEUENODE) ll_itrpeek(pq->binqueue))->left;
	for (i = max; i > 0; i--) {
		PRIQUEUENODE y = x->right;
		x->right = NULL;
		ll_push(temp->binqueue, x);
		x = y;
	}
	free(ll_exchange(pq->binqueue, NULL));
	if (max == ll_size(pq->binqueue) - 1)
		(void) ll_removelast(pq->binqueue);
	pq_join(pq, temp);

out:
	return v;
}
