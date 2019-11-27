#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(p, s) if (!((p) = malloc(s))) { fprintf(stderr, "메모리 충분치않음"); exit(EXIT_FAILURE); }

#include<stdio.h>
#include<stdlib.h>


int FALSE = 0;
int TRUE = 1;

typedef struct element {
	int key;
}element;
typedef struct treeNode* treePointer;

typedef struct treeNode {
	element data;
	int bf;
	treePointer leftChild;
	treePointer rightChild;
}treeNode;

void leftRotation(treePointer* parent, int* unbalanced) {
	treePointer grandChild, child;
	child = (*parent)->leftChild;
	if (child->bf == 1) {
		/* LL rotation */
		(*parent)->leftChild = child->rightChild;
		child->rightChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
	}
	else {
		/*LR rotation */
		grandChild = child->rightChild;
		child->rightChild = grandChild->leftChild;
		grandChild->leftChild = child;
		(*parent)->leftChild = grandChild ->rightChild;
		grandChild->rightChild = *parent;
		//*parent = grandChild;
		//leftRotation(&parent, &unbalanced);

		switch (grandChild->bf)
		{
		case 1: (*parent)->bf = -1;
			child->bf = 0;  break;
		case 0: (*parent)->bf = child->bf = 0; break;
		case -1: (*parent)->bf = 0; child->bf = 1;
		}
		*parent = grandChild;
	}
	(*parent)->bf = 0; 
	*unbalanced = FALSE;
}


void rightRotation(treePointer* parent, int* unbalanced) {
	treePointer grandChild, child;
	child = (*parent)->rightChild;

	if (child->bf == -1) {
		/* RR rotation */
		(*parent)->rightChild = child->leftChild;
		child->leftChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
	}
	else {
		/*RL rotation */
		grandChild = child->leftChild;
		child->leftChild = grandChild->rightChild;
		grandChild->rightChild = child;
		(*parent)->rightChild = grandChild->leftChild;
		grandChild->leftChild = *parent;

		//rightRotation(&parent, &unbalanced);

		switch (grandChild->bf)
		{
		case 1:   (*parent)->bf = 0; child->bf = 1;  break;
		case 0:  (*parent)->bf = child->bf = 0; break;
		case -1: (*parent)->bf = -1; child->bf = 0;
		}
		*parent = grandChild;
	}
	(*parent)->bf = 0;
	*unbalanced = FALSE;
}
void avlInsert(treePointer * parent, element x, int* unbalanced) {
	
	if (!*parent) 
	{ /*insert element into null tree */ 
		*unbalanced = TRUE; 
		MALLOC(*parent, sizeof(treeNode)); 
		(*parent)->leftChild = (*parent)->rightChild = NULL; 
		(*parent)->bf = 0; 
		(*parent)->data = x; 
	}
	else if (x.key < (*parent)->data.key) 
	{ 
	avlInsert(&(*parent)->leftChild, x, unbalanced); 
	if (*unbalanced) 
	/* left branch has grown higher */ 
		switch ((*parent)->bf) { 
			case -1: (*parent)->bf = 0; *unbalanced = FALSE; break; 
			case 0: (*parent)->bf = 1; break; 
			case 1: leftRotation(parent, unbalanced); 
		} 
	}
																																												 
	else if (x.key > (*parent)->data.key) 
	{ 
		avlInsert(&(*parent)->rightChild, x, unbalanced); 
		if (*unbalanced) /*right branch has grown higher */ 
			switch ((*parent)->bf) { 
				// 높이가 같아짐.
				case 1: (*parent)->bf = 0; *unbalanced = FALSE; break; 
				// 오른쪽으로 하나더 많음
				case 0: (*parent)->bf = -1; break; 
				// 오른쪽에 또 붙어서 rl rotation 필요
				case -1: rightRotation(parent, unbalanced); 
			}
	}																																																																																					  
	else { 
		*unbalanced = FALSE; 
		printf("The key is already in the tree"); 
	}
}


void preorder(FILE * f, treePointer tree)
{
	if (tree == NULL)
		return;
	fprintf(f,"%d(%d) ", tree->data.key, tree->bf);
	preorder(f,tree->leftChild);
	preorder(f,tree->rightChild);
}

void inorder(FILE *f,treePointer tree)
{
	if (tree == NULL)
		return;
	inorder(f,tree->leftChild);
	fprintf(f,"%d(%d) ", tree->data.key, tree->bf);
	inorder(f,tree->rightChild);
}

int main(int argc, char* argv[] )
{
	FILE* fr = fopen(argv[1],"r");
	FILE* fw = fopen(argv[2], "w+");


	int n,temp,i;
	treePointer tree = NULL;

	fscanf(fr,"%d\n", &n);
	for (i = 0; i < n; i++)
	{
		fscanf(fr,"%d ",&temp);
		element x;
		x.key = temp;
		int unbalance = TRUE;
		//입력.
		avlInsert(&tree, x, &unbalance);
		fprintf(fw, "AVL TREE  \n");
		fprintf(fw, "PRE ORDER :");
		preorder(fw,tree);
		fprintf(fw,"\n");
		fprintf(fw, "IN ORDER :");
		inorder(fw,tree);
		fprintf(fw,"\n");

	}




}
