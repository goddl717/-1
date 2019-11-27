#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 8
//�׷��� �����.


typedef struct node {
	int y;
	int x;
	struct node *next;
}node;

node* adj[MAX*MAX];
int dy[MAX] = { -2,-1,1,2,2,1,-1,-2 };
int dx[MAX] = { 1,2,2,1,-1,-2,-2,-1 };
//�� �� �ִ��� �Ǵ�.
int can_go(int y, int x)
{
	//int num = x + y*MAX;
	if (y >= 0 && x >= 0 && y < MAX && x < MAX)
		return 1;
	return 0;
}
// num, y,x, adj�� �޾Ƽ� ������ �ϴ� �Լ�.
void insert(int num, int y, int x, node **first)
{
	node* temp;
	temp = (node *)malloc(sizeof(node));
	temp->next = NULL;
	temp->x = x;
	temp->y = y;

	//������ �ٷ� ����.
	if (*first == NULL)
		*first = temp;
	else {
		temp->next = *first;
		*first = temp;
	}
	//������ �տ��� ����.
}

int bfs(FILE *f, int cnt, int sy, int sx, int visited[MAX*MAX])
{
	int nx, ny;
	int num;
	int min = 999;
	int index = -1;
	int cnt1 = 0;
	node* temp;
	int mx, my;

	int x, y, i, j;

	//ã���� ���
	if (cnt == MAX * MAX)
	{
		for (i = 0; i < MAX; i++)
		{
			for (j = 0; j < MAX; j++)
				fprintf(f, "%2d ", visited[i * MAX + j]);
			fprintf(f, "\n");

		}
		fprintf(f, "======================\n");
		fclose(f);

		return 1;
	}
	//cnt +1 �� �ϸ鼭 ���� .
	temp = adj[sx + sy * MAX];
	//���Ʈ ������ ����� ���� .

	for (; temp; temp = temp->next)
	{
		// ������ �����,
		//
		// ���鼭 �湮 ���� ���� ������ �湮�� �ؼ� Ż���� �Ѵ�.
		if (visited[temp->x + (temp->y)*MAX] == -1)
		{
			visited[temp->x + (temp->y)*MAX] = cnt;
			if (bfs(f, cnt + 1, temp->y, temp->x, visited) == 1)
				return 1;
			visited[temp->x + (temp->y)*MAX] = -1;
		}
	}


	return -1;
}

int main(int argc, char *argv[])
{
	int visited[MAX*MAX];
	int i, j, k, nx, ny;
	int num = 0;
	int m, n;
	char * filename;
	FILE *f;
	//Y,X ����//
	//scanf("%d %d", &m, &n);
	if (argc != 4)
	{
		exit(1);
	}
	m = atoi(argv[1]);
	n = atoi(argv[2]);
	filename = argv[3];
	f = fopen(filename, "w+");

	//adj����Ʈ ����.
	for (i = 0; i < MAX*MAX; i++)
		adj[i] = NULL;

	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
			visited[i*MAX + j] = -1;

	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
		{
			num = i * MAX + j;
			for (k = 0; k < MAX; k++)
			{
				ny = i + dy[k];
				nx = j + dx[k];
				if (can_go(ny, nx) == 1)
					insert(num, ny, nx, &adj[num]);
			}
		}
	//���� �Ϸ�..

	visited[m*MAX + n] = 0;
	bfs(f, 1, n, m, visited);

	//system("pause");
}