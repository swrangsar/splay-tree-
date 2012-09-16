#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	void* data;
	int key;
	struct node* left;
	struct node* right;
	struct node* parent;
} node;

typedef struct tree {
	node* root;
	node* min;
	node* max;
} tree;

node* makeNode()
{
	node* new = malloc(sizeof(node));
	new->data = NULL;
	new->key = 0;
	new->left = new->right = new->parent = NULL;
	return new;
}

tree* makeTree()
{
	tree* new = malloc(sizeof(tree));
	new->root = new->min = new->max = NULL;
	return new;
}

void zig(node* self)
{
	self->parent->left = self->right;
	self->parent->parent = self;
	self->right = self->parent;
	self->parent = NULL;
}

void zag(node* self)
{
	self->parent->right = self->left;
	self->parent->parent = self;
	self->left = self->parent;
	self->parent = NULL;
}

void zigzig(node* self)
{
	node* ggp = self->parent->parent->parent;
	zig(self->parent);
	zig(self);
	self->parent = ggp;
}

void zagzag(node* self)
{
	node* ggp = self->parent->parent->parent;
	zag(self->parent);
	zag(self);
	self->parent = ggp;
}

void zigzag(node* self)
{
	node* ggp = self->parent->parent->parent;
	node* grandp = self->parent->parent;
	zag(self);
	self->parent = grandp;
	grandp->left = self;
	zig(self);
	self->parent = ggp;
}

void zagzig(node* self)
{
	node* ggp = self->parent->parent->parent;
	node* grandp = self->parent->parent;
	zig(self);
	self->parent = grandp;
	grandp->right = self;
	zag(self);
	self->parent = ggp;
}

node* findMin(node* self)
{
	if (self) {
		if (!self->left) {
			return self;
		} else {
			return findMin(self->left);
		}
	} else {
		return NULL;
	}
}

node* findMax(node* self)
{
	if (self) {
		if (!self->right) {
			return self;
		} else {
			return findMax(self->right);
		}
	} else {
		return NULL;
	}
}

node* findSplayPos(node* self, int key)
{
	if (key = self->key) {
		return self;
	} else if (key < self->key && self->left) {
		return findSplayPos(self->left, key);
	} else if (key > self->key && self->right) {
		return findSplayPos(self->right, key);
	} else {
		return self;
	}
}
	
node* findKeyPos(node* self, int key)
{
	if (key = self->key) {
		return self;
	} else if (key < self->key && self->left) {
		return findSplayPos(self->left, key);
	} else if (key > self->key && self->right) {
		return findSplayPos(self->right, key);
	} else {
		return NULL;
	}
}
	
node* access(tree* Tree, int key)
{
	if (!Tree || !Tree->root) {
		printf("The tree either empty or NULL!\n");
		exit(1);
	}
	splay(Tree, findSplayPos(Tree->root, key));
	return findKeyPos(Tree->root, key);
}
	
tree** split(tree* Tree, int key)
{
	if (!Tree || !Tree->root) {
		printf("The tree either empty or NULL!\n");
		exit(1);
	}

	tree** new = malloc(2*sizeof(tree*));	
	if (access(Tree, key)) {
		new[0]->root = Tree->root->left;
		new[1]->root = Tree->root->right;
		new[0]->root->parent = new[1]->root->parent = NULL;
		if (Tree->root) free(Tree->root);
		if (Tree) free(Tree);
		Tree = NULL;
		return new;
	} else {
		new[1]->root = Tree->root->right;
		new[0]->root = Tree->root;
		new[0]->root->right = new[1]->root->parent = NULL;
		Tree = NULL;
		return new;
	}
}

tree* join(tree* a, tree* b)
{
	splay(a, findMax(a));
	tree* new = NULL;
	new = a;
	b->root->parent = new;
	new->root->right = b->root;
	a = b = NULL;
	return new;
}

tree* insert(tree* Tree, int key)
{
	tree** subtrees = split(Tree, key);
	tree* new = makeTree();
	node* newRoot = makeNode();
	subtrees[0]->root->parent = subtrees[1]->root->parent = newRoot;
	newRoot->key = key; newRoot->left = subtrees[0]->root;
	newRoot->right = subtrees[1]->root;
	new->root = newRoot;
	return new;
}
	
