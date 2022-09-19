//Name: Cesar Cantu-Perez
//ID# 1001463763
//Course: CSE-3320-001
//Due:4/11/2022

// The MIT License (MIT)
// 
// Copyright (c) 2022 Trevor Bakker 
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "mavalloc.h"
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

enum TYPE
{
    FREE = 0,
    USED
};

struct Node {
  size_t size;
  enum TYPE type;
  void * arena;
  struct Node * next;
  struct Node * prev;
};

struct Node *alloc_list;
struct Node *previous_node;


void * arena;

enum ALGORITHM allocation_algorithm = FIRST_FIT;

int mavalloc_init( size_t size, enum ALGORITHM algorithm )
{
  arena = malloc( ALIGN4( size ) );
  
  allocation_algorithm = algorithm;

  alloc_list = ( struct Node * )malloc( sizeof( struct Node ));

  alloc_list -> arena = arena;
  alloc_list -> size  = ALIGN4(size);
  alloc_list -> type  = FREE;
  alloc_list -> next  = NULL;
  alloc_list -> prev  = NULL;

  previous_node  = alloc_list;

  return 0;
}

void mavalloc_destroy( )
{
  free( arena );
  struct Node *node = alloc_list;
  // iterate over the linked list and free the nodes
  while( node )
  {
	alloc_list = node -> next;
	free( node );
	node = alloc_list;
  }
	

  return;
}

void * mavalloc_alloc( size_t size )
{
  struct Node * node;
  if(alloc_list == NULL)
  {
    return NULL;
  }
  if( allocation_algorithm != NEXT_FIT )
  { 
    node = alloc_list;
  }
  else if ( allocation_algorithm == NEXT_FIT )
  {
    node = previous_node;
  }
  else
  {
    printf("ERROR: Unknown allocation algorithm!\n");
    exit(0);
  }

  size_t aligned_size = ALIGN4( size );

  if( allocation_algorithm == FIRST_FIT )
  {
    while( node )
    {
      if( node -> size >= aligned_size  && node -> type == FREE )
      {
        int leftover_size = 0;
  
        node -> type  = USED;
        leftover_size = node -> size - aligned_size;
        node -> size =  aligned_size;
  
        if( leftover_size > 0 )
        {
          struct Node * previous_next = node -> next;
          struct Node * leftover_node = ( struct Node * ) malloc ( sizeof( struct Node ));
  
          leftover_node -> arena = node -> arena + size;
          leftover_node -> type  = FREE;
          leftover_node -> size  = leftover_size;
          leftover_node -> next  = previous_next;
  
          node -> next = leftover_node;
        }
        previous_node = node;
        return ( void * ) node -> arena;
      }
      node = node -> next;
    }
  }

  // Implement Next Fit
  if( allocation_algorithm == NEXT_FIT )
  {
	while( node )
    {
      if( node -> size >= aligned_size  && node -> type == FREE )
      {
        int leftover_size = 0;
  
        node -> type  = USED;
        leftover_size = node -> size - aligned_size;
        node -> size =  aligned_size;
  
        if( leftover_size > 0 )
        {
          struct Node * previous_next = node -> next;
          struct Node * leftover_node = ( struct Node * ) malloc ( sizeof( struct Node ));
  
          leftover_node -> arena = node -> arena + size;
          leftover_node -> type  = FREE;
          leftover_node -> size  = leftover_size;
          leftover_node -> next  = previous_next;
  
          node -> next = leftover_node;
        }
        previous_node = node;
		return ( void * ) node -> arena;
      }
      node = node -> next;
    }
	node = alloc_list;
	while( node )
    {
      if( node -> size >= aligned_size  && node -> type == FREE )
      {
        int leftover_size = 0;
  
        node -> type  = USED;
        leftover_size = node -> size - aligned_size;
        node -> size =  aligned_size;
  
        if( leftover_size > 0 )
        {
          struct Node * previous_next = node -> next;
          struct Node * leftover_node = ( struct Node * ) malloc ( sizeof( struct Node ));
  
          leftover_node -> arena = node -> arena + size;
          leftover_node -> type  = FREE;
          leftover_node -> size  = leftover_size;
          leftover_node -> next  = previous_next;
  
          node -> next = leftover_node;
        }
        previous_node = node;
		return ( void * ) node -> arena;
      }
      node = node -> next;
    }
	
  }
 
  // Implement Worst Fit
  if( allocation_algorithm == WORST_FIT )
  {
	if(size > alloc_list -> size)
	{
	  return NULL;
	}
	struct Node *finder = alloc_list;
	int biggestBlock = 0;
	while( node )
	{
	  if( biggestBlock < node -> size && node ->type == FREE )
	  {
		biggestBlock = node -> size;
	  }
	  node = node -> next;
	}
	node = alloc_list;
	while( node )
    {
      if( node -> size == biggestBlock  && node -> type == FREE )
      {
        int leftover_size = 0;
  
        node -> type  = USED;
        leftover_size = node -> size - aligned_size;
        node -> size =  aligned_size;
  
        if( leftover_size > 0 )
        {
          struct Node * previous_next = node -> next;
          struct Node * leftover_node = ( struct Node * ) malloc ( sizeof( struct Node ));
  
          leftover_node -> arena = node -> arena + size;
          leftover_node -> type  = FREE;
          leftover_node -> size  = leftover_size;
          leftover_node -> next  = previous_next;
  
          node -> next = leftover_node;
        }
        previous_node = node;
		return ( void * ) node -> arena;
      }
      node = node -> next;
    }
  }
 
  // Implement Best Fit
  if( allocation_algorithm == BEST_FIT )
  {
	if(size > alloc_list -> size)
	{
	  return NULL;
	}
	int smallestBlock = 999999999;
	while( node )
	{
	  if(smallestBlock > node -> size && node -> type == FREE )
	  {
		smallestBlock = node -> size;
	  }
	  node = node -> next;
	}
	node = alloc_list;
	while( node )
    {
      if( node -> size == smallestBlock  && node -> type == FREE )
      {
        int leftover_size = 0;
  
        node -> type  = USED;
        leftover_size = node -> size - aligned_size;
        node -> size =  aligned_size;
  
        if( leftover_size > 0 )
        {
          struct Node * previous_next = node -> next;
          struct Node * leftover_node = ( struct Node * ) malloc ( sizeof( struct Node ));
  
          leftover_node -> arena = node -> arena + size;
          leftover_node -> type  = FREE;
          leftover_node -> size  = leftover_size;
          leftover_node -> next  = previous_next;
  
          node -> next = leftover_node;
        }
        previous_node = node;
		return ( void * ) node -> arena;
      }
      node = node -> next;
    }
  }
  return NULL;
}

void mavalloc_free( void * ptr )
{
  struct Node *node = alloc_list;
  struct Node *holder = alloc_list;
  while( node )
  {
	if(node -> type == USED)
	{
      if( node -> arena == ptr )
	  {
	    if( arena != NULL )
		{
	      node -> type = FREE;
		  
	      /*if( holder -> prev != NULL )
	      {
		    holder = holder -> prev;
			if( holder -> type == FREE )
	        {
		      holder -> size = node -> size + holder -> size;
		      if( node -> next == NULL )
			  {
				holder -> next = NULL;
				return;
			  }
			  else
			  {
				holder -> next = node -> next;
				return;
			  }
		      return;
	        }
	      }*/
	      holder = node;
		  holder = holder -> next;
	      if( holder != NULL )
	      {
		    if( holder -> type == FREE )
	        {
		      node -> size = holder -> size + node -> size;
		      if( holder -> next == NULL )
			  {
				node -> next = NULL;
				return;
			  }
			  else
			  {
				node -> next = holder -> next;
				return;
			  }
	        }
	      }
		  return;
		}
	    
	  }
    }	 
	node = node -> next;
	holder = holder -> next;
  }
  
  return;
}

int mavalloc_size( )
{
  int number_of_nodes = 0;
  struct Node * ptr = alloc_list;

  while( ptr )
  {
    number_of_nodes ++;
    ptr = ptr -> next; 
  }

  return number_of_nodes;
}
