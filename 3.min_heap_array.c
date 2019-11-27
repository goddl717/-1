#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int heapcount = 0;
int* heap;
//call by address.
void swap1(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
	return;

};

//���� max heap �� ��� ..
//�׳� ��ȣ�� �ִ� ��쿡 ���� �� ��ȣ�� �ٲٸ� �ȴ�.


int delete1(int* heap) {
	// ù��°���� ���� 
	int ret = heap[1];
	// ���¸� ���߱� ���ؼ� ��ȯ .
	swap1(&heap[1], &heap[heapcount]);
	heapcount--;

	int parent = 1;
	int child = parent * 2;

	// �� �� ���� ���� ����. 
	if (child + 1 <= heapcount) {
		child = (heap[child] < heap[child + 1]) ? child : child + 1;
	}

	//������ ���� ���� ������ �ø���. //
	// �ڽĳ�� �� �� �� ���� ���̶� �ٲ۴�. 
	while (child <= heapcount && heap[parent] > heap[child]) {
		swap1(&heap[parent], &heap[child]);

		parent = child;
		child = child * 2;

		if (child + 1 <= heapcount) {
			child = (heap[child] < heap[child + 1]) ? child : child + 1;
		}
	}
	return ret;
}
void insert(int temp, int* heap)
{
	//���� �������� ����
	heap[++heapcount] = temp;
	int child = heapcount;
	int parent = heapcount / 2;
	//���� �θ� ũ�� �ö󰣴�.
	//�׸��� �θ�� �ڽ��ڸ��� ����.

	while (child > 1 && heap[child] < heap[parent])
	{
		swap1(&heap[child], &heap[parent]);
		child = parent;
		parent = child / 2;
	}
}

void print_heap(int* heap, int n) {
	int i;
	int sum = 1;
	int j = 1;
	printf("root node : ");
	for (i = 1; i < n + 1; i++)
	{
		printf("%d ", heap[i]);

		if (i == sum) {
			printf("\n");
			printf("leve %d node :", j + 1);
			sum += (int)pow(2.0, j++);
		}
	}
	printf("\n\n");
}
//������ 1�� ��ȯ
int check(int* heap, int temp)
{
	int i;
	for (i = 1; i <= heapcount; i++)
	{
		if (heap[i] == temp)
			return 1;
	}
	return 0;

}
int main(void)
{

	int n, i;
	int temp;
	int value;
	FILE* f = fopen("input.txt", "r");

	fscanf(f, "%d\n", &n);
	heap = (int*)malloc(sizeof(int) * n);

	for (i = 0; i < n; i++) {
		fscanf(f, "%d", &temp);
		insert(temp, heap);

	}
	print_heap(heap, heapcount);
	while (1)
	{
		printf("Select menu and input the number(1: insert, 2 : delete) : \n");

		scanf("%d", &temp);
		if (temp == 1)
		{
			scanf("%d", &value);
			if (check(heap, value) == 1)
			{
				printf("�ߺ��� ���Դϴ� �ٸ� ���� �Է����ּ���\n");
				continue;
			}
			insert(value, heap);
			print_heap(heap, heapcount);
		}
		else if (temp == 2)
		{
			printf("%d\n", delete1(heap));
			print_heap(heap, heapcount);
		}
	}
}