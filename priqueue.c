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
