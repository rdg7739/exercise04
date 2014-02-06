/*
 * circular.h
 *
 *  Created on: Apr 6, 2013
 *      Author: rdg77_000
 */

#ifndef CIRCULAR_H_
#define CIRCULAR_H_

typedef struct quote{
   unsigned int time;
   double rate;
}quote;

typedef struct cbuf{
   quote *quotes;
   signed int start;
   signed int end;
   unsigned int currentSize;
   unsigned int maxSize;
}cbuf;

cbuf *cbuf_init();
void cbuf_delete(cbuf *cb_ptr);
void cbuf_sort(cbuf *cb_ptr);
void cbuf_update(cbuf *cb_ptr, unsigned int time, double rate);
double cbuf_average(cbuf *cb_ptr);
quote *cbuf_start(cbuf *cb_ptr);
quote *cbuf_end(cbuf *cb_ptr);
void cbuf_dump();
void cbuf_stats();

#endif /* CIRCULAR_H_ */
