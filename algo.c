//
// 결과적으로 실패한 프로그램이긴하지만 이쁜 프로그램을 짜기위한 변수 설정 방법 , 주석처리 참고용
//

#define _CRT_SECURE_NO_WARNINGS
#define SIZE 10 // the size of sub arrays n'
#define MAX_SIZE 60 // the size of N.
#define K (MAX_SIZE/SIZE) // for calculating unknown K.
#include <stdio.h>
#include <stdlib.h>
//----------------------------------------------------------------------------
//        O(nlogK)-Algorithm             
// Step 1) create new empty Heap     
// Step 2) Build Max-Heap with Array[1...(MAX_SZIE/SIZE)] // O(n')
// Step 3) Extrac and Insert using Heap with K number nodes// O(nlogk) 
//----------------------------------------------------------------------------
typedef int Element;
typedef struct HeapNode* Node;
typedef struct my_Max_Heap* Heap;
typedef struct my_Max_Heap{
	int Capacity; // limit the size of heap
	int Current_Size;
	Node Heap_Array;
}my_Max_Heap;
typedef struct HeapNode{
	int index;
	Element key;
}HeapNode;
void Initialize_Max_Heap(Heap H, int i);// initialize Heap
void Init_Merge_Heap(Heap H);
void Insert_New_Key(Node x, Heap H);// Insert new Key in Heap
void Max_Heapify(Heap H);
void Heap_Sort(Heap H);// Extrac Max_Value and re-build heap
HeapNode Extrac_Max(Heap H);
int isEmpty(Heap H);
int isFull(Heap H);

int main(int argc, char* argv[])
{
	int i, j, s;
	int Merged_list[MAX_SIZE];
	HeapNode HNode;
	Heap my_Heap = NULL;
	Heap Merge_Heap = NULL;

	my_Heap = (Heap)malloc(sizeof(my_Max_Heap)*K + 1);
	Merge_Heap = (Heap)malloc(sizeof(my_Max_Heap)*K + 1);

	for (i = 0; i < K; i++)
	{
		Initialize_Max_Heap(&my_Heap[i], i);
	}

	Init_Merge_Heap(Merge_Heap);
	printf("The number of Sroted list: %d", K);
	printf("\n");

	for (i = 0; i < K; i++)
	{
		for (j = 1; j <= SIZE; j++)
		{
			printf("index= %d element= %d ", my_Heap[i].Heap_Array[j].index, my_Heap[i].Heap_Array[j].key);
			printf("\n");
		}
		printf("\n");
	} printf("\n");
	//---------------------------------------------------------------------------------------
	//     After executing "HEAP SORT" for creating K-Sorted Lists
	//---------------------------------------------------------------------------------------
	printf("----------------------------------------------------------------------------\n");
	printf("   After executing 'HEAP SORT' for creating K-Sorted Lists\n");
	printf("----------------------------------------------------------------------------\n");
	for (i = 0; i < K; i++)
	{
		while (!isEmpty(&my_Heap[i]))
		{
			Heap_Sort(&my_Heap[i]);
		}
		my_Heap[i].Current_Size = my_Heap[i].Capacity;
	}
	for (i = 0; i < K; i++)
	{
		for (j = 1; j <= SIZE; j++)
		{
			printf("%d-th Array element= %d ", my_Heap[i].Heap_Array[j].index, my_Heap[i].Heap_Array[j].key);
			printf("\n");
		}
		printf("\n");
	} printf("\n"); 

	//----------------------------------------------------------------------------------------
	//       O(NlogK) Algorithm Using Max-Heap
	//----------------------------------------------------------------------------------------
	// Insery keys in Heap having k nodes
	// 1) run Insert_Key func to implement heap using the k number arrays
	// 2) extrac max and Insert a new key
	s = i = j = 0;  
	while (!isFull(Merge_Heap))
	{
		Insert_New_Key(&my_Heap[i].Heap_Array[my_Heap[i].Current_Size--], Merge_Heap);
		i++;
	}
	while (!isEmpty(Merge_Heap)) // times : O(n) 
	{
		HNode = Extrac_Max(Merge_Heap); // tiems: O(1) Extrac Maxium +O(logK) Max-Heapify

		Merged_list[s] = HNode.key;

		for (i = 0; HNode.index != i && i < K; i++)
		{
			//do nothing, only to increment i until hit the exact index
		}

		if (!isEmpty(&my_Heap[i]))
		{
			if (!isFull(Merge_Heap))
				Insert_New_Key(&my_Heap[i].Heap_Array[my_Heap[i].Current_Size], Merge_Heap); 
			//tiems: O(1) Insert key + O(logK) Max-Heapify
			my_Heap[i].Current_Size--;
		}
		s++;
	}	printf("\n");

	printf("----------------------------------------------------------------------------\n");
	printf("			Completely Merged List\n");
	printf("----------------------------------------------------------------------------\n");

	for (i = 0; i < MAX_SIZE; i++)
	{
		printf("%d ", Merged_list[i]);
	}	printf("\n");
	printf("the number of elements in Array= %d\n", i);
	

	//--------------------------------------------------------------------------------
	//     Eliminate all dynamic allocations.
	//--------------------------------------------------------------------------------
	// call Destroy_Heap routine

	return 0;

}
void Initialize_Max_Heap(Heap H, int X)
{
	int i;
	H->Capacity = SIZE;
	H->Current_Size = 0;
	H->Heap_Array = (Node)malloc(sizeof(HeapNode)*SIZE + 1);

	for (i = 1; i <= SIZE; i++)
	{
		H->Heap_Array[i].key = rand() % 100 + 1;
		H->Heap_Array[i].index = X;
		H->Current_Size++;
		Max_Heapify(H);
	}

}

void Init_Merge_Heap(Heap H)
{
	H->Capacity = K;
	H->Current_Size = 0;
	H->Heap_Array = (Node)malloc(sizeof(HeapNode)* K + 1);
}

void Max_Heapify(Heap H)
{
	int i, child;
	int temp;

	for (i = H->Current_Size / 2; i > 0; i--) // "Percolating-UP" Stage Starting from the bottom-level
	{
		child = 2 * i;
		if (H->Heap_Array[child].key > H->Heap_Array[i].key && child <= H->Current_Size)
		{
			temp = H->Heap_Array[i].key;
			H->Heap_Array[i].key = H->Heap_Array[child].key;
			H->Heap_Array[child].key = temp;
		}
		if (H->Heap_Array[child + 1].key > H->Heap_Array[i].key && child + 1 <= H->Current_Size)
		{
			temp = H->Heap_Array[i].key;
			H->Heap_Array[i].key = H->Heap_Array[child + 1].key;
			H->Heap_Array[child + 1].key = temp;
		}
	}
}

void Insert_New_Key(Node X, Heap H)
{
	int i;
	if (isFull(H))
	{
		printf("Your Heap is Full!");
	}

	if (isEmpty(H))
	{
		H->Heap_Array[1].key = X->key;
		H->Heap_Array[1].index = X->index;
		H->Current_Size++;
	}
	else
	{
		for (i = ++H->Current_Size; H->Heap_Array[i / 2].key < X->key && i > 1; i = i / 2)
		{
			if (i == 0)
			{
				break;
			}
			H->Heap_Array[i].key = H->Heap_Array[i / 2].key;
			H->Heap_Array[i].index = H->Heap_Array[i / 2].index;
		}

		H->Heap_Array[i].index = X->index;
		H->Heap_Array[i].key = X->key;

	}
}

void Heap_Sort(Heap H)
{
	Node Max_key = (Node)malloc(sizeof(HeapNode));
	int Last_pos;
	int child;
	int i;
	if (isEmpty(H))
	{
		printf("Your heap is empty!!");
	}
	else
	{
		Max_key->key = H->Heap_Array[1].key; // save the global Maximum Value.
		Max_key->index = H->Heap_Array[1].index;
		Last_pos = H->Current_Size; // save the element of last max.
		--H->Current_Size; // decrease the size of heap for heap sort.

		for (i = 1; i * 2 <= H->Current_Size; i = child)
		{
			child = 2 * i;
			if (H->Heap_Array[child].key < H->Heap_Array[child + 1].key && child != H->Current_Size)
			{
				++child;
			}
			if (H->Heap_Array[child].key > H->Heap_Array[Last_pos].key)
			{
				H->Heap_Array[i].key = H->Heap_Array[child].key;
				H->Heap_Array[i].index = H->Heap_Array[child].index;
			}
			else
			{
				break;
			}
		}
		H->Heap_Array[i].key = H->Heap_Array[Last_pos].key;
		H->Heap_Array[i].index = H->Heap_Array[Last_pos].index;
		H->Heap_Array[Last_pos].key = Max_key->key;
		H->Heap_Array[Last_pos].index = Max_key->index;
	}
}

HeapNode Extrac_Max(Heap H)
{
	HeapNode Max_Node;
	HeapNode temp_Node;
	int Last_pos;
	int child;
	int i;
	if (isEmpty(H))
	{
		printf("Your heap is empty!!");
	}
	else
	{

		Max_Node = H->Heap_Array[1];
		Max_Node.index = H->Heap_Array[1].index;
		Max_Node.key = H->Heap_Array[1].key; // save the imformaiton on ROOT
		Last_pos = H->Current_Size; // save the element of last max.
		--H->Current_Size;// decrease the size of heap for heap sort.

		for (i = 1; i * 2 <= H->Current_Size; i = child)
		{
			child = 2 * i;
			if (H->Heap_Array[child].key < H->Heap_Array[child + 1].key && child != H->Current_Size)
			{
				++child;
			}
			if (H->Heap_Array[child].key > H->Heap_Array[Last_pos].key)
			{
				H->Heap_Array[i].key = H->Heap_Array[child].key;
				H->Heap_Array[i].index = H->Heap_Array[child].index;
			}
			else
			{
				break;
			}
		}
		temp_Node = Max_Node;
		H->Heap_Array[i].key = H->Heap_Array[Last_pos].key;
		H->Heap_Array[i].index = H->Heap_Array[Last_pos].index;

	}
	return temp_Node;
}

int isEmpty(Heap H)
{
	return H->Current_Size == 0;
}
int isFull(Heap H)
{
	return H->Current_Size == H->Capacity;
}

