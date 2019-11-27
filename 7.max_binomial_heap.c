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
//������ ��ġ�� ������ �ִ� �Լ��� �ʿ��ϴ�. ���߿� ����.
//a�� �ϳ��� �߰��Ǿ����� �����ϴ� �Լ�.
//����� ���� merge

//a�� ���.
//b�� �ϳ�.
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
		//���� �տ� �ִ� ���
		//����տ� �ִ� ���
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
//������ ����� a���� merge �ϱ�.
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
		//�ٸ��� ����.
		if (temp->degree != next->degree)
		{
			pre = temp;
			temp = temp->link;
			next = temp->link;
			continue;

		}
		// �ڷ� �ΰ��� ������ ���
		// ���� ���ٸ� ��ĭ �� ����.
		if (temp->link != NULL && next->link != NULL)
			if ((next->degree == temp->degree) && (temp->degree == next->link->degree))
			{
				pre = temp;
				temp = temp->link;
				next = temp->link;
				continue;
			}

		//next�� ������ 
		if (temp->link != NULL)
		{
			if (next->degree == temp->degree)
			{
				//temp�� ���� ���.
				if (temp->data > next->data)
				{
					temp->link = next->link;
					next->link = temp->child;
					temp->child = next;
					temp->degree++;
					next = temp->link;

				}
				//temp�� ū ���
				else {
					if (pre != NULL) {
						pre->link = next;
						temp->link = next->child;
						next->child = temp;
						next->degree++;
						temp = next;
					}
					//temp�� ū ���
					else {
						temp->link = next->child;
						next->child = temp;
						next->degree++;
						*a = next;
						temp = next;
						next = temp->link;

						continue;
						//���Ⱑ �� �̻��ѵ�
						//pre�� ���� ���.
						//�������Ű���.
					}
				}
			}
		}
		//pre = temp;
		//������ ����.
	}
}
//�ϳ��� ���ö� ó���ϴ� ��.
//���� ���ķ� ���� �ϸ�ȴ�.


//��� ������ �տ� ������ �ȴ�. 
//a�� b�� ���������� �� a �� ��ġ�� ����� �ؼ� �־�� �ȴ�.
void init(node** heap, int key) {
	node* nodetemp;

	nodetemp = (node*)malloc(sizeof(node));
	nodetemp->data = key;
	nodetemp->child = NULL;
	nodetemp->link = NULL;
	nodetemp->degree = 0;
	//�ϳ��� ������ head�� �����Ѵ�.
	if (*heap != NULL) {
		nodetemp->link = *heap;
		*heap = nodetemp;
	}
	else {
		*heap = nodetemp;
	}
	//���Ͼտ� �־ merge�� �����غ���.
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
//min ã��.
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

// ���� ������ ������ �Ǿ������� ������ �ƴϹǷ� 
// 
void print_tree(node* a) {
	//�ڽ��� ����ϰ� �ڽĺ��� print_node �� �ִ´�.
	node* temp = a;
	int i = 0;

	for (; temp; temp = temp->link) {
		printf("\nB[%d] :", i++);
		printf("%d(%d) ", temp->data, temp->degree);
		print_node(temp->child);
	}
}
//����� ��ȯ����.
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

//���鼭 degree �� ������ �ִٸ� merge �� ����,
//������ Ż��
int main() {
	int n;
	int temp;
	node* heap = NULL;
	node* heap2 = NULL;
	node* temp2;
	int i = 0;

	scanf("%d", &n);
	//degree, key ���� ���õ� ����Ʈ�� �����ؼ� 
	//���ﶧ���� ���ο� ����� ���� �ϸ� �ȴ�.
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

	//temp2�� ��ġ�� ��ȯ�Ѵ�.
	//��������
	int min_te = getMin(heap);
	temp2 = deleteMin(&heap, min_te);
	printf("\nmax : %d\n", temp2->data);
	//child�� �ϳ����������� ����
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