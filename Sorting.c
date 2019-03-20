#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

int chkOrder(int *, int);
int printArray(int *, int, int);
int sort_merge(int *, int);
int sort_quick(int *, int);
int heapify(int *, int, int);
int sort_heap(int *, int);

int sort_merge(int *toSort, int szToSort)
{
	if(szToSort<2)
		return 99;

	int i=0;
	int idxA=0;
	int idxB=(szToSort/2);
	int idxSorted=0;
	int *sorted=calloc(szToSort, sizeof(int));

	sort_merge(toSort, szToSort/2);
	sort_merge(toSort+szToSort/2, (szToSort-szToSort/2));

	while(idxA<(szToSort/2) && idxB<szToSort)
		*(sorted+idxSorted++)=(toSort[idxA]<toSort[idxB]? toSort[idxA++]: toSort[idxB++]);

	memcpy((sorted+idxSorted), (idxA<(szToSort/2)? &toSort[idxA]: &toSort[idxB]),(idxA<(szToSort/2)? (((szToSort/2)-idxA)*sizeof(int)): ((szToSort-idxB)*sizeof(int))));
	memcpy(toSort, sorted, szToSort*sizeof(int));

	free(sorted);
	return 0;
}

int sort_quick(int *toSort, int szToSort)
{
	//Ending Case
	if(szToSort<3)
	{
		sort_merge(toSort, szToSort);
		return 99;
	}

	int i=0;
	int idxFront=0;
	int idxRear=szToSort-2;
	int vluPivot=toSort[szToSort-1];

	//Processing portion
	while(idxFront<idxRear)
	{
		while(toSort[idxFront]<vluPivot)
			idxFront++;
		while(toSort[idxRear]>vluPivot)
			idxRear--;
		if(idxFront<idxRear)
		{
			toSort[idxFront]^=toSort[idxRear];
			toSort[idxRear]^=toSort[idxFront];
			toSort[idxFront++]^=toSort[idxRear--];
		}
	}
	toSort[szToSort-1]=(toSort[szToSort-1]>toSort[idxFront]? toSort[++idxFront]: toSort[idxFront]);
	toSort[idxFront]=vluPivot;

	//Recursive portion
	sort_quick(&toSort[0], idxFront++);
	sort_quick(&toSort[idxFront], szToSort-idxFront);
	return 0;
}

int heapify(int *toHeapify, int szToHeapify, int idxRoot)
{
	int idxShouldBeRoot=idxRoot;
	int idxLeftChild=idxRoot*2+1;
	int idxRightChild=idxRoot*2+2;

	//Check if any of the children is greater than the root
	if(idxLeftChild<szToHeapify && toHeapify[idxLeftChild]>toHeapify[idxShouldBeRoot])
		idxShouldBeRoot=idxLeftChild;
	if(idxRightChild<szToHeapify && toHeapify[idxRightChild]>toHeapify[idxShouldBeRoot])
		idxShouldBeRoot=idxRightChild;

	//Swap the content of the root with the content of greater one
	if(idxShouldBeRoot!=idxRoot)
	{
		toHeapify[idxShouldBeRoot]^=toHeapify[idxRoot];
		toHeapify[idxRoot]^=toHeapify[idxShouldBeRoot];
		toHeapify[idxShouldBeRoot]^=toHeapify[idxRoot];
		//Heapify again on the swapped node
		heapify(toHeapify, szToHeapify, idxShouldBeRoot);
	}
	return 0;
}

int sort_heap(int *toSort, int szToSort)
{
	int i;

	//Heapify the whole array
	for(i=szToSort/2-1; i>=0; i--)
		heapify(toSort, szToSort, i);

//printf("A:\n");
//printArray(toSort, szToSort, 0);

	//Pop from root of the heap one-by-one to the end of the array to the head of the array
	for(i=szToSort-1; i>0; i--)
	{
		toSort[i]^=toSort[0];
		toSort[0]^=toSort[i];
		toSort[i]^=toSort[0];
		heapify(toSort, i, 0);
	}

//printf("B:\n");
//printArray(toSort, szToSort, 0);

	return 0;
}

int main(int argc, char **argv)
{
	if(argc<3 || strtol(*(argv+2), NULL, 10)<1)
	{
		printf("./a.out [size of elements] [number of digits for element()]\n");
		return 1;
	}
	srand(time(0));
	int rtn=99;
	int i=0;
	int szToSort=strtol(*(argv+1), NULL, 10);
	int modulator=1;
	int *toSort=calloc(szToSort, sizeof(int));

	for(i=0; i<strtol(*(argv+2), NULL, 10); i++)
		modulator*=10;

	for(i=0; i<szToSort; i++)
		toSort[i]=(rand()%modulator);
/*
int dbgToSort[]={6,9,5,8,8,2,3,3,5,7};
free(toSort);
toSort=dbgToSort;
szToSort=sizeof(dbgToSort)/sizeof(int);
*/
	printf("Before:\n");
	rtn=printArray(toSort, szToSort, 2);

	rtn=sort_merge(toSort, szToSort);
	//rtn=sort_quick(toSort, szToSort);
	//rtn=sort_heap(toSort, szToSort);

	printf("After:\n");
	rtn=printArray(toSort, szToSort, 2);

	return 0;
}

int chkOrderAscending(int *toSort, int szToSort)
{
	int i=0;
	for(i=0; i<szToSort-1; i++)
		if(toSort[i]>toSort[i+1])
			return 0;
	return 1;
}

int printArray(int *toPrint, int szToPrint, int option)
{
	int i=0;
	int sum=0;
	while(i<szToPrint)
	{
		sum+=toPrint[i];
		printf("%d ", toPrint[i++]);
	}

	switch(option)
	{
		case 2:
			printf("=> Ascending=%s,\t", (chkOrderAscending(toPrint, szToPrint)? "True": "False"));
		case 1:
			printf("=> sum=%d", sum);
		default:
			printf("\n");
			break;
	}

	return 0;
}

