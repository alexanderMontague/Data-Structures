#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "BinarySearchTreeAPI.h"

#ifndef TREE_API
#define TREE_API


TreeNode* createTreeNode(TreeDataPtr data) {
	
	TreeNode* createNode = malloc(sizeof(TreeNode));
	createNode->data = data;
	createNode->left = NULL;
	createNode->right = NULL;
	
	return createNode;
}

Tree * createBinTree(CompareFunc compare, DeleteFunc del, PrintFunc print) {
	
	Tree* newTree = NULL;
	newTree = malloc(sizeof(Tree));
	newTree->root = NULL;
	newTree->compareFunc = compare;
	newTree->deleteFunc = del;
	newTree->printFunc = print;

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

}

TreeDataPtr findInTree( Tree* theTree, TreeDataPtr data ) {
	
	return inTree(theTree, theTree->root, data);

}

TreeDataPtr getRootData(Tree * theTree) {
	return NULL;
}

void printInOrder(Tree * theTree, PrintFunc printData) {

	inOrder(theTree->root, printData);

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

int getHeight(TreeNode* treeNode) {
	
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
			return maxHeight + 1;
		}
		else if(right >= left) {
			maxHeight = right;
			return maxHeight + 1;
		}
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

TreeDataPtr inTree(Tree* theTree, TreeNode* findNode, TreeDataPtr data) {

	if(theTree->compareFunc(findNode->data, data) == 0) {
		return data;
	}
	else if(findNode == NULL) {
		return NULL;
	}
	else {
		inTree(theTree, findNode->left, data);
		inTree(theTree, findNode->right, data);
	}
	return NULL;	// dummy return to silence warning
}

#endif


