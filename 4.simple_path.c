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

	//없으면 바로 연결.
	if (*first == NULL)
		*first = temp;
	else {
		temp->next = *first;
		*first = temp;
	}
	//있으면 앞에도 연결.
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

//cnt가 길이를 나타낸다.
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
		//recursive 를 써서 가장 나중에 들어간것부터 출력하기.
		path_print(f,end, visited);
		fprintf(f,"%c\n", end);
		//경우의 수가 더하지면 더함.
		max++;
		return 0;
	}

	//현재의 노드에서 연결된 것을 파악한다.
	node* temp = adj[current - 'A'];
	for (; temp; temp = temp->next)
	{
		//방문한적 없다면 
		if (visited[temp->index - 'A'] == -1)
		{
			visited[temp->index - 'A'] = current - 'A';
			dfs(f,cnt + 1, visited, temp->index);
			visited[temp->index - 'A'] = -1;
		}
	}


}
//갈수 있는 모든 경우 .
int main(void) {

	char input_name[20];
	char output_name[20];


	printf("입력 파일 이름을 적으세요 :");
	scanf("%s", input_name);

	printf("출력 파일 이름을 적으세요 :");
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
	printf("OUTPUT.TXT 파일을 확인하세요~\N");
}