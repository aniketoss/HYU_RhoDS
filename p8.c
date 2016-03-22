#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct AVLNode* AVLtree;
typedef struct AVLNode* Position;
typedef struct AVLNode{
	ElementType keyValue;
	AVLtree left;
	AVLtree right;
	int Height;
}AVLNode;
Position DoubleRotationWithLeft(Position P);
Position DoubleRotationWithRight(Position P);
Position SingleRotationWithLeft(Position P);
Position SingleRotationWithRight(Position P);
AVLtree Insert(ElementType X, AVLtree T);
void PrintInOrder(AVLtree T);
int Height(AVLtree T);
int Max(int a, int b);

int main(int argc, char** argv)
{

	FILE* input = fopen(argv[1], "r");
	int Number;
	AVLtree Avl = (AVLtree)malloc(sizeof(AVLNode));
	Avl = NULL;

	while (!feof(input))
	{
		fscanf(input, "%d", &Number);
		Avl=Insert(Number, Avl);
	}
	PrintInOrder(Avl);
	printf("\n");
	fclose(input);
	return 0;
}

AVLtree Insert(ElementType X, AVLtree T)
{
	if (T == NULL)
	{

		T = (AVLtree)malloc(sizeof(AVLNode));
		// Check if(T==NULL)
		if (T == NULL)
		{
			printf("OUT OF SPACE!!");
		}
		else
		{
			T->left = T->right = NULL;
			T->Height = 0;
			T->keyValue = X;
		}
	}
	else if (X <= T->keyValue)
	{
		T->left = Insert(X, T->left);
		if ((Height(T->left) - Height(T->right)) == 2)
		{
			if (X < T->left->keyValue)
			{
				T = SingleRotationWithLeft(T);
			}
			else
			{
				T = DoubleRotationWithLeft(T);
			}
		}

	}
	else if (X > T->keyValue)
	{
		T->right = Insert(X, T->right);
		if ((Height(T->right) - Height(T->left)) == 2)
		{
			if (X >= T->right->keyValue)
			{
				T = SingleRotationWithRight(T);
			}
			else
			{
				T = DoubleRotationWithRight(T);
			}
		}
	}

	T->Height = Max(Height(T->left), Height(T->right)) + 1;
	return T;
}
Position DoubleRotationWithLeft(Position P3)
{

	P3->left = SingleRotationWithRight(P3->left);
	return SingleRotationWithLeft(P3);
	//return P3;
}
Position DoubleRotationWithRight(Position P3)
{
	P3->right = SingleRotationWithLeft(P3->right);
	return SingleRotationWithRight(P3);
}
Position SingleRotationWithLeft(Position P2)
{
	Position P1;

	P1 = P2->left;
	P2->left = P1->right;
	P1->right = P2;

	P2->Height = Max(Height(P2->left), Height(P2->right)) + 1;
	P1->Height = Max(Height(P1->left), Height(P1->right)) + 1;

	return P1;
}
Position SingleRotationWithRight(Position P2)
{
	Position P1;
	P1 = P2->right;
	P2->right = P1->left;
	P1->left = P2;

	P2->Height = Max(Height(P2->left), Height(P2->right)) + 1;
	P1->Height = Max(Height(P1->left), Height(P1->right)) + 1;
	return P1;
}
int Height(Position P)
{
	if (P == NULL)
		return -1;

	else
		return P->Height;
}
int Max(int a, int b)
{
	return a>b ? a : b;
}
void PrintInOrder(AVLtree T)
{
	if (T != NULL)
	{
		PrintInOrder(T->left);
		printf("%3d", T->keyValue);
		PrintInOrder(T->right);
	}
}
