#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_SIZE 1000000

int N;
int Heights[MAX_SIZE+10];
int MaxArea;

typedef struct _Stack
{
	int top;
	int index[MAX_SIZE];
} Stack;

Stack createStack ();
void push (Stack *stack, int idx);
int pop (Stack *stack);
int peek (Stack *stack);
void isMax (int area);
bool isEmpty (Stack *stack);

// Modify this main function
int main() {
	int i, area, topIndex = 0;
	Stack stack = createStack();
	int height = 0;
	int width = 0;
	MaxArea = 0;
	// Read the bar heights in the histogram
	scanf("%d", &N);
	for (i = 0; i < N; i ++) scanf("%d", &Heights[i]);
	
	for(i = 0; i < N; i++)
	{
		while(!isEmpty(&stack) && Heights[i] < Heights[peek(&stack)])
		{
			topIndex = pop(&stack);
			height = Heights[topIndex];
			if(!isEmpty(&stack)) width = i-peek(&stack) - 1;
			else width = i;
			area = height * width;
			isMax(area);
		}
		push(&stack, i);
	}
	
	while(!isEmpty(&stack))
	{
		topIndex = pop(&stack);
		height = Heights[topIndex];
		if(!isEmpty(&stack)) width = i-peek(&stack) - 1;
		else width = i;
		area = height * width;
		isMax(area);
	}
	
	printf("%d", MaxArea);
	return 0;
}

Stack createStack ()
{
	Stack newStack;
	newStack.top = -1;
	return newStack;
}

void push (Stack *stack, int idx)
{
	stack->top++;
	stack->index[stack->top] = idx;
}

int pop (Stack *stack)
{
	int idx = stack->index[stack->top];
	stack->top--;
	return idx;
}

int peek (Stack *stack)
{
	return stack->index[stack->top];
}

void isMax (int area)
{
	if(MaxArea < area) MaxArea = area;
}

bool isEmpty (Stack *stack)
{
	return stack->top == -1;
}
