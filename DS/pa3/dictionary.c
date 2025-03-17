#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// You can declare any global variable, structure, etc.

int N;

typedef struct _Node
{
	char item;
	int rep;
	int target;
	struct _Node *leftChild, *rightSibling;
}Node;

Node* createNode(char item);
Node* insert(char *item, Node *parent);
Node* deleteNode(char *item, Node *parent);
int find(char *item, Node *root);
void print(Node *parent, char* buffer, int depth);
void freeTree(Node* node);

// Modify this main function
int main() {
	char op[10];
	scanf("%d", &N);
	
	Node *root = createNode(0);
	char buffer[101];
	int depth = 0;
	
	while (N --) {
		scanf("%s", op);
		char item[101] = {0, };
		if (strcmp(op, "insert") == 0) {
			scanf("%s", item);
			if(find(item, root) == -1) insert(item, root);
		}
		else if (strcmp(op, "delete") == 0) {
			scanf("%s", item);
			deleteNode(item, root);
		}
		else if (strcmp(op, "print") == 0) {
			Node *temp = root->leftChild;
			print(temp, buffer, depth);
			printf("\n");
		}
		else if (strcmp(op, "find") == 0) {
			scanf("%s", item);
			int result = find(item, root);
			printf("%d\n", result);
		}
	}
	
	freeTree(root);
	return 0;
}

Node* createNode(char item)
{
	Node *newNode = (Node *)malloc(sizeof(Node));
	newNode->item = item;
	newNode->rep = 0;
	newNode->target = 0;
	newNode->leftChild = NULL;
	newNode->rightSibling = NULL;
	return newNode;
}

Node* insert(char *item, Node *parent)
{
	if(*item == '\0') return NULL;
	
	Node *current = parent->leftChild;
	Node *prev = NULL;
	Node *newNode = NULL;
	
	while(current != NULL && current->item < *item)
	{
		prev = current;
		current = current->rightSibling;
	}
	
	if(current == NULL || current->item != *item)
	{
		newNode = createNode(*item);
		newNode->rightSibling = current;
		
		if(prev == NULL)
		{
			parent->leftChild = newNode;
		}
		else
		{
			prev->rightSibling = newNode;
		}
		
		current = newNode;
	}
	
	if(current->item == *item) current->rep++;
	
	if(*(item + 1) == '\0')
	{
		current->target++;
	}
	
	insert(item + 1, current);
	return current;
}

Node* deleteNode(char *item, Node *parent)
{
	if(*item == '\0' || parent == NULL) return NULL;
	
	Node *current = parent->leftChild;
	Node *prev = NULL;
	
	while(current != NULL && current->item != *item)
	{
		prev = current;
		current = current->rightSibling;
	}
	
	if(current == NULL) return NULL;
	
	if(current->item == *item) current->rep--;
	
	if(*(item + 1) == '\0' && current->target > 0)
	{
		current->target--;
		current->rep--;
		
		if(current->target == 0 && current->leftChild == NULL)
		{
			if(prev == NULL)
			{
				parent->leftChild = current->rightSibling;
			}
			else
			{
				prev->rightSibling = current->rightSibling;
			}
			free(current);
			return NULL;
		}
	}
	
	deleteNode(item + 1, current);
	return parent;
}

int find(char *item, Node *root)
{
	Node *current = root->leftChild;
	int index = 0;
	
	while (current != NULL) {
		if(current->item == *item)
		{
			if(*(item + 1) == '\0' && current->target == 1)
			{
				return index;
			}
			if(current->target == 1) index++;
			current = current->leftChild;
			item++;
		}
		else
		{
			index += current->rep;
			current = current->rightSibling;
		}
	}
	return -1;
}

void print(Node *parent, char* buffer, int depth)
{
	if(parent == NULL) return;
	
	buffer[depth] = parent->item;
	depth++;
	
	if(parent->target > 0)
	{
		buffer[depth] = '\0';
		printf("%s ", buffer);
	}
	
	print(parent->leftChild, buffer, depth);
	
	depth--;
	
	print(parent->rightSibling, buffer, depth);
}

void freeTree(Node* node) {
	if (node == NULL) return;
	freeTree(node->leftChild);
	freeTree(node->rightSibling);
	free(node);
}
