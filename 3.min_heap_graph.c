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
	//����
	node* new1 = (node*)malloc(sizeof(node));

	new1->value = value;
	new1->left = NULL;
	new1->right = NULL;
	new1->next = NULL;
	
	new1->parent = NULL;

	//�� ó���� �ƹ��͵� ������ ó�� ���� ���� first�� ��.
	if (first == NULL ) {
		first = new1;
		end = new1;
		return;
	}

	node* temp;
	temp = first;
	//�ڿ� �����ϰ� ���ο� ��带 ���� �ڷ� ����.
	end->next = new1;
	end = new1;

	// ó������ ���鼭 ó�� ������ �ڽ��� ���� ��忡 ������ �Ѵ� 
	// ������ ������ ���ʿ� // ������ �ְ� �������� ������ �����ʿ�
	// �Ѵ� ������ �������� �Ѿ��.
	// �θ� �����Ѵ�.
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

	//���� �ڿ� �ִ� ��带 // �� ������ �°� �ø���.

	temp = end;


	
	node* parent = temp->parent;
	node* child = temp;

	while (parent != NULL && child->value < parent->value) {
		//�ڽ��� ������ ����.
		int temp_value = parent->value;
		parent->value = child->value;
		child->value = temp_value;
		//�ڽ���ġ ����
		child = parent;
		parent = parent->parent;
	}
}
//���� ���� ���� ����, ���� �ڿ����� ���� �ְ� �������鼭 ���� �ڽ��� ��ġ�� ����.
int pop() {
	
	int ret = first->value;
	int last_value = end->value;

	// end�� ����� �θ���� ���� ����
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

	//end �� ����� next ��������
	node* temp = first;
	for (; temp; temp = temp->next)
	{
		if (temp->next == end)
		{
			temp->next = NULL;
			end = temp;
		}
	}
	
	//���� �ڿ� �ִ� ���� ������ �ִ´�.
	first->value = last_value;
	node* parent = first;
	node* child;

	//�ڽ��߿��� ���� ���� �̴´�.

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
				printf("�ߺ��� ���Դϴ�. �ٸ� ���� �Է��Ͻÿ� \n");
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
