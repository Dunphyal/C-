// Date - 01/12/2016
// Student Name - Alex Dunphy
// Student Number - 12303659

#include <stdio.h>
#include <stdlib.h>

const int size = 6;
struct Tree_Node {
	char data;
	Tree_Node *left, *right; //*temp;

};

Tree_Node* newNode(char data) {
	Tree_Node* newnode = new Tree_Node;
	newnode->data = data;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;
}

// The tree_insert functions purpose is to insert a new value into the BST i.e. creating a new node.
// A double pointer is used so that the function can be used recursively making the code a lot more
// concise. The function first checks wether the tree is empty, if so the the data is inserted into the 
// root of the list. Otherwise the function checks if the new data is less than the root, if so the
// function is called again using the left leaf as the root. If the new data is greater than the root 
// the function is called and right leaf is used as the root. This is repeated until the current 'root' 
// is empty and the value is inserted.
void tree_insert(Tree_Node** root, char data) {


	if (*root == NULL) {
		*root = newNode(data);
	}

	else if (data <= (*root)->data) {
		tree_insert(&(*root)->left, data);
	}

	else if (data > (*root)->data) {
		tree_insert(&(*root)->right, data);
	}

	return;
}

// The tree_search function is a function used to find a particular value in the BST and return
// a pointer to the value, in the case that the desired char is not in the BST NULL is returned.
// The function works by first checking if the tree is empty otherwise a while loop is used to move
// either left or right in tree, at each iteration of the while loop the program checks wether the
// value of data in temp is equal to the target, if so the function returns the pointer temp. Otherwise
// the function completes the while loop and returns the value of NULL.


Tree_Node* tree_search(Tree_Node* root, char data) {

	Tree_Node* temp = root;
	if (temp == NULL) {
		return NULL;
	}


	else
		while (temp->left != NULL || temp->right != NULL) {

			if (temp->data == data) {
				printf(" Value Found ");
				return temp;
			}

			if (data < temp->data) {

				temp = temp->left;
			}

			if (data > temp->data) {

				temp = temp->right;

			}
		}

	printf(" Value not Found");
	return NULL;
}

// The tree-print function is a recursive function, its process is to recursively call itself so
// to move down the left hand side of the BST until it reaches the last occupied left leaf, the value
// is then printed. The function then checks if the current leaf has a right leaf which is occupied,
// if it does the funciton will recurse using the right leaf at the root and the same operation occurs.
// This is repeated for the entire list using the same method.

void tree_print_sorted(Tree_Node* root) {
	if (root != NULL) {
		if (root->left != NULL) {
			tree_print_sorted(root->left);
		}
		printf(" %c ", root->data);

		if (root->right != NULL) {
			tree_print_sorted(root->right);
		}
	}

}

// The tree_delete function is a recursive function, the function works by moving to the lowest level
// of the tree by calling itself recursively first for the left hand side and then secondly by the
// right. This is done as we need to delete them in an order whereby we dont delete nodes which
// we will need to access again. Each time the program reaches the bottom level of the BST the node is
// deleted.

void tree_delete(Tree_Node* root) {
	if (root != NULL) {
		if (root->left != NULL) {
			tree_delete(root->left);
		}
		if (root->right != NULL) {
			tree_delete(root->right);
		}
		delete(root);
		//printf("node deleted"); 
		root = NULL;
	}
}

void swap(char *array, int x, int y) { //swap function taken from previous assignment
	int temp = array[x];
	array[x] = array[y];
	array[y] = temp;
}

void selection_sort(char *array, int size) {   // selection sort taken from previous assignment

	for (int k = 0; k < size - 1; k++) {
		int current_pos = k;
		int min_val = k;
		for (int i = k; i < size; i++) {

			if (array[i] < array[min_val]) {
				min_val = i;
			}
		}
		swap(array, k, min_val);
	}
}

// The print function is a simple function which prints the values in an array by cycling
// through the array and printing the value at each position

void print(char*array, int size) {

	for (int i = 0; i < size; i++) {
		printf("%c ", array[i]);
	}
	printf("\n");
}

// The purpose of the midpoint function is to find the midpoint of the array
// as this will need to be used as the root in order to create a balanced tree, this is
// done by halfing the size. The midpoint value is then switched with the first value in the array,
// this is done so that when using the insert function the first value will be the one we desire 
// to be the root.
// We assign root the value of NULL so that the first value read in using the insert function will be 
// used as the root

Tree_Node*midpoint(char*array, int size) {

	int first = 0;
	int midpoint = size / 2;
	swap(array, midpoint, first);
	Tree_Node*root = NULL;
	return root;
}

// The array_to_BST function reads in each value of the array using the for loop
// through every cycle the insert function is called inserting the corresponding value 
// in the array into the BST. From the midpoint function the array should be ordered such that the 
// mid value is in the first position and will be used as the root of the BST. 

Tree_Node*array_to_BST(char*array, int size) {

	Tree_Node*root = midpoint(array, size);

	for (int k = 0; k < size; k++) {

		tree_insert(&root, array[k]);

	}
	printf(" root of balanced tree: %c \n", root->data);
	return root;
}

int main() {
	Tree_Node* root = NULL;
	tree_insert(&root, 'B'); // task 1
	tree_insert(&root, 'A');
	tree_insert(&root, 'C');
	tree_insert(&root, 'C');
	tree_insert(&root, 'D');

	printf("\n Result of Search for C: ");  // task 2
	Tree_Node*temp = tree_search(root, 'C'); // pointer stored in temp
											 //printf("\n test of search function for C: %c ", temp->data); // used to test if correct pointer was returned
	printf("\n Result of Search for G: ");
	Tree_Node*temp_2 = tree_search(root, 'G'); // pointer stored in temp_2

	printf("\n BST - Smallest to Greatest: ");
	tree_print_sorted(root); // task 3

	tree_delete(root); // task 4
	printf("\n list deleted \n");

	char test_array[size] = { 'X', 'Z', 'C', 'B', 'A', 'Y' };
	selection_sort(test_array, size);
	array_to_BST(test_array, size);
	tree_print_sorted(root); // task 5

	return 0;
}