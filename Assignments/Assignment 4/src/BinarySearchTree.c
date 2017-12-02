#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "BinarySearchTreeAPI.h"
#include "rule.h"

#ifndef TREE_API
#define TREE_API


TreeNode* createTreeNode(TreeDataPtr data) {
	
	TreeNode* createNode = malloc(sizeof(TreeNode));
	createNode->data = data;
	createNode->left = NULL;
	createNode->right = NULL;
	
	return createNode;
}

Tree * createBinTree(CompareFunc compare, DeleteFunc del) {
	
	Tree* newTree = NULL;
	newTree = malloc(sizeof(Tree));
	newTree->root = NULL;
	newTree->compareFunc = compare;
	newTree->deleteFunc = del;

	return newTree;
}

void destroyBinTree(Tree * toDestroy) {

}

void addToTree(Tree * theTree, TreeDataPtr data) {
	
	int val = 0;
	TreeNode* addNode = createTreeNode(data);
	TreeNode* searchNode = NULL;
	TreeNode* tempNode = NULL;

	if(theTree->root == NULL) {		// if the root is null, set it
		theTree->root = addNode;
	}
	else {
		searchNode = theTree->root;
		while(searchNode != NULL) {
			val = theTree->compareFunc(addNode->data, searchNode->data);
			if(val < 0) {
				tempNode = searchNode;
				searchNode = searchNode->left;
			}
			else if(val > 0) {
				tempNode = searchNode;
				searchNode = searchNode->right;
			}
			else if(val == 0) {
				printf("This Rule has already been added!\n");
				return;
			}
		}
		val = theTree->compareFunc(addNode->data, tempNode->data);
		if(val < 0) {
			tempNode->left = addNode;	// searchNode
		}
		else if(val > 0) {
			tempNode->right = addNode;
		}
		else {
			printf("Something went wrong!\n");
		}
	}
}

void removeFromTree(Tree * theTree, TreeDataPtr data) {
	if(findInTree(theTree, data) == NULL) {
		printf("The Rule could not be Found!\n");
	}
	else {
		theTree->root = removeNode(theTree, theTree->root, data);
	}
}

TreeDataPtr findInTree(Tree* theTree, TreeDataPtr data) {
	
	TreeNode* returnNode = NULL;

	returnNode = inTree(theTree, theTree->root, data);

	if(returnNode == NULL) {
		return NULL;
	}
	return returnNode->data;
}

TreeDataPtr getRootData(Tree * theTree) {
	return NULL;
}

void printInOrder(Tree * theTree, PrintFunc printData) {	// Print functions referenced from http://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
	if(theTree->root == NULL) {
		printf("The Tree is Empty!\n");
	}
	else {
		inOrder(theTree->root, printData);
	}
}

void printPreOrder(Tree * theTree, PrintFunc printData) {

	preOrder(theTree->root, printData);

}

void printPostOrder(Tree * theTree, PrintFunc printData) {

	postOrder(theTree->root, printData);

}

int isTreeEmpty(Tree* theTree) {
	
	if(theTree->root == NULL) {
		return 1;
	}

	return 0;
}

int isLeaf( TreeNode * treeNode) {
	
	if(treeNode->left == NULL && treeNode->right == NULL) {
		return 1;
	}
	
	return 0;
}

int hasTwoChildren( TreeNode *treeNode) {
	
	if(treeNode->left != NULL && treeNode->right != NULL) {
		return 1;
	}
	
	return 0;
}

int getHeight(TreeNode* treeNode) {		// Referenced from Prof Ian's Slides
	
	int left = 0;
	int right = 0;
	int maxHeight = 0;

	if(treeNode == NULL) {
		return 0;
	}
	else {
		left = getHeight(treeNode->left);
		right = getHeight(treeNode->right);
		if(left >= right) {
			maxHeight = left;
			maxHeight++;
		}
		else if(right >= left) {
			maxHeight = right;
			maxHeight++;
		}
		return maxHeight;
	}

	return 0;
}

void inOrder(TreeNode* printNode, PrintFunc printData) {

	if(printNode == NULL) {
    	return;
    }
 
    inOrder(printNode->left, printData);

    printData(printNode->data);
 
    inOrder(printNode->right, printData);

}

void preOrder(TreeNode* printNode, PrintFunc printData) {

	if(printNode == NULL) {
    	return;
    }
 	
    printData(printNode->data);

    preOrder(printNode->left, printData);
 
    preOrder(printNode->right, printData);

}

void postOrder(TreeNode* printNode, PrintFunc printData) {

	if(printNode == NULL) {
    	return;
    }
 
    postOrder(printNode->left, printData);
 
    postOrder(printNode->right, printData);
 
    printData(printNode->data);

}

TreeNode* inTree(Tree* theTree, TreeNode* searchNode, TreeDataPtr data) {
	if(searchNode == NULL) {
		return NULL;
	}
	else if(theTree->compareFunc(data, searchNode->data) == 0) {
		return searchNode;
	}
	else if(theTree->compareFunc(data, searchNode->data) < 0) {
		return inTree(theTree, searchNode->left, data);
	}
	else if(theTree->compareFunc(data, searchNode->data) > 0) {
		return inTree(theTree, searchNode->right, data);
	}
	return searchNode; // dummy return to silence warning
}

TreeNode* removeNode(Tree* theTree, TreeNode* searchNode, TreeDataPtr data) {

	if(searchNode == NULL) {
		return NULL;
	}
	if(theTree->compareFunc(data, searchNode->data) == 0) {
		if(isLeaf(searchNode) == 1) {			// delete case if node is a leaf
			if(theTree->root == searchNode) {
				theTree->root = NULL;
				printf("in here\n");
			}
			free(searchNode);
			searchNode = NULL;
			printf("Successfully Deleted the Node1\n");
		}
		else if(searchNode->right == NULL) {	// delete case if 1 child and on left
			TreeNode* nextNode = searchNode->left;
			free(searchNode);
			searchNode = NULL;
			printf("Successfully Deleted the Node2\n");
			return nextNode;
		}
		else if(searchNode->left == NULL) {	// delete case if 1 child and on right
			TreeNode* nextNode = searchNode->right;
			free(searchNode);
			searchNode = NULL;
			printf("Successfully Deleted the Node2\n");
			return nextNode;
		}
		else if(searchNode->left != NULL && searchNode->right != NULL) {	// delete case if node has 2 children
			TreeNode* maxNode = findMax(searchNode->left);
			searchNode->data = maxNode->data;
			searchNode->left = removeNode(theTree, searchNode->left, maxNode->data);
			printf("Successfully Deleted the Node3\n");
		}
		return searchNode;
	}
	else if(theTree->compareFunc(data, searchNode->data) < 0) {			// iterate left side of tree
		searchNode->left = removeNode(theTree, searchNode->left, data);
	}		
	else if(theTree->compareFunc(data, searchNode->data) > 0) {			// iterate right side of tree
		searchNode->right = removeNode(theTree, searchNode->right, data);
	}
	return searchNode;
}

TreeNode* findMax(TreeNode* searchNode) {	// Finds Max Node in a tree
	while(searchNode->right != NULL) {
		searchNode = searchNode->right;
	}
	return searchNode;
}

#endif


