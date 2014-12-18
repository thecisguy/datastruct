#include <stdlib.h>
#include <stdbool.h>
#include "lnkdlst.h"

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
	PRIQUEUENODE t;
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
		c = pair(c, ll_itrpeek(pq->binqueue));
		(void) ll_exchange(pq->binqueue, NULL);
		(void) ll_next(pq->binqueue);
	}
	if (!ll_hasnext(pq->binqueue)) {
		ll_add(pq->binqueue, c);
	}

out:
	return t;
}
