#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef struct node {
	int value;
	struct node* next;
	struct node* left;
	struct node* right;
	struct node* parent;
	
}node;
struct node * first = NULL;
struct node* end = NULL;

void insert(int value)
{
	//생성
	node* new1 = (node*)malloc(sizeof(node));

	new1->value = value;
	new1->left = NULL;
	new1->right = NULL;
	new1->next = NULL;
	
	new1->parent = NULL;

	//맨 처음에 아무것도 없으면 처음 들어온 것이 first가 됨.
	if (first == NULL ) {
		first = new1;
		end = new1;
		return;
	}

	node* temp;
	temp = first;
	//뒤에 연결하고 새로운 노드를 가장 뒤로 갱신.
	end->next = new1;
	end = new1;

	// 처음부터 돌면서 처음 만나는 자식이 없는 노드에 연결을 한다 
	// 왼쪽이 없으면 왼쪽에 // 왼쪽은 있고 오른쪽은 없으면 오른쪽에
	// 둘다 있으면 다음껄로 넘어간다.
	// 부모도 연결한다.
	temp = first;
	for (; temp; temp = temp->next)
	{
		if (temp->left == NULL) {
			temp->left = new1;
			new1->parent = temp;
			break;
		}
		else if (temp->right == NULL) {
			temp->right = new1;
			new1->parent = temp;
			break;
		}
	}

	//가장 뒤에 있는 노드를 // 힙 구조에 맞게 올린다.

	temp = end;


	
	node* parent = temp->parent;
	node* child = temp;

	while (parent != NULL && child->value < parent->value) {
		//자식이 작으면 스왑.
		int temp_value = parent->value;
		parent->value = child->value;
		child->value = temp_value;
		//자식위치 변경
		child = parent;
		parent = parent->parent;
	}
}
//가장 위에 것을 빼고, 가장 뒤에껏을 위에 넣고 내려오면서 값을 자신의 위치에 들어간다.
int pop() {
	
	int ret = first->value;
	int last_value = end->value;

	// end와 연결된 부모관계 연결 해제
	if (end == first)
	{
		free(first);
		return ret;
	}

	if (end->parent->right != NULL)
		end->parent->right = NULL;
	else 
		end->parent->left = NULL;

	end->parent = NULL;

	//end 와 연결된 next 연결해제
	node* temp = first;
	for (; temp; temp = temp->next)
	{
		if (temp->next == end)
		{
			temp->next = NULL;
			end = temp;
		}
	}
	
	//제일 뒤에 있는 것을 값으로 넣는다.
	first->value = last_value;
	node* parent = first;
	node* child;

	//자식중에서 작은 것을 뽑는다.

	if (parent->right == NULL)
		child = parent->left;
	else if (parent->right->value < parent->left->value)
		child = parent->right;
	else if (parent->right->value > parent->left->value)
		child = parent->left;
	else {
		return ret;
	}

	while (child != NULL && child->value < parent->value)
	{
		int temp_value = parent->value;
		parent->value = child->value;
		child->value = temp_value;

		parent = child;

		if (parent->right == NULL)
			child = parent->left;
		else if (parent->right->value < parent->left->value)
			child = parent->right;
		else if (parent->right->value > parent->left->value)
			child = parent->left;
	}

	return ret;
}
int istwo(int n)
{
	int ret = n & n - 1;
	if (ret == 0)
		return 1;
	else
		return 0;


}
void print_node() {
	
	node* temp;
	temp = first;
	int i = 1;
	int sum = 1;
	int j = 1;
	printf("root node : ");
	for (; temp; temp = temp->next)
	{
		printf("%d ", temp->value);
		if (istwo(i+1) == 1)
		{
			printf("\n");
			printf("leve %d node :", j + 1);
			j++;
		}
		i++;
	}
	printf("\n");
}

int check(int index ) {
	node* temp = first;
	for (; temp; temp = temp->next)
		if (temp->value == index)
			return 1;
	return 0;

}
int main() {
	int n,i;
	int temp;
	int index;

	FILE* f = fopen("input.txt", "r");
	fscanf(f, "%d", &n);
	for (i = 0; i < n; i++) {
		fscanf(f, "%d",&temp);
			insert(temp);
	}
	print_node();

	while (1) {
		printf("Select menu and input the number(1: insert, 2 : delete) : \n");

		scanf("%d", &index);
	

		if (index == 1)
		{
			scanf("%d", &temp);
			
			if (check(temp) == 1) {
				printf("중복된 수입니다. 다른 수를 입력하시오 \n");
				continue;
			}

			insert(temp);
			print_node();
		}
		else if (index  == 2)
		{
			printf("%d\n", pop());
			print_node();
		}
	
	}

	
	
}
