#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
typedef struct node* nodePointer;
typedef struct node {
	char color;
	int value;
	nodePointer left;
	nodePointer right;
	nodePointer parent;
}node;

void print_inorder(FILE *f, node* first)
{
	if (first == NULL)
		return;

	print_inorder(f,first->left);
	fprintf(f,"%d(%c) ", first->value, first->color);
	print_inorder(f,first->right);
}

void print_preorder(FILE* f, node* first)
{
	if (first == NULL)
		return;

	fprintf(f,"%d(%c) ", first->value, first->color);
	print_preorder(f,first->left);
	print_preorder(f,first->right);
}
//������ �ϴ� �� ó���� ���������� ����
int find_type(node* leaf)
{
	if (leaf->parent != NULL)
	{
		if (leaf->parent->parent != NULL)
		{
			node* pu = leaf->parent;
			node* gu = pu->parent;

			//  �÷� ü����

			//LLr �̸� 1�� ��ȯ.
			if (pu->left == leaf && (gu->right != NULL && gu->right->color == 'R' )&& gu->right != pu)
				return 1;
			//LRr �̸� 2�� ��ȯ
			if (pu->right == leaf && (gu->right != NULL && gu->right->color == 'R') && gu->right != pu)
				return 2;
			//RRr�̸�
			if (pu->right == leaf && (gu->left != NULL && gu->left->color == 'R') && gu->left != pu)
				return 3;
			//RLr�̸� 4�� ��ȯ
			if (pu->left == leaf && (gu->left != NULL  && gu->left->color == 'R') && gu->left != pu)
				return 4;

			//rotation 
			//LLb�̸� 5�� ��ȯ.
			if (pu->left == leaf && (gu->right == NULL || gu->right->color == 'B') && gu->left == pu)
				return 5;
			//RRb�̸� 6�� ��ȯ
			if (pu->right == leaf && (gu->left == NULL || gu->left->color == 'B') && gu->right == pu)
				return 6;
			//LRb�̸� 7�� ��ȯ
			if (pu->right == leaf && (gu->right == NULL ||gu->right->color == 'B') && gu->left == pu)
				return 7;
			//RLb �̸� 8�� ��ȯ.
			if (pu->left == leaf && (gu->left == NULL || gu->left->color == 'B') && gu->right == pu)
				return 8;
		}
	}
	//�� ���� �ö� �� ���������� 
	return 0;

}
//bstinsert �ϱ�.
//����Ʈ�� ���� �� ����.

node * bi_insert(node* first, int value)
{
	if (first->value > value)
	{
		if (first->left == NULL)
		{
			node* temp;
			temp = (node*)malloc(sizeof(node));
			temp->left = NULL;
			temp->right = NULL;
			temp->color = 'R';
			temp->parent = first;
			temp->value = value;
			first->left = temp;
			return temp;
		}
		bi_insert(first->left, value);
	}
	else if (first->value < value) {
		if (first->right == NULL)
		{
			node* temp;
			temp = (node*)malloc(sizeof(node));
			temp->left = NULL;
			temp->right = NULL;
			temp->color = 'R';
			temp->parent = first;
			temp->value = value;
			first->right = temp;
			return temp; 
		}
		bi_insert(first->right, value);
	}
}
void rb_insert(node** first, int value)
{
	node* temp = NULL;
	node* leaf = NULL;

	//ó���� null �̸� �ְ� first�� �������ش�.
	if (*first == NULL)
	{
		temp = (node*)malloc(sizeof(node));
		temp->left = NULL;
		temp->right = NULL;
		temp->parent = NULL;
		temp->color = 'B';
		temp->value = value;
		*first = temp;
		return;

	}
	else {
		
		leaf = bi_insert(*first,value);
		while (leaf->parent != NULL) {
			//inbalance �ϴٸ�,
			if (leaf->color == 'R' && leaf->parent->color == 'R')
			{
				//Ÿ�� �Ǵ��ϱ�
				printf("type : %d ", find_type(leaf));
				//leaf�� ����.
				if (find_type(leaf) == 0) {
					//leaf->color = 'B'; //�̰� ���� �ǹ��� ? 
					// 0�̸� balance �ϴٴ� ���� �ƴѰ� ?
					//
					//balance �ؼ� �׳� Ż��.
					break;
				}
				//r�� ���
				else if (find_type(leaf) == 1 || find_type(leaf) == 2)
				{
					node* pu = leaf->parent;
					node* gu = pu->parent;
					//���� �ٲٱ�.
					gu->right->color = 'B';
					pu->color = 'B';
					gu->color = 'R';
					leaf = leaf->parent->parent;
				}
				else if (find_type(leaf) == 3 || find_type(leaf) == 4)
				{
					node* pu = leaf->parent;
					node* gu = pu->parent;
					//���� �ٲٱ�.
					gu->left->color = 'B';
					pu->color = 'B';
					gu->color = 'R';
					leaf = leaf->parent->parent;
				}
				else {
					node* pu = leaf->parent;
					node* gu = pu->parent;
					// LLb
					if (find_type(leaf) == 5)
					{
						pu->color = 'B';
						gu->color = 'R';
						//gu->left = pu->right;
						//�ö󰡼� �ٽ� �ڽ��� ��������� �Ѵ�.
						//�θ� �ְ� �θ��� �����ʿ� ������.
						if (gu->parent != NULL && gu->parent->value < gu->value)
						{
							gu->parent->right = pu;
							pu->parent = gu->parent;
							gu->left = pu->right;
							if (gu->left != NULL)
								gu->left->parent = gu;
							pu->right = gu;
							//? �� ���� ?
							//pu->parent = NULL;

						}
						else if (gu->parent != NULL && gu->parent->value > gu->value)
						{
							gu->parent->left = pu;
							pu->parent = gu->parent;
							gu->left = pu->right;
							if (gu->left != NULL)
								gu->left->parent = gu;
							pu->right = gu;
							//�򰥸���.
						}
						else if (gu->parent == NULL)
						{
							gu->left = pu->right;
							if (gu->left != NULL)
								gu->left->parent = gu;
							pu->right = gu;
							gu->parent = pu;
							*first = pu;

						}
						break;
					}
					// RRb
					else if (find_type(leaf) == 6)
					{
						pu->color = 'B';
						gu->color = 'R';
						//gu->right = pu->left;
						//�ö󰡼� �ٽ� �ڽ��� ��������� �Ѵ�.
						//�θ� �ְ� �θ��� �����ʿ� ������.

						if (gu->parent != NULL && gu->parent->value < gu->value)
						{
							gu->parent->right = pu;
							pu->parent = gu->parent;
							gu->right = pu->left;
							if (gu->right != NULL)
								gu->right->parent = gu;
							gu->parent = pu;
							pu->left = gu;

						}
						else if (gu->parent != NULL && gu->parent->value > gu->value)
						{
							gu->parent->left = pu;
							pu->parent = gu->parent;
							gu->right = pu->left;
							if (gu->right != NULL)
								gu->right->parent = gu;
							gu->parent = pu;
							pu->left = gu;

						}
						else if (gu->parent == NULL)
						{
							//�ݴ�� ?
							gu->right = pu->left;
							if (gu->right != NULL)
								gu->right->parent = gu;

							pu->left = gu;
							gu->parent = pu;
							*first = pu;
							pu->parent = NULL;
						}
						break;
					}
					// LRb
					else if (find_type(leaf) == 7)
					{
						gu->color = 'R';
						leaf->color = 'B';
						if (gu->parent == NULL)
						{
							pu->right = leaf->left;
							gu->left = leaf->right;
							leaf->left = pu;
							leaf->right = gu;
							pu->parent = leaf;
							gu->parent = leaf;
							*first = leaf;
						}
						//�Ҿƹ����� �����Ҿƹ��� ���� ū ��� �Ҿƹ����� �����ʿ� �ִ� ���
						else if (gu->parent != NULL && gu->parent->value < gu->value)
						{
							pu->right = leaf->left;
							gu->left = leaf->right;
							leaf->left = pu;
							leaf->right = gu;
							gu->parent->right = leaf;
							leaf->parent = gu->parent;
							pu->parent = leaf;
							gu->parent = leaf;

						}
						else if (gu->parent != NULL && gu->parent->value > gu->value)
						{
							pu->right = leaf->left;
							gu->left = leaf->right;
							leaf->left = pu;
							leaf->right = gu;
							gu->parent->left = leaf;
							leaf->parent = gu->parent;
							pu->parent = leaf;
							gu->parent = leaf;
						}
						break;
					}
					// RLb
					else if (find_type(leaf) == 8)
					{
						gu->color = 'R';
						leaf->color = 'B';
						if (gu->parent == NULL)
						{
							pu->left = leaf->right;
							gu->right = leaf->left;
							
							leaf->left = gu;
							leaf->right = pu;

							pu->parent = leaf;
							gu->parent = leaf;
							
							*first = leaf;
						}
						//�Ҿƹ����� �����Ҿƹ��� ���� ū ��� �Ҿƹ����� �����ʿ� �ִ� ���
						else if (gu->parent != NULL && gu->parent->value < gu->value)
						{
							pu->left = leaf->right;
							gu->right = leaf->left;
							
							leaf->left = gu;
							leaf->right = pu;
							gu->parent->right = leaf;
							leaf->parent = gu->parent;
						}
						else if (gu->parent != NULL && gu->parent->value > gu->value)
						{
							pu->left = leaf->right;
							gu->right = leaf->left;
							leaf->right = pu;
							leaf->left = gu;
							gu->parent->left = leaf;
							leaf->parent = gu->parent;
						}
						break;
					}
				}
			}
			else
				break;

		}
	}
	//�ݺ����� ���� ���� 
	if ((*first)->color == 'R')
	{
		(*first)->color = 'B';
	}

}


int main(int argc, char* argv[]) {
	
	FILE* fi = fopen(argv[1], "r");
	FILE* fo = fopen(argv[2], "w+");
	int n,i,temp;
	fscanf(fi,"%d", &n);
	node* first = NULL;
	
	for (i = 0; i < n; i++)
	{
		fprintf(fo,"inserting : ");
		fscanf(fi, "%d", &temp);
		fprintf(fo, "%d ",temp);
		rb_insert(&first, temp);

		fprintf(fo,"\n");
		fprintf(fo, "inorder : ");
		print_inorder(fo,first);
		fprintf(fo, "\n");
		fprintf(fo, "preorder : ");
		print_preorder(fo,first);
		fprintf(fo, "\n");
	}

}