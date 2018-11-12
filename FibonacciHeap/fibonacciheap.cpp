#include <limits.h>
#include "fibonacciheap.h"

void linkedlist_insert(HeapNode* src, HeapNode* dst) {
	HeapNode* nxt = dst->right;

	dst->right = src;
	src->left = dst;
	src->right = nxt;
	nxt->left = src;
}
void linkedlist_merge(HeapNode* n1, HeapNode* n2) {
	HeapNode* n3 = n2->left;
	HeapNode* n4 = n1->right;

	n1->right = n2;
	n2->left = n1;
	n3->right = n4;
	n4->left = n3;
}

HeapNode* FibonacciHeap::insert(int key, int value) {
	HeapNode* node = new HeapNode(key, value);

	if (min == NULL) {
		node->left = node->right = node;
		min = node;
	}
	else {
		linkedlist_insert(node, min);
		if (node->key < min->key) min = node;
	}
	size++;

	return node;
}
HeapNode* FibonacciHeap::minimum() {
	return min;
}
void FibonacciHeap::consolidate() {
	HeapNode* arr[75];
	for (int i = 0; i < 75; i++) arr[i] = NULL;

	int cnt = 0;
	HeapNode* cur = min;
	do {
		cnt++;
		cur = cur->right;
	} while (cur != min);

	cur = min;
	while(cnt--) {
		HeapNode* x = cur;
		int deg = x->degree;
		while (arr[deg] != NULL) {
			HeapNode* y = arr[deg];
			if (x->key > y->key) {
				HeapNode *xl = x->left, *xr = x->right;
				HeapNode *yl = y->left, *yr = y->right;
				if (xr == y && yr == x);
				else if (xr == y) {
					xl->right = y, y->left = xl;
					y->right = x, x->left = y;
					x->right = yr, yr->left = x;
				}
				else if (yr == x) {
					yl->right = x, x->left = yl;
					x->right = y, y->left = x;
					y->right = xr, xr->left = y;
				}
				else {
					yl->right = x, x->left = yl;
					x->right = yr, yr->left = x;
					xl->right = y, y->left = xl;
					y->right = xr, xr->left = y;
				}
				HeapNode* tu = x;
				x = y;
				y = tu;
				cur = x;
			}

			// FIB-HEAP-LINK(y, x)
			y->left->right = y->right;
			y->right->left = y->left;
			y->parent = x;
			if (x->child == NULL) {
				x->child = y;
				y->left = y->right = y;
			}
			else {
				HeapNode *ln = x->child, *rn = x->child->right;
				ln->right = y, rn->left = y;
				y->left = ln, y->right = rn;
			}
			x->degree++, y->mark = false;

			arr[deg] = NULL;
			deg++;
		}
		arr[deg] = x;
		cur = cur->right;
	}

	min = NULL;
	for (int i = 0; i < 75; i++) {
		if (arr[i] == NULL) continue;
		if (min == NULL) min = arr[i];
		else if (min->key > arr[i]->key) min = arr[i];
	}
}
HeapNode* FibonacciHeap::extract_min() {
	if (min == NULL) return min;

	HeapNode* z = min;
	while (z->child != NULL) {
		HeapNode *x = z->child;
		HeapNode *ln = x->left, *rn = x->right;
		if (x == rn) z->child = NULL;
		else {
			ln->right = rn;
			rn->left = ln;
			z->child = rn;
		}
		linkedlist_insert(x, min);
		x->mark = false;
		x->parent = NULL;
	}
	z->left->right = z->right;
	z->right->left = z->left;
	if (z == z->right) min = NULL;
	else {
		min = z->right;
		consolidate();
	}
	size--;

	return z;
}
void FibonacciHeap::decrease_key(HeapNode* ptr, int key) {
	if (key > ptr->key) {
#ifdef FIBONACCIHEAP_DEBUG
		printf("decrease_key: New key is greater than current key. Nothing happened.\n");
#endif
		return;
	}

	ptr->key = key;
	HeapNode* p = ptr->parent;
	if (p != NULL && p->key > ptr->key) {
		HeapNode *x = ptr, *y = p;
		while(1) {
			if (x == x->right) y->child = NULL;
			else {
				if (y->child == x) y->child = x->right;
				x->left->right = x->right;
				x->right->left = x->left;
			}
			y->degree--;
			linkedlist_insert(x, min);
			x->parent = NULL;
			x->mark = false;

			if (y->parent == NULL) break;
			if (!y->mark) {
				y->mark = true;
				break;
			}
			x = y, y = y->parent;
		}
	}
	if (ptr->key < min->key) min = ptr;
}
void FibonacciHeap::delete_node(HeapNode* ptr) {
	decrease_key(ptr, INT_MIN);
	HeapNode* mn = extract_min();
	delete mn;
}

FibonacciHeap* union_heap(FibonacciHeap* H1, FibonacciHeap* H2) {
	if (H1->size == 0) {
		delete H1;
		return H2;
	}
	if (H2->size == 0) {
		delete H2;
		return H1;
	}

	H1->size += H2->size;
	linkedlist_merge(H1->min, H2->min);
	if (H1->min->key > H2->min->key) H1->min = H2->min;
	delete H2;
	return H1;
}