#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

//struct node;
//struct node *insert(struct node *, struct node *);

struct node{
	int value;
	int count;
	struct node *parent;
	struct node *left;
	struct node *right;
};

struct node *insert(struct node *root, struct node *toBeInserted)
{
	if(!root)
		return toBeInserted;
	if(toBeInserted->value < root->value)
	{
		root->left = insert(root->left, toBeInserted);
		root->left->parent = root;
	}
	else if(toBeInserted->value > root->value)
	{
		root->right = insert(root->right, toBeInserted);
		root->right->parent = root;
	}
	else
		root->count++;
	return root;
}

int printBSTInOrder(struct node*root)
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

int main()
{
	int i = 0;
	struct node *root = NULL;
	struct node *toBeInserted = NULL;
	srand(time(0));
	printf("A: ");
	while(i++ < 10)
	{
		toBeInserted = calloc(1, sizeof(struct node));
		toBeInserted->value = rand()%10;
		toBeInserted->count = 1;
		printf("%d ", toBeInserted->value);
		root = insert(root, toBeInserted);
	}
	printf("\nB: ");
	printBSTInOrder(root);
	printf("\n");

	return 0;
}