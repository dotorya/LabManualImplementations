#include "fibonacciheap.h"

#include <stdio.h>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

typedef pair<int, int> pii;

vector <pii> conn[100050];
int dis[100050];
HeapNode* ptr[100050];
int main() {
	int N, M, i, j, S;
	/*scanf("%d %d %d", &N, &M, &S);
	for (i = 1; i <= M; i++) {
		int t1, t2, t3;
		scanf("%d %d %d", &t1, &t2, &t3);
		conn[t1].emplace_back(t3, t2);
	}*/
	N = 1000, S = 1;

	srand(123323);
	for (i = 1; i <= N; i++) {
		for (j = i+1; j <= N; j++) {
			conn[i].emplace_back(rand() + 1, j);
			conn[j].emplace_back(rand() + 1, i);
		}
	}

	FibonacciHeap *Hx = new FibonacciHeap();
	memset(dis, 0x3f, sizeof(dis));
	dis[S] = 0;
	ptr[S] = Hx->insert(0, S);
	while (Hx->size != 0) {
		HeapNode* u = Hx->extract_min();
		
		int d = u->key, n = u->value;
		for (auto it : conn[n]) {
			if (dis[it.second] <= it.first + d) continue;
			dis[it.second] = it.first + d;
			if (ptr[it.second]) Hx->decrease_key(ptr[it.second], dis[it.second]);
			else ptr[it.second] = Hx->insert(dis[it.second], it.second);
		}
		ptr[n] = NULL;
		delete u;
	}

	for (i = 1; i <= N; i++) {
		if (dis[i] == 0x3f3f3f3f) printf("INF\n");
		else printf("%d\n", dis[i]);
	}
	return 0;
}