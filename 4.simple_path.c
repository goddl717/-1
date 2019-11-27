#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef struct node {
	char index;
	struct node* next;
}node;

node* adj[26];
char start, end;
int max = 0;

void insert(char index, node** first)
{
	node* temp;
	temp = (node*)malloc(sizeof(node));
	temp->next = NULL;
	temp->index = index;

	//������ �ٷ� ����.
	if (*first == NULL)
		*first = temp;
	else {
		temp->next = *first;
		*first = temp;
	}
	//������ �տ��� ����.
}
void path_print(FILE *f,char temp, int visited[26])
{
	if (visited[temp - 'A'] == -1)
	{
		return;
	}
	
	path_print(f,visited[temp - 'A'] + 'A', visited);
	fprintf(f,"%c -> ", visited[temp - 'A'] + 'A');

}

//cnt�� ���̸� ��Ÿ����.
int dfs(FILE *f, int cnt, int visited[26], char current)
{
	int i;

	if (cnt > 26) {
		return -1;
	}

	if (current == end)
	{
		//for (i = 0; i < cnt+2; i++)
		//	printf("%d ", visited[i]);
		//printf("\n");
		//recursive �� �Ἥ ���� ���߿� ���ͺ��� ����ϱ�.
		path_print(f,end, visited);
		fprintf(f,"%c\n", end);
		//����� ���� �������� ����.
		max++;
		return 0;
	}

	//������ ��忡�� ����� ���� �ľ��Ѵ�.
	node* temp = adj[current - 'A'];
	for (; temp; temp = temp->next)
	{
		//�湮���� ���ٸ� 
		if (visited[temp->index - 'A'] == -1)
		{
			visited[temp->index - 'A'] = current - 'A';
			dfs(f,cnt + 1, visited, temp->index);
			visited[temp->index - 'A'] = -1;
		}
	}


}
//���� �ִ� ��� ��� .
int main(void) {

	char input_name[20];
	char output_name[20];


	printf("�Է� ���� �̸��� �������� :");
	scanf("%s", input_name);

	printf("��� ���� �̸��� �������� :");
	scanf("%s", output_name);

	

	FILE *f = fopen(output_name, "w+");
	FILE* f2 = fopen(input_name, "r");

	

	int vertex, edge;

	char temp1, temp2;
	int visited[26];


	int i;
	for (i = 0; i < 26; i++)
	{
		adj[i] = NULL;
		visited[i] = -1;
	}
	fscanf(f2,"%d %d%*c%c %c\n", &vertex, &edge,&start,&end);
	

	
	for (i = 0; i < edge; i++)
	{
		
		fscanf(f2,"%c %c\n", &temp1, &temp2);
		if (temp1-'A' >=0 && temp1-'A' <26)
			insert(temp2, &adj[temp1 - 'A']);

	}
	dfs(f,0, visited, start);
	fprintf(f,"max : %d", max);
	printf("OUTPUT.TXT ������ Ȯ���ϼ���~\N");
}