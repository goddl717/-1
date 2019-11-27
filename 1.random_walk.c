#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

int dir[8][2] = { { -1,1 },{ 0,1 },{ 1,1 },{ 1,0 },{ 1,-1 },{ 0,-1 },{ -1,-1 },{ -1,0 } };
int **visited;
int lastx, lasty;
int lastsum;
// ���������� ��� �湮�ߴ� �� �Ǵ��ϴ� �Լ�

int check(int m, int n) {
		int i = 0, j = 0;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			if (visited[i][j] == 0)
				return -1;

	return 1;
};
//check�� �ϸ鼭 ������� ��� �湮�ϴ��� Ȯ���ϴ� �Լ�
int gogo(int m, int n)
{
	int sum = 0;
	int i = 0, j = 0;
	int nx, ny;
	int random;
	int cx, cy;
	
	visited[m / 2][n / 2] = 1;
	cy = m / 2;
	cx = n / 2;
	while (check(m, n) == -1)
	{
		random = rand() % 8;
		nx = cx + dir[random][0];
		ny = cy + dir[random][1];
		if (nx < 0 || ny < 0 || nx >= m || ny >= n)
			continue;

		visited[ny][nx]++;
		cx = nx;
		cy = ny;
	}

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			sum += visited[i][j];

	//�������� �����ϴ� ��������.
	lastx = cx;
	lasty = cy;
	lastsum = sum;
	return sum;
}
//1000��° ������ ��ġ
//��������° �湮 ȸ��
//1000���� ��� .
int main(int argc, char* argv[])
{
	if (argc != 4) {
	puts("number error");
		printf("������ %d���Դϴ� ", argc);
		system("pause");	
	}

	if (argv[1] <= 0 || argv[2] <= 0)
	{
		puts("range error");
		system("pause");
	}
	srand(time(NULL));
	int m, n;
	int i = 0, j = 0;
	double avg = 0;
	int k = 0;

	FILE *f = fopen(argv[3], "w");
	//scanf("%d %d", &m, &n);
	m = atoi(argv[1]);
	n = atoi(argv[2]);
	visited = (int **)malloc(sizeof(int)*m);

	for (i = 0; i<m; i++)
		visited[i] = (int*)malloc(sizeof(int)*n);

	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			visited[i][j] = 0;
	
	while (k < 1000) {
		for (i = 0; i < m; i++)
			for (j = 0; j < n; j++)
				visited[i][j] = 0;

		avg += gogo(m, n);
		k++;
	}
	/*
	printf("��� : %lf\n", avg / 1000);
	printf("������ ��ġ : %d %d\n", lastx, lasty);
	printf("������ �湮 Ƚ��\n");
	for (i = 0; i < m; i++)
	{
	for (j = 0; j < n; j++)
	printf("%3d ", visited[i][j]);
	printf("\n");
	}
	*/

	fprintf(f, "������ ��ġ : %d %d\n", lastx, lasty);
	fprintf(f, "������ �湮 Ƚ��\n");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			fprintf(f, "%3d ", visited[i][j]);
		fprintf(f, "\n");
	}
	fprintf(f, "��� : %.2lf\n", avg / 1000);
	fclose(f);
	return 0;

}



// �ѹ� �ַ����� ������ ����� �����غ���.

// 2.9.10�� ������ Ǫ�µ� �迭���� Ǫ�ÿ�, �׷����� Ǫ�ÿ�.

// stack permutation �� ��� ������ Ǯ���.

