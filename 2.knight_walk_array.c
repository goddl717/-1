#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define MAX 8

int dy[MAX] = { -2,-1,1,2,2,1,-1,-2 };
int dx[MAX] = { 1,2,2,1,-1,-2,-2,-1 };

// arr -1이면 들어가지 않은 상태 // 갈수있으면 1을 반환
int can_go(int y, int x, int arr[5][6])
{
	if (y >= 0 && x >= 0 && y < 5 && x < 6 && arr[y][x] == -1)
		return 1;

	return 0;
}
// 현재 위치에서 갈수 있는 경우의 수.
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
//재귀함수로 계속 진행
int knight_tour(FILE *f, int arr[5][6], int y, int x, int cnt)
{
	int visited[8];
	int min = 999;
	int index = -1;
	int i, j;
	int ny, nx;
	//모든 곳을 다 돌았다면 탈출
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
		//가장 작은 원소를 찾기.
		for (i = 0; i < 8; i++) {
			ny = y + dy[i];
			nx = x + dx[i];
			//갈 수 있으면 
			if ((can_go(ny, nx, arr) == 1))
			{
				// 가장 작은 것을 찾되 안쓴것중 하나를 뽑는다.
				if (min > count1(ny, nx, arr) && visited[i] == 0)
				{
					min = count1(ny, nx, arr);
					index = i;
					visited[index] = 1;
				}
			}

		}
		// 그 중에서 가장 작은 것을 고를 수없을때는 반복문을 탈출한다.
		if (index == -1)
			break;
		// 가장 작은 경우를 뽑을때에는 다음 것을 수행한다.
		if (index != -1) {

			ny = y + dy[index];
			nx = x + dx[index];

			arr[ny][nx] = cnt;
			// 하나의 경우를 찾으면 바로 종료
			if (knight_tour(f,arr, ny, nx, cnt + 1) == 1)
				return 1;
			// 안 간 척하기.
			arr[ny][nx] = -1;
		}
		//새로 경신.
		index = -1;
		min = 999;
		for (i = 0; i < 8; i++)
			visited[i] = 0;
	}
	// 모두 돌고 나왓는데 기저사례에 들어가지 않으면 경로를 못찾음.
	return 0;
}


int main(void)
{
	int i, j;
	int m, n;
	int arr[MAX][MAX];
	FILE *f;
	//mㅜ 은 첫 위치

	//scanf("%d %d", &m, &n);

	//안들어 갔으면 -1로 갱신
	for (i = 0; i < MAX; i++)
		for (j = 0; j < MAX; j++)
			arr[i][j] = -1;

	// 
	m = 4;
	n = 5;

	arr[m][n] = 0;
	if (knight_tour(f,arr, m, n, 1) == 1)
		printf("경로가 출력됩니다.\n");
	else
		printf("경로가 없습니다.");


	//원하는 출력값.


	//system("pause");

}