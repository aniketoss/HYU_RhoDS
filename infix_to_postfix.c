#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#define MAX_CAPACITY 100
#define EMPTY_TOS -1

typedef char ElementType;
typedef struct StackNode* Stack; // Pointer to StackNode
typedef struct StackNode {

   ElementType* key;
   int TopOfStack;
   int maxElements;

}StackNode;// unit Data Sturcture;


         //
         // Functions for implementatin of STack
         //
         // 1. create -> 2. initilize -> 3. push or pop  4. isEmpty Is full

Stack create_Stack(int max);
void Make_Empty(Stack S);
void Push(ElementType X, Stack S);
void Pop(Stack S);
ElementType TopAndPop(Stack S); // Pop operation and return Top element
int isEmpty(Stack S);
int isFull(Stack S);

int Define_Priority(ElementType X);
void Compare_Priority(ElementType X, Stack S);

int main(int argc, char* argv[])
{
   FILE* input = fopen(argv[1], "r");
   ElementType* expr;
   ElementType ch;
   int i, index = 0;
   int priority, in_stack;
   ElementType output;

   Stack my_Stack = create_Stack(MAX_CAPACITY);
   expr = (ElementType*)malloc(sizeof(ElementType)*MAX_CAPACITY);

   while ((ch = fgetc(input)) != EOF)
   {
      expr[index] = ch;
      index = index + 1;
   }
   printf("Original infix Form:");
   for (i = 0; i <index; i++)
   {
      printf("%c", expr[i]);
   }   printf("\n");

   printf("Converted post fix form:");
   //
   // Challenge!
   // Body for infix-to-Posfix
   index = 0;

   while (expr[index] != '#')
   {
      priority = Define_Priority(expr[index]);

      if (priority == 0)
      {
         //print Operand;   
         printf("%c", expr[index]);
      }
      else if (priority == 1 || priority == 2)
      {
         //print and Compare
         //
         // in empty stack , push (operatior ) --(1)
         // not empty , how to insert operator --(2)

         if (isEmpty(my_Stack))// in case of empty
         {
            Push(expr[index], my_Stack);

         }
         else // not empty
         {
            Compare_Priority(expr[index], my_Stack);
         }
      }
      else if (priority == 3)
      {
         //print and Compare
         if (expr[index] == '(')
         {
           //printf("expr[index]=%c\n", expr[index]);
            Push(expr[index], my_Stack);

            index = index + 1;

           //printf("index=%d\n", index);
            while (expr[index] != ')')
            {
               priority = Define_Priority(expr[index]);
               in_stack = Define_Priority(my_Stack->key[my_Stack->TopOfStack]);

               if (priority == 0) //meet operand
               {
                  printf("%c", expr[index]);
               }
               else if (priority == 1 || priority == 2) // meet +,- or *,/,%
               {
                  if (in_stack >= priority)
                  {
                     if (my_Stack->key[my_Stack->TopOfStack] == '(')// Top Of Stack indicate '(' 
                     {
                        Push(expr[index], my_Stack); // top Of Stack  -> '(' , push (*) ,

                     }
                     else
                     {
                        output = TopAndPop(my_Stack);
                        printf("%c", output);
                        Push(expr[index], my_Stack);
                     }
                  }
                  else if (in_stack < priority)
                  {
                     Push(expr[index], my_Stack);
                  }
               }

               index = index + 1;
            }
         }// while until meet ')'
         if (expr[index] == ')')
         {
            while (my_Stack->key[my_Stack->TopOfStack] != '(')
            {
               output = TopAndPop(my_Stack);
               printf("%c", output);
            }   Pop(my_Stack);
         }
      }

      index = index + 1;
   }

 	while(!isEmpty(my_Stack))
	{
		output=TopAndPop(my_Stack);
		printf("%c", output);
	}	printf("%c", expr[index]);
		printf("\n");
   //
   //
   //

   free(expr);
   //dispose_Stack(my_Stack);
   free(my_Stack);
   fclose(input);
   return 0;

}

//
//   FUNCTION DEFINITION BELOW
//

Stack create_Stack(int max)
{
   Stack S;
   // void* malloc() 
   S = (Stack)malloc(sizeof(StackNode));
   // S <- void* .. tpyecaseting float a; int b;  b =(int)a
   if (S == NULL)
   {
      printf("OUT OF SPACE!\n");
   }

   S->maxElements = max;// setting for MAX_CAPACITY
   S->key = (ElementType*)malloc(sizeof(ElementType) * max);
   Make_Empty(S); // 

   return S;
}

void Make_Empty(Stack S)
{

   S->TopOfStack = EMPTY_TOS;
}

void Push(ElementType X, Stack S)
{
   if (isFull(S))
   {
      printf("STACK IS FULL!\n");
   }
   else
   {
      S->key[++S->TopOfStack] = X;
      //printf("TopOfStack:%d\n", S->TopOfStack);
      //printf("S->Key[Top]=%c\n", S->key[S->TopOfStack]);
   }
}
void Pop(Stack S)
{
      if(isEmpty(S))
      {
         printf("STACK IS EMPTY\n");
      }
      else
      {
   	S->TopOfStack--;
      }
}

ElementType TopAndPop(Stack S)
{
      if(isEmpty(S))
      {
         printf("STACK IS EMPTY\n");
      }
      else
      {
   	 return S->key[S->TopOfStack--];
      }

}

int isEmpty(Stack S)
{
   return S->TopOfStack == EMPTY_TOS; // cmp a == b return 1 or 0
}
int isFull(Stack S)
{
   return S->TopOfStack == (MAX_CAPACITY - 1);
}


int Define_Priority(ElementType X)
{

   switch (X)
   {
   case '(':
      return 3;
   case ')':
      return 3;
   case '*':
      return 2;
   case '/':
      return 2;
   case '%':
      return 2;
   case '+':
      return 1;
   case '-':
      return 1;
   default:
      return 0;
   }
}

void Compare_Priority(ElementType X, Stack S)
{
   int in_Stack, in_Coming;
   char result;
   //int 

   //
   //need something   
   //  in_Stack = Define_Priority(S->key[S->TopOfStack]);
   //  in_Coming = Define_Priority(X);
   // printf("in_Stack_prio=%d\n", in_Stack);
   // printF("in_Coming_prio=%d\n", in_Coming);
   while (1)
   {
      in_Stack = Define_Priority(S->key[S->TopOfStack]);
      in_Coming = Define_Priority(X);
      if (in_Coming <= in_Stack)
      {
         //
         // Pop and return key;
         // 
         result = TopAndPop(S);
         printf("%c", result);
      }
      else
      {
         // push(X, in STack);
         Push(X, S);
         break;
      }
   }
}
