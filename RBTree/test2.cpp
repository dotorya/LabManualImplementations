#include "rbtree.h"
#include <stdio.h>
#pragma warning(disable:4996)
int main() {
	RBTree* tr = new RBTree();
	int N, i;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) {
		int t;
		scanf("%d", &t);
		if (t) tr->insert(t);
	}

	RBNode* v = tr->minimum(tr->root);

	int cnt = 0;
	while (v != tr->nil) {
		cnt++;
		v = tr->successor(v);
	}
	return !printf("%d\n", cnt);
}