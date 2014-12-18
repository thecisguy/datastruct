#include <stdlib.h>
#include <stdbool.h>
#include "lnkdlst.h"

struct LNKDLST {
	struct node *head;
	struct node *tail;
	int size;

	struct node *itr;
	bool forward;
};

struct node {
	void *data;
	struct node *next;
	struct node *previous;
};

LNKDLST ll_init(void) {
	LNKDLST newll;
	if ((newll = (LNKDLST) malloc(sizeof(struct LNKDLST))) == NULL)
		return NULL;
	struct node *initarr;
	if ((initarr = (struct node *) malloc(sizeof(struct node) * 2)) == NULL) {
		free(newll);
		return NULL;
	}

	newll->head = initarr;
	newll->tail = initarr + 1;
	newll->head->data = NULL;
	newll->tail->data = NULL;

	newll->itr = NULL;
	newll->forward = true;

	newll->head->next = newll->tail;
	newll->tail->next = NULL;
	newll->head->previous = NULL;
	newll->tail->previous = newll->head;
	newll->size = 0;
	
	return newll;
}

void ll_destroy(LNKDLST sacrifice) {
	struct node *nextinline = sacrifice->head->next;
	while (nextinline != sacrifice->tail) {
		struct node *tmp = nextinline->next;
		free(nextinline);
		nextinline = tmp;
	}

	// will also free tail, b/c they were malloc'd together
	free(sacrifice->head);

	free(sacrifice);
}

void ll_autodestroy(LNKDLST sacrifice) {
	struct node *nextinline = sacrifice->head->next;
	while (nextinline != sacrifice->tail) {
		struct node *tmp = nextinline->next;
		if (nextinline->data != NULL) {
			free(nextinline->data);
		}
		free(nextinline);
		nextinline = tmp;
	}

	// will also free tail, b/c they were malloc'd together
	free(sacrifice->head);

	free(sacrifice);
}

LNKDLST ll_clone(LNKDLST lnkdlst) {
	LNKDLST newll;
	if ((newll = ll_init()) == NULL)
		return NULL;
	struct node *item = lnkdlst->head->next;
	while (item != lnkdlst->tail) {
		ll_addlast(lnkdlst, item->data);
		item = item->next;
	}
	return newll;
}

LNKDLST ll_deepclone(LNKDLST lnkdlst, void *(*clone)(void *)) {
	LNKDLST newll;
	if ((newll = ll_init()) == NULL)
		return NULL;
	struct node *item = lnkdlst->head->next;
	while (item != lnkdlst->tail) {
		ll_addlast(lnkdlst, clone(item->data));
		item = item->next;
	}
	return newll;
}

// Conventional use
void ll_addnum(LNKDLST lnkdlst, void *data, int index) {
	// if index is past the end of the list, do nothing
	if (index > lnkdlst->size || index < 0)
		return;

	// initialize new node
	struct node *newnode;
	if ((newnode = (struct node *) malloc(sizeof(struct node *))) == NULL)
		return;
	newnode->data = data;

	// find spot in list to put the new node
	struct node *n = lnkdlst->head;
	int i = 0;
	while (i < index) {
		n = n->next;
		i++;
	}

	// place the new node in the list
	newnode->next = n->next;
	newnode->previous = n;
	n->next->previous = newnode;
	n->next = newnode;
	lnkdlst->size++;
}

void ll_addfirst(LNKDLST lnkdlst, void *data) {
	// initialize new node
	struct node *newnode;
	if ((newnode = (struct node *) malloc(sizeof(struct node *))) == NULL)
		return;
	newnode->data = data;

	// place the new node in the list
	newnode->next = lnkdlst->head->next;
	newnode->next->previous = newnode;
	newnode->previous = lnkdlst->head;
	lnkdlst->head->next = newnode;
	lnkdlst->size++;
}

void ll_addlast(LNKDLST lnkdlst, void *data) {
	// initialize new node
	struct node *newnode;
	if ((newnode = (struct node *) malloc(sizeof(struct node *))) == NULL)
		return;
	newnode->data = data;

	// place the new node in the list
	newnode->previous = lnkdlst->tail->previous;
	newnode->next = lnkdlst->tail;
	lnkdlst->tail->previous = newnode;
	newnode->previous->next = newnode;
	lnkdlst->size++;
}

void *ll_removenum(LNKDLST lnkdlst, int index) {
	// if index is past the end of the list, do nothing
	if (index >= lnkdlst->size || index < 0)
		return NULL;

	// find spot in list to remove node
	struct node *n = lnkdlst->head;
	int i = 0;
	while (i < index) {
		n = n->next;
		i++;
	}

	// remove node and return data
	struct node *deleteme = n->next;
	void *returnme = deleteme->data;
	n->next = deleteme->next;
	deleteme->next->previous = n;
	free(deleteme);
	lnkdlst->size--;
	return returnme;
}

void *ll_removefirst(LNKDLST lnkdlst) {
	// if list is empty, do nothing
	if (lnkdlst->size == 0)
		return NULL;

	//remove node and return data
	struct node *deleteme = lnkdlst->head->next;
	void *returnme = deleteme->data;
	lnkdlst->head->next = deleteme->next;
	deleteme->next->previous = lnkdlst->head;
	free(deleteme);
	lnkdlst->size--;
	return returnme;
}

void *ll_removelast(LNKDLST lnkdlst) {
	// if list is empty, do nothing
	if (lnkdlst->size == 0)
		return NULL;

	//remove node and return data
	struct node *deleteme = lnkdlst->tail->previous;
	void *returnme = deleteme->data;
	lnkdlst->tail->previous = deleteme->previous;
	deleteme->previous->next = lnkdlst->tail;
	free(deleteme);
	lnkdlst->size--;
	return returnme;
}

bool ll_removeitem(LNKDLST lnkdlst, void *data) {
	// if list is empty, do nothing
	if (lnkdlst->size == 0)
		return NULL;

	// find item to remove
	struct node *deleteme = lnkdlst->head->next;
	while (deleteme != lnkdlst->tail) {
		if (deleteme->data == data) {
			// item given has been found in a node
			deleteme->previous->next = deleteme->next;
			deleteme->next->previous = deleteme->previous;
			free(deleteme);
			lnkdlst->size--;
			return true;
		}
		deleteme = deleteme->next;
	}
	return false;
}

void *ll_getnum(LNKDLST lnkdlst, int index) {
	// if index is past the end of the list, do nothing
	if (index >= lnkdlst->size || index < 0)
		return NULL;

	// find spot in list to get node
	struct node *n = lnkdlst->head;
	int i = 0;
	while (i < index) {
		n = n->next;
		i++;
	}

	return n->next->data;
}

void *ll_getfirst(LNKDLST lnkdlst) {
	// if list is empty, do nothing
	if (lnkdlst->size == 0)
		return NULL;

	return lnkdlst->head->next->data;
}

void *ll_getlast(LNKDLST lnkdlst) {
	// if list is empty, do nothing
	if (lnkdlst->size == 0)
		return NULL;

	//remove node and return data
	return lnkdlst->tail->previous->data;
}

int ll_size(LNKDLST lnkdlst) {
	return lnkdlst->size;
}

int ll_indexof(LNKDLST lnkdlst, void *data) {
	int index = 0;
	struct node *item = lnkdlst->head->next;
	while (item != lnkdlst->tail) {
		if (item->data == data)
			return index;
		item = item->next;
		index++;
	}
	return -1;
}

bool ll_contains(LNKDLST lnkdlst, void *data) {
	return ll_indexof(lnkdlst, data) != -1;
}

// LIFO-style use
void ll_push(LNKDLST lnkdlst, void *data) {
	ll_addfirst(lnkdlst, data);
}

void *ll_pop(LNKDLST lnkdlst) {
	return ll_removefirst(lnkdlst);
}

void *ll_peek(LNKDLST lnkdlst) {
	return ll_getfirst(lnkdlst);
}

// FIFO-style use
void ll_add(LNKDLST lnkdlst, void *data) {
	ll_addlast(lnkdlst, data);
}

void *ll_remove(LNKDLST lnkdlst) {
	return ll_removefirst(lnkdlst);
}

//Iteration

void ll_setitr(LNKDLST lnkdlst, int index, bool forward) {
	// if index is past the end of the list, do nothing
	if (index >= lnkdlst->size || index < 0)
		return;

	// find spot in list to get node
	struct node *n = lnkdlst->head;
	int i = 0;
	while (i < index) {
		n = n->next;
		i++;
	}

	lnkdlst->itr = n->next;
	lnkdlst->forward = forward;
}

void ll_setitrF(LNKDLST lnkdlst) {
	// if list is empty, do nothing
	if (lnkdlst->size == 0)
		return;

	lnkdlst->itr = lnkdlst->head->next;
	lnkdlst->forward = true;
}

void ll_setitrB(LNKDLST lnkdlst) {
	// if list is empty, do nothing
	if (lnkdlst->size == 0)
		return;

	lnkdlst->itr = lnkdlst->tail->previous;
	lnkdlst->forward = false;
}

void ll_itrreverse(LNKDLST lnkdlst) {
	lnkdlst->forward = !lnkdlst->forward;
}

bool ll_hasnext(LNKDLST lnkdlst) {
	if (lnkdlst->itr == NULL ||
	    lnkdlst->itr == lnkdlst->tail ||
	    lnkdlst->itr == lnkdlst->head)
		return false;
	else
		return true;
}

void *ll_next(LNKDLST lnkdlst) {
	if (!ll_hasnext(lnkdlst))
		return NULL;

	void *returnme = lnkdlst->itr->data;
	lnkdlst->itr = lnkdlst->forward ? lnkdlst->itr->next : lnkdlst->itr->previous;
	return returnme;
}

void *ll_exchange(LNKDLST lnkdlst, void *data) {
	if (!ll_hasnext(lnkdlst))
		return NULL;

	void *temp = lnkdlst->itr->data;
	lnkdlst->itr->data = data;
	return temp;
}
