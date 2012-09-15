#include <stdio.h>
#include <stdlib.h>


void splay(tree* Tree, tree* leftTree, tree* rightTree, int key)
{
	if (!Tree || !leftTree || !rightTree) {
		printf("The trees cannot be NULL.\n");
		exit(1);
	}
	if (!Tree->root || key = Tree->root-key) return;

	if (key < Tree->root->key) {
		if (!Tree->root->left) return;
		if (key == Tree->root->left->key) {
			// zig
			return;
		}
		if (key < Tree->root->left->key) {
			if (!Tree->root->left->left) {
				// zig
				return;
			}
			if (key == Tree->root->left->left->key) {
				// zig zig
				return;
			} else {
				if (Tree->root->left->left->left || Tree->root->left->left->right) {
					splay(Tree, leftTree, rightTree, key);
					return;
				}
				// zig zig
				return;
			}
		}
		if (key > Tree->root->left->key) {
			if (!Tree->root->left->right) {
				// zig
				return;
			}
			if (key == Tree->root->left->right->key) {
				// zig zag;
				return;
			} else {
				
				if (Tree->root->left->right->left || Tree->root->left->right->right) {
					splay(Tree, leftTree, rightTree, key);
					return;
				}
				// zig zag;
				return;
			}
		}
	}
	if (key > Tree->root->key) {
		if (!Tree->root->right) return;
		if (key == Tree->root->right->key) {
			// zag
			return;
		}
		if (key > Tree->root->right->key) {
			if (!Tree->root->right->right) {
				// zag
				return;
			}
			if (key == Tree->root->right->right->key) {
				// zag zag
				return;
			} else {
				if (Tree->root->right->right-right || Tree->root->right->right->left) {
					splay(Tree, leftTree, rightTree, key);
					return;
				}
				// zag zag
				return;
			}
		}
		if (key < Tree->root->right->key) {
			if (!Tree->root->right->left) {
				// zag
				return;
			}
			if (key == Tree->root->right->left->key) {
				// zag zig;
				return;
			} else {
				if (Tree->root->right->left->right || Tree->root->right->left->left) {
					splay(Tree, leftTree, rightTree, key);
					return;
				}
				// zag zig;
				return;
			}
		}
	}
}			
