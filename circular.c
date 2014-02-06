/*
 * circular.c
 *
 *  Created on: Apr 6, 2013
 *      Author: rdg77_000
 */

#include "circular.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#define BUFF_SIZE 10

/**
   initialize the cbuf*/

cbuf *cbuf_init(){
	cbuf *hoo;
	hoo = (cbuf *)malloc(sizeof(cbuf));
	hoo->quotes = (quote *)malloc(BUFF_SIZE * sizeof(quote));
	hoo->start = 0;
	hoo->end = 0;
	hoo->currentSize = 0;
	hoo->maxSize = BUFF_SIZE;
	return hoo;
}
/**
check that time is passed over 5 min or not.
it it did then set the time to -1 and increase the start point to next
it checks all the buffers from start to end
 */
void cbuf_checkTime(cbuf *cb_ptr, int time){
   int i = 0;
   int start = cb_ptr->start;
   
   while(i < cb_ptr->currentSize){
//	printf("start %d, %d\n\n", start, cb_ptr->start);
      if(start ==  cb_ptr->maxSize){
	 start -= cb_ptr->maxSize;
      }
      if((time - cb_ptr->quotes[start].time) > 300){
	 printf("%d ", time-cb_ptr->quotes[start].time);
	 cb_ptr->quotes[start].time = -1;
	 cb_ptr->start += 1;
	 if(cb_ptr->start == cb_ptr->maxSize){
	    cb_ptr->start -= cb_ptr->maxSize;
	 }
	 cb_ptr->currentSize -=1;
      }
      
      i++;
      start++;
//	printf("start %d, %d\n\n", start, cb_ptr->start);
   }
   

}

/**
   free all buffers*/
void cbuf_delete(cbuf *cb_ptr){
	free(cb_ptr->quotes);
	free(cb_ptr);
}

/**
update the buffers
shrink half the size of buffer if the buffer is using 1/4 of its max size
and enpend size twice if the buffer is full */
void cbuf_update(cbuf *cb_ptr, unsigned int time, double rate){
	int less = 0;
	cbuf_checkTime(cb_ptr, time); //check that time is passed or not

	if(cb_ptr->maxSize > BUFF_SIZE){
	   less = cb_ptr->maxSize / 4;
	}

	// printf("%d %d\n", less, cb_ptr->currentSize);
	quote *temp;
	int maxSize = cb_ptr->maxSize;
	temp = (quote *)malloc(maxSize/2 * sizeof(quote));
	
	if(cb_ptr->currentSize < less){//shrink the size if the condition is met
//	   cbuf_dump(cb_ptr);
	   int i = 0;
	   int start = cb_ptr->start;
		printf("Shrinking circular buffer: old max = %d, new max = %d\n", maxSize, maxSize/2);
		while(i<= cb_ptr->currentSize){ 		//copying cb_ptr to temp
			assert(i <= cb_ptr->currentSize);
			temp[i].time  = cb_ptr->quotes[start].time;
			temp[i].rate = cb_ptr->quotes[start].rate;
			i++;
			start++;
		}
		//	cbuf_delete(cb_ptr);
		cb_ptr->quotes = (quote *) malloc(maxSize /2 *sizeof(quote));
		cb_ptr->currentSize = i;//copy objects from temp and initialize cb_ptr
		cb_ptr->end = i;
		cb_ptr->start = 0;
		cb_ptr->maxSize = maxSize /2;
		cb_ptr->quotes = temp;
		//cbuf_delete(temp);
		//    cbuf_sort(cb_ptr);
	}

	if(cb_ptr->currentSize == cb_ptr->maxSize){ //expends the size of buffer if the condition is met
	   int i = 0;
	   int start = cb_ptr->start;
	   printf("%d\n", start);
	   printf("Expending circular buffer: old max = %d, new max = %d\n", maxSize, maxSize*2);
	   if(start > cb_ptr->end){
	      while (start <=cb_ptr->maxSize){
		 temp[i].time = cb_ptr->quotes[start].time;
		 temp[i].rate = cb_ptr->quotes[start].rate;
		 i++;
		 start++;
	      }
	      
	   }
	   int j = cb_ptr->start;
	   while(j <= cb_ptr->end){
	      temp[i].time  = cb_ptr->quotes[j].time;
	      temp[i].rate = cb_ptr->quotes[j].rate;
	      i++;
	      j++;
	   }
	   
//	   cbuf_delete(cb_ptr);
	   cb_ptr->quotes = (quote *) malloc(maxSize *2 *sizeof(quote));
	   cb_ptr->currentSize = i;//copy objects from temp and initialize cb_ptr
	   cb_ptr->end = i;
	   cb_ptr->start = 0;
	   cb_ptr->maxSize = maxSize *2;
	   cb_ptr->quotes = temp;
	   //cbuf_delete(temp);
	   //  cbuf_sort(cb_ptr);
	}
	cb_ptr->quotes[cb_ptr->end].time = time;
	cb_ptr->quotes[cb_ptr->end].rate = rate;
	cb_ptr-> end += 1;
	if(cb_ptr->end == cb_ptr->maxSize){//if the buffer reach end of the index, point it to index 0
	   cb_ptr->end -= cb_ptr->maxSize;
	}
	cb_ptr->currentSize += 1;
	

}

double cbuf_average(cbuf *cb_ptr){ //find out the average of input
	double avg = 0;
	double total = 0;
	int i =0;
	int start = cb_ptr->start;
	//	cbuf_dump();
	while(i < cb_ptr->currentSize){
		if(start == cb_ptr->maxSize){	//setting back to original start point
			start -= cb_ptr->maxSize;
		}
		total += cb_ptr->quotes[start].rate;
		i++;
		start++;
	}
	avg = total / cb_ptr->currentSize;
	return avg;
}
quote *cbuf_start(cbuf *cb_ptr){//return the quote at first position
	quote *pBuf;
	pBuf = (quote *)malloc (sizeof(quote));
	pBuf->time=  cb_ptr->quotes[cb_ptr->start].time;
	pBuf->rate=  cb_ptr->quotes[cb_ptr->start].rate;
	return pBuf;
}
quote *cbuf_end(cbuf *cb_ptr){ //return the quote at end position
	quote *pBuf;
	pBuf = (quote *)malloc (sizeof(quote));
	pBuf->time=  cb_ptr->quotes[cb_ptr->end-1].time;
	pBuf->rate=  cb_ptr->quotes[cb_ptr->end-1].rate;
	//	printf("Start: time = %d rate = %f\n", pBuf.time, pBuf.rate);
	return pBuf;
}
void cbuf_stats(cbuf *cb_ptr){ //print out the statistic of buffer
	printf("size: %3d max: %3d\n  start: %3d end: %3d\n\n", cb_ptr->currentSize, cb_ptr->maxSize, cb_ptr->start, cb_ptr->end-1);
}
void cbuf_dump(cbuf *cb_ptr){ //dump all the buffers in the array from start to end
	int i = cb_ptr->start;
	int j = 0;
	cbuf_stats(cb_ptr);
	printf("*** Circular Buffer Dump ***\n");
	while (j < cb_ptr->currentSize){
		if(i == cb_ptr->maxSize){
			i -= cb_ptr->maxSize;
		}
		if(cb_ptr->currentSize != 0){
			printf("%3.2d: time : %10.5d, rate: %10.5f\n", i, cb_ptr->quotes[i].time, cb_ptr->quotes[i].rate);
		}
		i++;
		j++;
	}
	printf("****************************\n\n\n\n");

}

