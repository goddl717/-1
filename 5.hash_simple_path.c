#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
// 해쉬 테이블의 크기를 몇으로 할까 ?
// 26개 해도 충분한데, 더 줄일수도 있나?
typedef struct node {
	char index;
	struct node* next;

}node;
int cnt = 0;

node *hash[26];

// hash function 은 어떻게 만들까 
// 대문자에 대한 값으로 해쉬 함수를 만든다.
int hash_func(char temp)
{
	return temp - 'A';
}

//value는 어떻게 집어 넣을까 ?
//overflow 는 어떻게 해결을 하나??
//linear probing 은 안좋은 방법이다 
//처음부터 링크드 리스트를 만든다

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

//찾을때에는 최
//넣으면서 찾아서 계산횟수를 줄이고 //
//중복되는 것으,B C C B 를 없앤다.

void check1(FILE *f, char start, char end)
{
	
	node *temp = hash[hash_func(end)];
	for (; temp; temp = temp->next)
	{
		char temp_index = temp->index;
		if (start == temp_index)
		{
			fprintf(f, "연결된 정보 : %c %c\n", end, start);
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

	printf("input file 이름을 입력하세요\n");
	scanf("%s", input);
	FILE *f = fopen(input, "r");

	printf("output file 이름을 입력하세요\n");
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