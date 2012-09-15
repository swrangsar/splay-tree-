#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	void* data;
	struct node* left;
	struct ndoe* right;
	struct node* parent;
} node;

typedef struct tree {
	node* root;
	node* min;
	node* max;
} tree;

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
	zig(self->parent);
	zig(self);
}

void zagzag(node* self)
{
	zag(self->parent);
	zag(self);
}

void zigzag(node* self)
{
	node* grandp = self->parent->parent;
	zag(self);
	self->parent = grandp;
	grandp->left = self;
	zig(self);
}

void zagzig(node* self)
{
	node* grandp = self->parent->parent;
	zig(self);
	self->parent = grandp;
	grandp->right = self;
	zag(self);
}

