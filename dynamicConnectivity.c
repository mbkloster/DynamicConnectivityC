#include <stdlib.h>
#include <stdio.h>

typedef struct QuickUnion
{
	int id[10];
	int treeSize[10];
} QuickUnion;

enum Boolean
{
	FALSE,
	TRUE
};

void quickUnionInit(struct QuickUnion* quickU)
{
	for (int i = 0; i < 10; ++i) {
		quickU->id[i] = i;
		quickU->treeSize[i] = 1;
	}
}

int quickUnionFindRoot(struct QuickUnion* quickU, int i) 
{
	while(i != quickU->id[i]) {
		quickU->id[i] = quickU->id[quickU->id[i]]; //Make each node point to it's parent through path compression
		i = quickU->id[i];
	}
	return i;
}

enum Boolean quickUnionCheckConnected(struct QuickUnion* quickU, int p, int q)
{
	if (quickUnionFindRoot(quickU, p) == quickUnionFindRoot(quickU, q))
		return TRUE;
	else return FALSE;
}

void quickUnionJoin(struct QuickUnion* quickU, int p, int q)
{
	int i = quickUnionFindRoot(quickU, p);
	int j = quickUnionFindRoot(quickU, q);
	if(quickU->treeSize[i] < quickU->treeSize[j]) { //Check the weights of each tree, connect the smaller subsets to the larger ones. Results in NlogN complexity for Union
		quickU->id[i] = j;
		quickU->treeSize[j] += quickU->treeSize[i];
	}
	else {
		quickU->id[j] = i;
		quickU->treeSize[i] += quickU->treeSize[j];
	}
}

void quickUnionGetIds(struct QuickUnion* quickU)
{
	printf("Ids: [");
	for(int i = 0; i < 10; ++i) {
		printf(" %d,", quickU->id[i]);
	}
}


int main(int argc, char *argv[])
{
	QuickUnion *testUnion = (QuickUnion*) malloc(sizeof(QuickUnion));
	quickUnionInit(testUnion);

	quickUnionJoin(testUnion, 0, 8);

	quickUnionGetIds(testUnion);

	return 0;
}

