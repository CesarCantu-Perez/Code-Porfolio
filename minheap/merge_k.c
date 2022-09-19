#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "merge_k.h"  // includes list.h



//nodePT insert_sorted_list(nodePT L , nodePT inserted);
void sinkDown(nodePT heap[], int p, int k);
// inserts a node in a sorted list
/*nodePT insert_sorted_list(nodePT L, nodePT inserted)
{
    nodePT sorted = NULL;
    nodePT temp = NULL;
    int firstNode = 0;
    while(L != NULL)
       {
            if(inserted->data < L->data)
            {
                L = insert_node(L, temp, inserted);
                return L;
            }
            temp = L;
            L = L->next;
            printf("sorted loop\n");
       }
       insert_node_after(temp, inserted);

    return sorted;
}*/

/*  Sorts linked list L in pace using insertion sort.
*/
nodePT sort_list(nodePT L){

	int i,k, temp = 0;
	int count = 0;
	int sort[100];
	for(i=0;(L!=NULL);L=L->next)
    {
        sort[i] = L->data;
        i++;
        count++;
    }
    for(i=1;i<count;i++)
    {
        k = i;
        while((sort[k]<sort[k-1]) && (k != 0))
        {
            temp = sort[k];
            sort[k] = sort[k-1];
            sort[k-1] = temp;
            k--;
        }
    }
    nodePT sorted = array_2_list(sort, count);

    destroy_list(L);
    return sorted;

}

/* It is recommended to implement a sinkDown function in this file.
You can declare its header at the top of this file (after include)
write the implementation anywhere in this file.
(You cannot modify any of the list.h or merge_k.h files)
*/
void sinkDown(nodePT heap[], int p, int k)
{
    int left, right, imv = 0;
    nodePT temp = NULL;
    left = (2*p)+1;
    right = (2*p)+2;
    imv = p;
    if(heap[imv] != NULL)
    {
        if((left<k) && ((heap[left]->data) <= (heap[imv]->data)))
        {
            imv = left;
        }
        if((right<k) && ((heap[right]->data) <= (heap[imv]->data)))
        {
            imv = right;
        }
        while((imv != p) && (imv<k))
        {
            temp  = heap[imv];
            heap[imv] = heap[p];
            heap[p] = temp;
            p = imv;
            left = (2*p)+1;
            right = (2*p)+2;
            if((left<k) && ((heap[left]->data) <= (heap[imv]->data)))
            {
                imv = left;
            }
            if((right<k) && ((heap[right]->data) <= (heap[imv]->data)))
            {
                imv = right;
            }
            //answer for part 1 : time complexity = O(Nlog(k)), space = O(k)
        }
    }




}


/* Turns the given array (named heap) into an actual Min-Heap
   using the bottom-up method to build the heap.
   (See buidMaxHeap pseudocode in slides)
*/
void make_heap(int k, nodePT heap[]){
	// write your code in here
	int i, p, index = 0;
	index = floor((double)((k-1)/2));
	for(p = index;p>0;p--)
    {
        sinkDown(heap,p,k);
    }
    printf("Finished.\n The heap is: ");
    for(i=0; i<k; i++)
    {
      print_list_pointer(heap[i]);
    }
}



/*  heap is a Min-Heap of linked lists
	remove_min will remove AND RETURN the first node of the list at index 0.
	k (size of heap) will only change when that removal leaves that list empty.
*/
nodePT remove_min(int* k, nodePT heap[]){
    int val = 0;
    nodePT temp = heap[0];
    val = heap[0]->data;
    heap[0] = heap[0]->next;
    free(temp);
    nodePT min = new_node(val);
    if(heap[0] == NULL)
    {
      heap[0] = heap[*k];
      *k = *k-1;
    }
    sinkDown(heap,0,*k);
    return min;
}


/*
Input
   heap - is a Min-Heap array of SORTED single linked lists.
   k - size of array heap. The first item is at index 0
   debug - debug on/off:
			if debug is 1, student code should print debugging information as well: heap and sorted result list
			if debug is 0, it does not print debugging infomation.
			if debug is anything but 1, it does not print debugging infomation.
Returns: a sorted single linked list built by merging the k lists.

Algorithm
   Merging process:
	- use the heap to identify and remove the node, np, with the smallest data out
      of the k lists.
	- insert np at the end of result list.
*/
nodePT merge_k(int k, nodePT heap[], int debug){
    nodePT merged = NULL;
    nodePT np = NULL;
    nodePT prev = NULL;
    int i = 0;
    k = k-1;
    np = remove_min(&k, heap);
    merged = insert_node(merged, prev, np);
    prev = merged;
    while(heap[0] != NULL)
    {
        np = remove_min(&k, heap);
        merged = insert_node(merged, prev, np);
        if(debug == 1)
        {
            printf("\n--------------- Sorted result list:");
            print_list_pointer(merged);
            printf("\n---- HEAP (start) --------\n");
            for(i=0; i<k+1; i++)
            {
                print_list_pointer(heap[i]);
            }
            printf("\n---- HEAP (end) --------\n");
        }
        prev = prev->next;
    }
    return merged;
}
