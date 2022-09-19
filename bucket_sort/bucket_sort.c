#include <stdlib.h>
#include <stdio.h>
#include <math.h>


#include "list.h"
//#include "list.c"



/*
compile with -g to collect debugging info needed for Valgrind:
gcc -g bucket_sort.c list.c

run with Valgrind:
valgrind --leak-check=full --show-leak-kinds=all ./a.out

run without Valgrind:
./a.out
*/

void print_array(int arr[], int N);
void bucket_sort(int arr[], int N);
//nodePT insertionSort(nodePT list);

/* // recommended helper functions:
// function to insert a new node in a sorted list.
nodePT insert_sorted(nodePT L, nodePT newP);
*/

//function to sort nodes in list by insertion sort
/*nodePT insertionSort(nodePT list)
{
    print_list_horiz(list);
    if(list == NULL)
    {
        return list;
    }
    if(list->next == NULL)
    {
        return list;
    }
    nodePT first = list;
    nodePT last = list;
    nodePT point = list->next;
    nodePT temp = list->next;
    nodePT toInsert;

    while(temp != NULL)
    {
        temp = temp->next;
        if(point->data <= first->data)
        {
            point->next = first;
            first = point;
        }
        if(point->data < last->data)
        {
            last->next = point;
            last = point;
        }
        else
        {
            toInsert = first;
            while(toInsert->data < last->data)
            {
                if(toInsert->data <= point->data && toInsert->next->data > point->data)
                {
                    point->next = toInsert->next;
                    toInsert->next = point;
                    break;
                }
                toInsert = toInsert->next;
            }
        }
        point = temp;
    }
    //last->next = NULL;
    return first;
}
*/

//  function to sort an array sing bucket sort
void bucket_sort(int arr[], int N)
{
    // number of buckets = size of array
    int NB = N;
    //find min and max from array
    int i, min, max = 0;
    min = arr[0];
    for(i=0;i<N;i++)
    {
        if(i<N)
        {
            if(arr[i] > max)
            {
                max = arr[i];
            }
        }
        if(arr[i] < min)
        {
            min = arr[i];
        }

    }
    printf("Bucketsort: min=%d, max=%d, N=%d buckets", min, max, N);
    //create a list from the array
    nodePT L = array_2_list(arr, N);
    print_list_horiz(L);
	//create an array of linked lists for buckets
    nodePT buckets[NB];
    for(i=0;i<NB;i++)
    {
        buckets[i] = NULL;
    }
	//print_list_horiz(*buckets[N]);
	//printf("\n N=%d\n", N);
	//sort original list into buckets
	int index, value;
	double idx;
	nodePT curr;
    nodePT temp;
	for (i = 0, curr = L; (curr != NULL); curr = curr->next)
    {
        value = curr->data;
        idx =(double)floor((((double)value-(double)min)*(double)NB/(1+(double)max-(double)min)));
        index = floor(idx);


        //printf("Index: %d", index);

        if(buckets[index] == NULL)
        {
            buckets[index] = new_node(value);
            //lastP = buckets[index];
        }
        else
        {
            temp = new_node(value);
            insert_node(buckets[index], buckets[index], temp);

        }
        //insert_node(buckets[index], buckets[index], temp);
        printf("arr[%d]=   %d, idx = %d\n", i, value, index);
        i++;
        //free(temp);
    }
    /*use insertion sort to order values in buckets
    for(i=0;i<N;i++)
    {
        buckets[i] = insertionSort(buckets[i]);
    }
    */
    // print each list in buckets
    for(i=0;i<N;i++)
    {
        index = i;
        printf("\n------ List at index %d:", index);
        print_list_horiz(buckets[index]);
    }

    //print the array in order of indexes
    printf("array:   ");
    for(i=0;i<N;i++)
    {
        int k;
        for (k = 0, curr = buckets[i]; (curr != NULL); curr = curr->next)
        {
            printf("%5d,    ", curr->data);
            k++;
        }
    }
    for(i=0;i<N;i++)
    {
        destroy_list(buckets[i]);
    }
    destroy_list(L);
    destroy_list(curr);
    //free(temp);
    return;
}


void print_array(int arr[], int N){
	int j;
	printf("\n array: ");
	for(j= 0; j<N; j++){
		printf("%5d,", arr[j]);
	}
	printf("\n");
}

//-------------------------------------------------------------


void run1(){
  // Fill in your code here. You should not write everything in this function.
  // Write some helper functions to separate the work.
  // get filename from user
	FILE *fp;
	char filename[100];
	int N, i = 0;
	printf("Enter the filename: ");
	scanf("%s", filename);
  //open file make and make sure its open if not print invalid file name
	fp = fopen(filename, "r");
	if(fp == NULL)
    {
        printf("File could not be opened");
        return;
    }
    fscanf(fp, "%d", &N);
    int fileArray[N];
    for(i=0;i<=N;i++)
    {
        fscanf(fp, "%d", &fileArray[i]);
    }
    fclose(fp);
    print_array(fileArray, N);
    printf("\n");
    //sort the array using bucket sort
    bucket_sort(fileArray, N);


}

int main()
{
	printf("This program will read a file name, load data for an array from there and print the sorted array.\n");
	printf("The array is sorted using bucket sort.\n");
	printf("This will be repeated as long as the user wants.\n");
	int option;
	do {
		run1();
		printf("\nDo you want to repeat? Enter 1 to repeat, or 0 to stop) ");
		scanf("%d",&option);
	} while (option == 1);

   return 0;
}
