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
// 바퀴벌레가 모두 방문했는 지 판단하는 함수

int check(int m, int n) {
		int i = 0, j = 0;
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
			if (visited[i][j] == 0)
				return -1;

	return 1;
};
//check를 하면서 몇번만에 모두 방문하는지 확인하는 함수
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

	//마지막을 저장하는 전역변수.
	lastx = cx;
	lasty = cy;
	lastsum = sum;
	return sum;
}
//1000번째 마지막 위치
//마지막번째 방문 회수
//1000번의 평균 .
int main(int argc, char* argv[])
{
	if (argc != 4) {
	puts("number error");
		printf("갯수는 %d개입니다 ", argc);
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
	printf("평균 : %lf\n", avg / 1000);
	printf("마지막 위치 : %d %d\n", lastx, lasty);
	printf("마지막 방문 횟수\n");
	for (i = 0; i < m; i++)
	{
	for (j = 0; j < n; j++)
	printf("%3d ", visited[i][j]);
	printf("\n");
	}
	*/

	fprintf(f, "마지막 위치 : %d %d\n", lastx, lasty);
	fprintf(f, "마지막 방문 횟수\n");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			fprintf(f, "%3d ", visited[i][j]);
		fprintf(f, "\n");
	}
	fprintf(f, "평균 : %.2lf\n", avg / 1000);
	fclose(f);
	return 0;

}



// 한발 멀러서서 로직을 제대로 이해해보자.

// 2.9.10번 문제를 푸는데 배열에서 푸시오, 그래프로 푸시오.

// stack permutation 은 장기 과제로 풀어보자.

