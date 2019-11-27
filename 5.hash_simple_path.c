#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
// �ؽ� ���̺��� ũ�⸦ ������ �ұ� ?
// 26�� �ص� ����ѵ�, �� ���ϼ��� �ֳ�?
typedef struct node {
	char index;
	struct node* next;

}node;
int cnt = 0;

node *hash[26];

// hash function �� ��� ����� 
// �빮�ڿ� ���� ������ �ؽ� �Լ��� �����.
int hash_func(char temp)
{
	return temp - 'A';
}

//value�� ��� ���� ������ ?
//overflow �� ��� �ذ��� �ϳ�??
//linear probing �� ������ ����̴� 
//ó������ ��ũ�� ����Ʈ�� �����

//shA :secure hashing algorithm 

void insert(int index, char value)
{
	node *temp = (node*)malloc(sizeof(temp));
	temp->index = value;
	temp->next = NULL;


	if (hash[index] == NULL)
		hash[index] = temp;
	else {
		temp->next = hash[index];
		hash[index] = temp;
	}
}

//ã�������� ��
//�����鼭 ã�Ƽ� ���Ƚ���� ���̰� //
//�ߺ��Ǵ� ����,B C C B �� ���ش�.

void check1(FILE *f, char start, char end)
{
	
	node *temp = hash[hash_func(end)];
	for (; temp; temp = temp->next)
	{
		char temp_index = temp->index;
		if (start == temp_index)
		{
			fprintf(f, "����� ���� : %c %c\n", end, start);
			cnt++;
		}
	}

}


int main(void)
{
	int vertex, edge;
	int i;
	char temp1, temp2;
	char input[20];
	char output[20];

	printf("input file �̸��� �Է��ϼ���\n");
	scanf("%s", input);
	FILE *f = fopen(input, "r");

	printf("output file �̸��� �Է��ϼ���\n");
	scanf("%s", output);
	FILE *f2 = fopen(output, "w+");


	for (i = 0; i < 26; i++)
		hash[i] = NULL;

	fscanf(f, "%d %d", &vertex, &edge);

	for (i = 0; i < edge; i++)
	{
		fscanf(f, "\n%c %c", &temp1, &temp2);
		insert(hash_func(temp1), temp2);
		check1(f2, temp1, temp2);

	}
	fprintf(f2, "cnt = %d\n", cnt);
	fprintf(f2,"--------------\n");

}