#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define SWAP(a,b,temp) { (temp)=(a); (a)=(b) ;(b)=(temp);};

typedef struct node {
	int data;
	int degree;
	struct node* child;
	struct node* link;

}node;
//적절한 위치에 넣을수 있는 함수가 필요하다. 나중에 구현.
//a에 하나가 추가되었을때 실행하는 함수.
//연결된 이후 merge

//a는 긴거.
//b는 하나.
node* proper_insert(node** a, node* b) {

	if (*a == NULL)
	{
		*a = b;
		return *a;
	}
	node* temp = *a;
	node* pre = NULL;
	node* next = NULL;

	for (; temp; temp = temp->link)
	{
		//가장 앞에 넣는 경우
		//가장앞에 넣는 경우
		if (pre == NULL && temp->degree >= b->degree)
		{
			b->link = *a;
			*a = b;
			return *a;
		}

		if (temp->link == NULL)
		{
			temp->link = b;
			return *a;
		}

		if (temp->link != NULL)
		{
			next = temp->link;
			if ((b->degree > temp->degree) && (b->degree <= next->degree))
			{
				b->link = next;
				temp->link = b;
				return *a;
			}
		}
		pre = temp;
	}
}
//적절히 연결된 a에서 merge 하기.
void merge(node** a) {
	if (!*a)
		return;
	node* temp = *a;
	node* pre = NULL;
	node* next = NULL;

	if (temp->link != NULL)
		next = temp->link;

	while (temp != next && next != NULL)
	{
		//다르면 전진.
		if (temp->degree != next->degree)
		{
			pre = temp;
			temp = temp->link;
			next = temp->link;
			continue;

		}
		// 뒤로 두개가 더있을 경우
		// 값이 같다면 한칸 더 전진.
		if (temp->link != NULL && next->link != NULL)
			if ((next->degree == temp->degree) && (temp->degree == next->link->degree))
			{
				pre = temp;
				temp = temp->link;
				next = temp->link;
				continue;
			}

		//next가 있으면 
		if (temp->link != NULL)
		{
			if (next->degree == temp->degree)
			{
				//temp가 작은 경우.
				if (temp->data > next->data)
				{
					temp->link = next->link;
					next->link = temp->child;
					temp->child = next;
					temp->degree++;
					next = temp->link;

				}
				//temp가 큰 경우
				else {
					if (pre != NULL) {
						pre->link = next;
						temp->link = next->child;
						next->child = temp;
						next->degree++;
						temp = next;
					}
					//temp가 큰 경우
					else {
						temp->link = next->child;
						next->child = temp;
						next->degree++;
						*a = next;
						temp = next;
						next = temp->link;

						continue;
						//여기가 좀 이상한데
						//pre가 들어가는 경우.
						//괜찮은거같음.
					}
				}
			}
		}
		//pre = temp;
		//이전꺼 저장.
	}
}
//하나가 들어올때 처리하는 것.
//들어갈때 정렬로 들어가게 하면된다.


//얘는 무조건 앞에 넣으면 된다. 
//a에 b를 넣을때에는 그 a 의 위치를 제대로 해서 넣어야 된다.
void init(node** heap, int key) {
	node* nodetemp;

	nodetemp = (node*)malloc(sizeof(node));
	nodetemp->data = key;
	nodetemp->child = NULL;
	nodetemp->link = NULL;
	nodetemp->degree = 0;
	//하나가 들어오면 head에 연결한다.
	if (*heap != NULL) {
		nodetemp->link = *heap;
		*heap = nodetemp;
	}
	else {
		*heap = nodetemp;
	}
	//제일앞에 넣어서 merge로 수행해보자.
	merge(heap);
}

void print_node(node* a) {
	if (a == NULL) {
		return;
	}
	printf("%d(%d) ", a->data, a->degree);
	print_node(a->link);
	print_node(a->child);
}
//min 찾기.
int getMin(node* a) {
	node* temp = a;
	int temp_min = temp->data;

	for (; temp; temp = temp->link)
	{
		if (temp_min <= temp->data)
			temp_min = temp->data;
	}
	return temp_min;
}

// 제일 위에는 연결은 되어있지만 연결이 아니므로 
// 
void print_tree(node* a) {
	//자신을 출력하고 자식부터 print_node 에 넣는다.
	node* temp = a;
	int i = 0;

	for (; temp; temp = temp->link) {
		printf("\nB[%d] :", i++);
		printf("%d(%d) ", temp->data, temp->degree);
		print_node(temp->child);
	}
}
//지우고 반환하자.
node* deleteMin(node** a, int temp_min) {
	node* temp = *a;
	node* pre = NULL;
	node* child = NULL;
	for (; temp; temp = temp->link)
	{
		if (temp->data == temp_min)
			break;
		pre = temp;
	}
	if (pre != NULL)
		pre->link = temp->link;

	else {
		*a = temp->link;
	}
	return temp;
}

//돌면서 degree 가 같은게 있다면 merge 를 수행,
//없으면 탈출
int main() {
	int n;
	int temp;
	node* heap = NULL;
	node* heap2 = NULL;
	node* temp2;
	int i = 0;

	scanf("%d", &n);
	//degree, key 간의 소팅된 리스트로 유지해서 
	//지울때에는 새로운 헤더를 만들어서 하면 된다.
	for (int i = 0; i < n; i++)
	{
		printf("inserting ");
		scanf("%d", &temp);
		init(&heap, temp);
		print_tree(heap);
		printf("\n");
	}
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		printf("inserting ");
		scanf("%d", &temp);
		init(&heap2, temp);
		print_tree(heap2);
		printf("\n");
	}

	node* next;
	node* pre;
	node* temp3;
	temp2 = heap2;

	while (temp2)
	{
		temp3 = temp2->link;
		temp2->link = NULL;
		heap = proper_insert(&heap, temp2);
		merge(&heap);
		temp2 = temp3;
	}
	printf("merging two bheapts of heap1 and heap2");
	print_tree(heap);
	printf("\n");

	//temp2에 위치를 반환한다.
	//이전꺼랑
	int min_te = getMin(heap);
	temp2 = deleteMin(&heap, min_te);
	printf("\nmax : %d\n", temp2->data);
	//child를 하나씩넣을려고 만듬
	node* child = temp2->child;

	while (child)
	{
		temp3 = child->link;
		child->link = NULL;
		heap = proper_insert(&heap, child);
		merge(&heap);
		child = temp3;
	}
	print_tree(heap);

	min_te = getMin(heap);
	temp2 = deleteMin(&heap, min_te);
	printf("\nmax : %d\n", temp2->data);
	child = temp2->child;

	while (child)
	{
		temp3 = child->link;
		child->link = NULL;
		heap = proper_insert(&heap, child);
		merge(&heap);
		child = temp3;
		//print_tree(heap);
	}
	print_tree(heap);
}