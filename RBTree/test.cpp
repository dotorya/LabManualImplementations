#include "rbtree.h"

#include <stdio.h>
#include <assert.h>
using namespace std;

#pragma warning(disable:4996)

int main() {
	RBTree* tr = new RBTree();

	tr->insert(41);
	tr->insert(38);
	tr->insert(31);
	tr->insert(12);
	tr->insert(19);
	tr->insert(8);
	
	assert(!tr->erase(9));
	tr->erase(8);
	tr->erase(12);
	tr->erase(19);
	tr->erase(31);
	tr->erase(38);
	tr->erase(41);

	tr->insert(41);
	tr->insert(38);
	tr->insert(31);
	tr->insert(12);
	tr->insert(19);
	tr->insert(8);

	RBNode* u = tr->search(9);
	if (u != tr->nil) {
		printf("WRONG: search is not nil\n");
		return 0;
	}
	u = tr->search(8);
	while (u != tr->nil) {
		printf("%d ", u->key);
		u = tr->successor(u);
	}
	printf("\n");

	u = tr->search(41);
	while (u != tr->nil) {
		printf("%d ", u->key);
		u = tr->predecessor(u);
	}
	printf("\n");
	
	printf("MAX = %d\n", tr->maximum(tr->root)->key);
	printf("MIN = %d\n", tr->minimum(tr->root)->key);
	return 0;
}
