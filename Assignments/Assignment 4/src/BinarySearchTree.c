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
			tempNode->left = addNode;
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
	return NULL;
}

TreeDataPtr getRootData(Tree * theTree) {
	return NULL;
}

void printInOrder(Tree * theTree, PrintFunc printData) {

}

void printPreOrder(Tree * theTree, PrintFunc printData) {

}

void printPostOrder(Tree * theTree, PrintFunc printData) {

	postOrder(theTree->root, printData);

}

int isTreeEmpty(Tree* theTee) {
	return 0;
}

int isLeaf( TreeNode * treeNode) {
	return 0;
}

int hasTwoChildren( TreeNode *treeNode) {
	return 0;
}

int getHeight( TreeNode* treeNode ) {
	return 0;
}

void postOrder(TreeNode* printNode, PrintFunc printData) {

	if(printNode == NULL) {
    	return;
    }
 
     // first recur on left subtree
     postOrder(printNode->left, printData);
 
     // then recur on right subtree
     postOrder(printNode->right, printData);
 
     // now deal with the node
     printData(printNode->data);

}

#endif


