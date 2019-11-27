#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int arr1[10001];
int arr_a[10001];
int arr_b[10001];


#define SWAP(a,b,temp) { (temp)=(a); (a)=(b) ;(b)=(temp);	};
typedef struct {
	int key;
} element;

typedef struct leftist* leftistTree;

typedef struct leftist {
	leftistTree leftChild;
	element data;
	leftistTree rightChild;
	int shortest;
}leftist;

int search_depth(leftist * temp) {
	int ret;
	//널이면 0을 주고,
	if (temp == NULL)
		return 0 ;

	else {
		if (search_depth(temp->leftChild) >= search_depth(temp->rightChild)) 
			ret = search_depth(temp->leftChild) + 1;
		else 
			ret = search_depth(temp->rightChild) + 1;		
	}
}

void minUnion(leftistTree* a, leftistTree* b)
{
	leftistTree temp;
	//크기에 따라서 스왑.
	if ((*a)->data.key > (*b)->data.key) SWAP(*a, *b, temp);
	if (!(*a)->rightChild) (*a)->rightChild = *b;
	else minUnion(&(*a)->rightChild, b);
	if (!(*a)->leftChild) {
		(*a)->leftChild = (*a)->rightChild;
		(*a)->rightChild = NULL;
	}
	else if ((*a)->leftChild->shortest < (*a)->rightChild->shortest)
		SWAP((*a)->leftChild, (*a)->rightChild, temp);

	(*a)->shortest = (!(*a)->rightChild) ? 1 : (*a)->rightChild->shortest + 1;
}

//왼쪽에 큰것을 만들어서 minUnion을 실행한다.
void minMeld(leftistTree* a, leftistTree* b)
{
	if (!*a) *a = *b;
	else if (*b) minUnion(a, b);
	*b = NULL;
}

void arr_change(int i, leftistTree start,int* arr) {
	//배열에 넣는 연산
	if (start == NULL)
		return;
	else {
		arr[i] = start->data.key;
		if (start->leftChild != NULL)
			arr_change(2 * i, start->leftChild,arr);
		if (start->rightChild != NULL)
			arr_change(2 * i + 1, start->rightChild,arr);
	}
}

int CheckPowerOfTwo(int nNum)
{
	int nResult = nNum & (nNum - 1);
	if (nResult == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
void print_tree(FILE *f, char * name, leftistTree * start,int *arr) {
	int i;
	fprintf(f,"%s\n", name);
	for (i = 1; i < pow(2, search_depth(start)); i++)
	{
		if (arr[i] == 0)
			fprintf(f, "- ");
		else
			fprintf(f, "%d ", arr[i]);

		if (CheckPowerOfTwo(i + 1) == 1)
			fprintf(f, "\n");

	}
	fprintf(f, "\n");

}


int main(void) {
	char input[30],output[30];
	printf("input 이름을 입력하세요 :");
	scanf("%s", input);

	printf("output 이름을 입력하세요 :");
	scanf("%s", output);

	
	FILE* fr = fopen(input,"r");
	FILE* fw = fopen(output, "w");


	int n1, n2;
	int i, j;
	leftist* start = NULL;
	leftist* start1 = NULL;


	int value;


	fscanf(fr,"%d\n", &n1);


	for (i = 0; i < n1; i++) {
		fscanf(fr,"%d", &value);
		//값을 받고, 
		leftistTree temp = NULL;
		temp = (leftist*)malloc(sizeof(leftist));
		temp->data.key = value;
		temp->leftChild = NULL;
		temp->rightChild = NULL;
		temp->shortest = 1;
		minMeld(&start, &temp);
	}
	arr_change(1, start, arr_a);
	print_tree(fw,"a", start,arr_a);
	fscanf(fr,"%d\n", &n2);
	for (i = 0; i < n2; i++)
	{
		fscanf(fr,"%d", &value);
		leftistTree temp = NULL;
		temp = (leftist*)malloc(sizeof(leftist));
		temp->data.key = value;
		temp->leftChild = NULL;
		temp->rightChild = NULL;
		temp->shortest = 1;
		minMeld(&start1, &temp);
	}
	arr_change(1, start1, arr_b);
	print_tree(fw, "b",start1,arr_b);
	minMeld(&start, &start1);
	arr_change(1,start,arr1);
	print_tree(fw, "after meld",start,arr1);
	fprintf(fw, "\n종료!\n");

	fclose(fr);
	fclose(fw);


}