#include "HeapAPI.h"
#include "video.h"

/**
 * Internal functions to search for the max element between the data stored at index i
 * and the left child. This function will use compares data using the function pointer and return the index of the maximum item.
 */
size_t findMaxLeft(Heap *heap,size_t i); 

/**
 * Internal functions to search for the max element between the data stored at index current
 * and the right child. This function will use compares data using the function pointer and return the index of the maximum item.
 */
size_t findMaxRight(Heap *heap,size_t curr, size_t i); 

/**************************************************************************************************************************/

Heap *createHeap(size_t initialSize, void (*destroyDataFP)(void *data),int (*compareFP)(const void *first, const void *second)){
    Heap *heap;
    if(!(heap = malloc(sizeof(Heap)))){
        fprintf(stderr,"Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    if(!(heap->heapArray = malloc(sizeof(Node)*initialSize))){
        fprintf(stderr,"Out of memory.\n");
        exit(EXIT_FAILURE);
    }
    heap->type = MIN_HEAP;
    heap->currentSize = 0;
    heap->maxSize = initialSize;
    heap->destroyData = destroyDataFP;
    heap->compare = compareFP;
    return heap;
}

Node *createHeapNode(void *data){
    Node *node;
    node = malloc(sizeof(Node));
    node->data = data;
    return node;
}

void insertHeapNode(Heap *heap, void *data){
    
    heap->currentSize++;
    heap->heapArray[heap->currentSize - 1] = createHeapNode(data);
    
    if(heap->currentSize > 1) {
    	fixOrder(heap, heap->currentSize);
    }
    
}

void deleteRoot(Heap *heap) {
    Node *temp;
    if(heap->currentSize>0) {
        temp = heap->heapArray[0];
        (heap->currentSize)--;
        heap->heapArray[0] = heap->heapArray[heap->currentSize];
        heap->destroyData(temp);
        heapify(heap, 0) ;
    } else {
        fprintf(stderr,"Heap is empty.\n") ;
    }
}

void deleteHeap(Heap *heap){
    size_t i;
    i = heap->currentSize;
    while(i>0){
        deleteRoot(heap);
        i--;
    }
    //free(heap->heapArray);
    //free(heap);
}

void* getRoot(Heap *heap){
    return heap->heapArray[0]->data;
}

void heapify(Heap *heap, size_t i) {	// Heapify function to keep heap in order top down (only goes down, so I use fixOrder after each insertion)
    size_t small = i;				// index of "parent" or "smallest" node
    size_t left = small * 2 + 1;	// index of left child node
    size_t right = small * 2 + 2;	// index of right child node
    
    if(heap->currentSize > left && heap->compare(heap->heapArray[small]->data, heap->heapArray[left]->data) > 0) {
        small = left;	// if left child is less than parent, make new smallest node left child
    }
    if(heap->currentSize > right && heap->compare(heap->heapArray[small]->data, heap->heapArray[right]->data) > 0) {
        small = right;	// if right child is less than parent, make new smallest node right child
    }
    if(small != i) {	// if the "smallest" node is not the same as i ("parent node") then perform a simple swap
        Node* temp = heap->heapArray[i];	
        heap->heapArray[i] = heap->heapArray[small];
        heap->heapArray[small] = temp;
        heapify(heap, small);	// Recursive call to 
    }
}


size_t findMaxLeft(Heap *heap,size_t i){
    size_t  leftIdx = getLeftChildIndex( i );
    if( leftIdx < heap->currentSize && heap->compare(heap->heapArray[leftIdx]->data,heap->heapArray[i]->data) > 0){
        return leftIdx;
    }
    return i;
}

size_t findMaxRight(Heap *heap,size_t curr, size_t i){
    size_t rightIdx = getRightChildIndex( curr );
    if( rightIdx < heap->currentSize && heap->compare(heap->heapArray[rightIdx]->data,heap->heapArray[i]->data) > 0){
      return rightIdx;
    }
    return i;
}


size_t getLeftChildIndex(size_t index)
{
    return (index * 2) + 1;
}

size_t getRightChildIndex(size_t index)
{
    return (index * 2) + 2;
}

size_t getParentIndex(size_t index)
{	
	index++;
    return (index / 2) - 1;
}

size_t currentSize(Heap* heap)
{
    return heap->currentSize;
}

void* search(Heap* heap, void* data)
{       
    for(size_t i = 0; i < currentSize(heap);i++) 
    {
        if( heap->compare(data,heap->heapArray[i]->data) == 0)
            return heap->heapArray[i]->data;
    }
    return NULL;
}

void printHeap(Heap* heap, void (*printFunc)(void*) )	// simply iterates and prints heap array
{
    for(int j = 0; j < heap->currentSize; j++) {
        printFunc(heap->heapArray[j]->data);
    }
}

void fixOrder(Heap* heap, int currentSize) {	// currentSize - 1 (index of heap array)
												// currentsize / 2 - 1 (index of parent node. works for both left and right children nodes)
    if(currentSize <= 1) {
    	return;
    }
    // This recursive function fixes the order of nodes to make sure a min heap structure is present
    else if(heap->compare(heap->heapArray[currentSize / 2 - 1]->data, heap->heapArray[currentSize - 1]->data) > 0) {	// if parent node is greater than child (works for both even and odd indexed children)
        Node* temp = heap->heapArray[currentSize / 2 - 1];							// Simple swap of the parent and child nodes
        heap->heapArray[currentSize / 2 - 1] = heap->heapArray[currentSize - 1];
        heap->heapArray[currentSize - 1] = temp;
        fixOrder(heap, currentSize / 2);											// Recursive call at the position of the new parent node to keep checking up the heap
    }
}
