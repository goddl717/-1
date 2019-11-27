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
//삽입을 하는 데 처음엔 검은색으로 삽입
int find_type(node* leaf)
{
	if (leaf->parent != NULL)
	{
		if (leaf->parent->parent != NULL)
		{
			node* pu = leaf->parent;
			node* gu = pu->parent;

			//  컬러 체인지

			//LLr 이면 1을 반환.
			if (pu->left == leaf && (gu->right != NULL && gu->right->color == 'R' )&& gu->right != pu)
				return 1;
			//LRr 이면 2를 반환
			if (pu->right == leaf && (gu->right != NULL && gu->right->color == 'R') && gu->right != pu)
				return 2;
			//RRr이면
			if (pu->right == leaf && (gu->left != NULL && gu->left->color == 'R') && gu->left != pu)
				return 3;
			//RLr이면 4를 반환
			if (pu->left == leaf && (gu->left != NULL  && gu->left->color == 'R') && gu->left != pu)
				return 4;

			//rotation 
			//LLb이면 5를 반환.
			if (pu->left == leaf && (gu->right == NULL || gu->right->color == 'B') && gu->left == pu)
				return 5;
			//RRb이면 6을 반환
			if (pu->right == leaf && (gu->left == NULL || gu->left->color == 'B') && gu->right == pu)
				return 6;
			//LRb이면 7을 반환
			if (pu->right == leaf && (gu->right == NULL ||gu->right->color == 'B') && gu->left == pu)
				return 7;
			//RLb 이면 8을 반환.
			if (pu->left == leaf && (gu->left == NULL || gu->left->color == 'B') && gu->right == pu)
				return 8;
		}
	}
	//더 위로 올라갈 수 없을때에는 
	return 0;

}
//bstinsert 하기.
//이진트리 생성 및 삽입.

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

	//처음에 null 이면 넣고 first를 정의해준다.
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
			//inbalance 하다면,
			if (leaf->color == 'R' && leaf->parent->color == 'R')
			{
				//타입 판단하기
				printf("type : %d ", find_type(leaf));
				//leaf를 수정.
				if (find_type(leaf) == 0) {
					//leaf->color = 'B'; //이게 무슨 의미지 ? 
					// 0이면 balance 하다는 뜻이 아닌가 ?
					//
					//balance 해서 그냥 탈출.
					break;
				}
				//r일 경우
				else if (find_type(leaf) == 1 || find_type(leaf) == 2)
				{
					node* pu = leaf->parent;
					node* gu = pu->parent;
					//색깔 바꾸기.
					gu->right->color = 'B';
					pu->color = 'B';
					gu->color = 'R';
					leaf = leaf->parent->parent;
				}
				else if (find_type(leaf) == 3 || find_type(leaf) == 4)
				{
					node* pu = leaf->parent;
					node* gu = pu->parent;
					//색깔 바꾸기.
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
						//올라가서 다시 자식을 갱신해줘야 한다.
						//부모가 있고 부모의 오른쪽에 있을때.
						if (gu->parent != NULL && gu->parent->value < gu->value)
						{
							gu->parent->right = pu;
							pu->parent = gu->parent;
							gu->left = pu->right;
							if (gu->left != NULL)
								gu->left->parent = gu;
							pu->right = gu;
							//? 넌 머지 ?
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
							//헷갈린다.
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
						//올라가서 다시 자식을 갱신해줘야 한다.
						//부모가 있고 부모의 오른쪽에 있을때.

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
							//반대로 ?
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
						//할아버지가 고조할아버지 보다 큰 경우 할아버지가 오른쪽에 있는 경우
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
						//할아버지가 고조할아버지 보다 큰 경우 할아버지가 오른쪽에 있는 경우
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
	//반복문을 돌고 나서 
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