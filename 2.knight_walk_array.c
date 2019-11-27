#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX 8

int dy[MAX] = { -2,-1,1,2,2,1,-1,-2 };
int dx[MAX] = { 1,2,2,1,-1,-2,-2,-1 };

// arr -1�̸� ���� ���� ���� // ���������� 1�� ��ȯ
int can_go(int y, int x, int arr[5][6])
{
	if (y >= 0 && x >= 0 && y < 5 && x < 6 && arr[y][x] == -1)
		return 1;

	return 0;
}
// ���� ��ġ���� ���� �ִ� ����� ��.
int count1(int y, int x, int arr[5][6])
{
	int i = 0, ny, nx;
	int ret = 0;

	for (i = 0; i < 8; i++)
	{
		ny = y + dy[i];
		nx = x + dx[i];
		if (can_go(ny, nx, arr) == 1)
			ret++;

	}
	return ret;
}
//����Լ��� ��� ����
int knight_tour(FILE *f, int arr[5][6], int y, int x, int cnt)
{
	int visited[8];
	int min = 999;
	int index = -1;
	int i, j;
	int ny, nx;
	//��� ���� �� ���Ҵٸ� Ż��
	for (i = 0; i < 8; i++)
		visited[i] = 0;

	if (cnt == MAX * MAX)
	{
		arr[y][x] = cnt;
		for (i = 0; i < 5; i++)
		{
			for (j = 0; j < 6; j++)
				printf("%2d ", arr[i][j]);
			printf(f,"\n");

		}
		printf("----------------\n");
	

		return 1;
	}

	while (1) {
		//���� ���� ���Ҹ� ã��.
		for (i = 0; i < 8; i++) {
			ny = y + dy[i];
			nx = x + dx[i];
			//�� �� ������ 
			if ((can_go(ny, nx, arr) == 1))
			{
				// ���� ���� ���� ã�� �Ⱦ����� �ϳ��� �̴´�.
				if (min > count1(ny, nx, arr) && visited[i] == 0)
				{
					min = count1(ny, nx, arr);
					index = i;
					visited[index] = 1;
				}
			}

		}
		// �� �߿��� ���� ���� ���� �� ���������� �ݺ����� Ż���Ѵ�.
		if (index == -1)
			break;
		// ���� ���� ��츦 ���������� ���� ���� �����Ѵ�.
		if (index != -1) {

			ny = y + dy[index];
			nx = x + dx[index];

			arr[ny][nx] = cnt;
			// �ϳ��� ��츦 ã���� �ٷ� ����
			if (knight_tour(f,arr, ny, nx, cnt + 1) == 1)
				return 1;
			// �� �� ô�ϱ�.
			arr[ny][nx] = -1;
		}
		//���� ���.
		index = -1;
		min = 999;
		for (i = 0; i < 8; i++)
			visited[i] = 0;
	}
	// ��� ���� ���Ӵµ� ������ʿ� ���� ������ ��θ� ��ã��.
	return 0;
}


int main(void)
{
	int i, j;
	int m, n;
	int arr[MAX][MAX];
	FILE *f;
	//m�� �� ù ��ġ

	//scanf("%d %d", &m, &n);

	//�ȵ�� ������ -1�� ����
	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
			arr[i][j] = -1;

	// 
	m = 4;
	n = 5;

	arr[m][n] = 0;
	if (knight_tour(f,arr, m, n, 1) == 1)
		printf("��ΰ� ��µ˴ϴ�.\n");
	else
		printf("��ΰ� �����ϴ�.");


	//���ϴ� ��°�.


	//system("pause");

}