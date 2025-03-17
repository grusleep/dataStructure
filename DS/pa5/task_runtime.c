#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE 100000

// you can modify any part of this code

typedef struct _Task {
	int id;
	int R, C, P;
} Task;

typedef struct _Heap {
	Task items[MAX_SIZE+1];
	int size;
} Heap;

void swap(Task *a, Task *b);
void insertNode(Heap *heap, Task task);
void deleteNode(Heap *heap);
void print(Heap *heap);

int N;
Task Tasks[MAX_SIZE+1];
Heap TaskBuffer; // use this heap structure

int main() {
	scanf("%d", &N);
	int runTime = 0;
	for (int i = 1; i <= N; i ++){
		Tasks[i].id = i;
		scanf("%d %d %d", &Tasks[i].R, &Tasks[i].C, &Tasks[i].P);
		runTime += Tasks[i].C;
	}
	
	if (runTime <= Tasks[N].R) runTime = Tasks[N].R + Tasks[N].C;
	// you must implement priority-based task management system here
	int time = 0; // the time when the last task is completed
	int i = 1;
	while (time <= runTime) {
		for (; i <= N; i++)
		{
			if (Tasks[i].R <= time && Tasks[i].R != -1)
			{
				insertNode(&TaskBuffer, Tasks[i]);
				Tasks[i].R = -1;
			}
			else
			{
				break;
			}
		}
		
		if (TaskBuffer.size > 0)
		{
			Task currentTask = TaskBuffer.items[1];
			print(&TaskBuffer);
			deleteNode(&TaskBuffer);
			time += currentTask.C;
		}
		else
		{
			time++;
		}
	}
	return 0;
}

void swap(Task *a, Task *b) {
	Task tmp = *a;
	*a = *b;
	*b = tmp;
}

void insertNode(Heap *heap, Task task) {
	// you must implement this function
	heap->size += 1;
	heap->items[heap->size] = task;
	int idx = heap->size;
	while(idx > 1 && heap->items[idx].P > heap->items[idx/2].P)
	{
		swap(&heap->items[idx], &heap->items[idx/2]);
		idx /= 2;
	}
}

void deleteNode(Heap *heap) {
	// you must implement this function
	swap(&heap->items[1], &heap->items[heap->size]);
	heap->size -= 1;
	int i = 1, child;
	while (i*2 <= heap->size)
	{
		if (i*2+1 > heap->size || heap->items[i*2].P > heap->items[i*2+1].P) child = i*2;
		else child = i*2+1;
		if (heap->items[i].P >= heap->items[child].P) break;
		swap(&heap->items[i], &heap->items[child]);
		i = child;
	}
}

void print(Heap *heap) {
	printf("%d\n", heap->items[1].id);
	// heap 디버깅 용도
	/*printf("heap: ");
	for (int i = 1; i <= heap->size; i ++) printf("%d ", heap->items[i]);
	printf("\n");*/
}
