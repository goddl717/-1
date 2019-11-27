#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 8
//그래프 만들기.


typedef struct node {
	int y;
	int x;
	struct node *next;
}node;

node* adj[MAX*MAX];
int dy[MAX] = { -2,-1,1,2,2,1,-1,-2 };
int dx[MAX] = { 1,2,2,1,-1,-2,-2,-1 };
//갈 수 있는지 판단.
int can_go(int y, int x)
{
	//int num = x + y*MAX;
	if (y >= 0 && x >= 0 && y < MAX && x < MAX)
		return 1;
	return 0;
}
// num, y,x, adj를 받아서 연결을 하는 함수.
void insert(int num, int y, int x, node **first)
{
	node* temp;
	temp = (node *)malloc(sizeof(node));
	temp->next = NULL;
	temp->x = x;
	temp->y = y;

	//없으면 바로 연결.
	if (*first == NULL)
		*first = temp;
	else {
		temp->next = *first;
		*first = temp;
	}
	//있으면 앞에도 연결.
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

	//찾으면 출력
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
	//cnt +1 을 하면서 돌자 .
	temp = adj[sx + sy * MAX];
	//브루트 포스로 만들어 보자 .

	for (; temp; temp = temp->next)
	{
		// 갯수를 만들고,
		//
		// 돌면서 방문 안한 곳이 있으면 방문을 해서 탈출을 한다.
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
	//Y,X 순서//
	//scanf("%d %d", &m, &n);
	if (argc != 4)
	{
		exit(1);
	}
	m = atoi(argv[1]);
	n = atoi(argv[2]);
	filename = argv[3];
	f = fopen(filename, "w+");

	//adj리스트 생성.
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
	//연결 완료..

	visited[m*MAX + n] = 0;
	bfs(f, 1, n, m, visited);

	//system("pause");
}