#include "binary_trees.h"

size_t binary_tree_height(const binary_tree_t *tree);
heap_t *last_node_heap(const heap_t *tree, size_t level);
void heapify(heap_t *tree);

/**
 * heap_extract - extracts the root node from a Max Binary Heap
 *
 * @root: pointer to the heap root
 *
 * Return: value of extracted node
 *         0 if otherwise
 **/
int heap_extract(heap_t **root)
{
	int value;
	size_t height;
	heap_t *first, *last;

	if (!root || !*root)
		return (0);

	first = *root;
	value = first->n;

	if (!(first->left || first->right))
	{
		*root = NULL;
		free(first);
		return (value);
	}

	/* Swap data between last node and first node and deletes last node */
	height = binary_tree_height(*root);
	last = last_node_heap(*root, height);
	first->n = last->n;
	if (last->parent->left == last)
		last->parent->left = NULL;
	else
		last->parent->right = NULL;
	free(last);

	heapify(*root);

	return (value);
}

/**
 * heapify - rearranges the Heap Binary Tree.
 *
 * @tree: pointer to the root node of the Heap Binary Tree.
 **/
void heapify(heap_t *tree)
{
	int temp;

	if (!tree)
		return;

	temp = tree->n;

	if (tree->left && tree->n < tree->left->n &&
	    (!tree->right || tree->left->n > tree->right->n))
	{
		tree->n = tree->left->n;
		tree->left->n = temp;
		heapify(tree->left);
	}
	if (tree->right && tree->n < tree->right->n &&
	    tree->left->n < tree->right->n)
	{
		tree->n = tree->right->n;
		tree->right->n = temp;
		heapify(tree->right);
	}
}

/**
 * last_node_heap - Extracts the last node of the binary heap.
 *
 * @tree: The current node to operate..
 * @level: The current height level of the node.
 *
 * Return: The last node of the tree.
 */
heap_t *last_node_heap(const heap_t *tree, size_t level)
{
	heap_t *last = NULL;

	if (tree)
	{
		if (level == 0)
			return ((heap_t *)tree);
		last = last_node_heap(tree->right, level - 1) ?
			last_node_heap(tree->right, level - 1) :
			last_node_heap(tree->left, level - 1);
		return (last);
	}
	return (NULL);
}

/**
 * binary_tree_height - Measures the height of a binary tree.
 *
 * @tree: The root of the tree to calculate its height.
 *
 * Return: the tree's height, 0 if tree is NULL.
 */
size_t binary_tree_height(const binary_tree_t *tree)
{
	size_t height_left, height_right;

	if (!tree || !(tree->left || tree->right))
		return (0);

	height_left = binary_tree_height(tree->left);
	height_right = binary_tree_height(tree->right);

	return (1 + (height_left >= height_right ? height_left : height_right));
}
