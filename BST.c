#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//struct node;
//struct node *insert(struct node *, struct node *);

struct node{
	int value;
	int count;
	int height;
	struct node *parent;
	struct node *left;
	struct node *right;
};

int getHeight(struct node *nodeToGet)
{
	if(!nodeToGet)
		return 0;
//printf("Height(%p)=%d\n", nodeToGet, nodeToGet->height);
	return nodeToGet->height;
}

int getBalance(struct node *nodeToGet)
{
	if(!nodeToGet)
		return 0;
	int heightLeft = (nodeToGet->left? nodeToGet->left->height: 0);
	int heightRight = (nodeToGet->right? nodeToGet->right->height: 0);
//printf("Balance(%p)=%d\n", nodeToGet, heightRight - heightLeft);
	return (heightRight - heightLeft);
}

int max(int a, int b)
{
	return (a > b? a: b);
}

struct node *rotateLeft(struct node *root)
{
	struct node *newRoot = root->right;
	root->right = newRoot->left;
	root->right->parent = root;
	newRoot->left = root;
	newRoot->parent = root->parent;
	root->parent = newRoot;
	root->height = max(getHeight(newRoot->left->left), getHeight(newRoot->left->right)) + 1;
	newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
	return newRoot;
}

struct node *rotateRight(struct node *root)
{
	struct node *newRoot = root->left;
	root->left = newRoot->right;
	root->left->parent = root;
	newRoot->right = root;
	newRoot->parent = root->parent;
	root->parent = newRoot;
	root->height = max(getHeight(newRoot->right->left), getHeight(newRoot->right->right)) + 1;
	newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
	return newRoot;
}

int normalizeAVL(struct node *newNode)
{
	struct node *nodeToExamine = newNode;
	while(nodeToExamine)
	{
		if(getBalance(nodeToExamine) > 1)
		{
			if(getBalance(nodeToExamine->right)>0)
				rotateLeft(nodeToExamine);
			else
			{
				nodeToExamine->right = rotateRight(nodeToExamine->right);
				rotateLeft(nodeToExamine);
			}
		}
		if(getBalance(nodeToExamine) < -1)
		{
			if(getBalance(nodeToExamine->left)<0)
				rotateRight(nodeToExamine);
			else
			{
				nodeToExamine->left = rotateLeft(nodeToExamine->left);
				rotateRight(nodeToExamine);
			}
		}
		nodeToExamine = nodeToExamine->parent;
	}
	return 0;
}

struct node *insertBST(struct node *root, struct node *nodeToInsert)
{
	if(!root)
		return nodeToInsert;

	if(nodeToInsert->value < root->value)
	{
		root->left = insertBST(root->left, nodeToInsert);
		root->left->parent = root;
		root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	}
	else if(nodeToInsert->value > root->value)
	{
		root->right = insertBST(root->right, nodeToInsert);
		root->right->parent = root;
		root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	}
	else
		root->count++;

	return root;
}

int printBSTPreOrder(struct node *root)
{
	int i = 0;
	while(root->count > i++)
		printf("%d ", root->value);
	if(root->left)
		printBSTPreOrder(root->left);
	if(root->right)
		printBSTPreOrder(root->right);
	return 0;
}

int printBSTInOrder(struct node *root)
{
	int i = 0;
	if(root->left)
		printBSTInOrder(root->left);
	while(root->count > i++)
		printf("%d ", root->value);
	if(root->right)
		printBSTInOrder(root->right);
	return 0;
}

int printBSTPostOrder(struct node *root)
{
	int i = 0;
	if(root->left)
		printBSTPostOrder(root->left);
	if(root->right)
		printBSTPostOrder(root->right);
	while(root->count > i++)
		printf("%d ", root->value);
	return 0;
}

int main(int argc, char **argv)
{
	int i = 0;
	struct node *root = NULL;
	struct node *nodeToInsert = NULL;
	srand(time(0));
	int size = (argc > 1? strtol(*(argv + 1), NULL, 10): 10);
	printf("Original: \t");
	while(i++ < size)
	{
		nodeToInsert = calloc(1, sizeof(struct node));
		nodeToInsert->value = rand()%10;
		nodeToInsert->count = 1;
		nodeToInsert->height = 1;
		printf("%d ", nodeToInsert->value);
		root = insertBST(root, nodeToInsert);
		normalizeAVL(nodeToInsert);
	}
	printf("\nPreOrder:\t");
	printBSTPreOrder(root);
	printf("\nInOrder:\t");
	printBSTInOrder(root);
	printf("\nPostOrder:\t");
	printBSTPostOrder(root);
	printf("\n");

	return 0;
}

