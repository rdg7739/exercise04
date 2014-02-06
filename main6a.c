/* File: main6a.c

   Test out circular buffer for foreign
   exchange quotes.

*/

#include <stdio.h>
#include <stdlib.h>
#include "circular.h"

int main() { 

   cbuf *cb1 ;
   cb1 = cbuf_init() ;
   cbuf_update(cb1, 60, 1.291) ;
   cbuf_update(cb1, 63, 1.287) ;
   cbuf_update(cb1, 63, 1.231) ;
   cbuf_update(cb1, 69, 1.229) ;
   cbuf_update(cb1, 72, 1.247) ;

   cbuf_dump(cb1) ;

   cbuf_update(cb1, 361, 1.291) ;

   cbuf_dump(cb1) ;

   cbuf_update(cb1, 411, 1.291) ;
   cbuf_update(cb1, 412, 1.281) ;
   cbuf_update(cb1, 413, 1.292) ;
   cbuf_update(cb1, 414, 1.284) ;
   cbuf_update(cb1, 414, 1.290) ;

   cbuf_dump(cb1) ;

   cbuf_update(cb1, 511, 1.241) ;
   cbuf_update(cb1, 512, 1.251) ;
   cbuf_update(cb1, 513, 1.232) ;
   cbuf_update(cb1, 514, 1.202) ;
   cbuf_update(cb1, 517, 1.119) ;

   cbuf_dump(cb1) ;

   cbuf_update(cb1, 551, 1.080) ;
   cbuf_update(cb1, 552, 1.081) ;
   cbuf_update(cb1, 553, 1.079) ;
   cbuf_update(cb1, 554, 1.088) ;
   cbuf_update(cb1, 561, 1.072) ;
   cbuf_update(cb1, 562, 1.113) ;
   cbuf_update(cb1, 563, 1.091) ;
   cbuf_update(cb1, 564, 1.092) ;
   cbuf_update(cb1, 571, 1.089) ;
   cbuf_update(cb1, 572, 1.073) ;
   cbuf_update(cb1, 573, 1.061) ;
   cbuf_update(cb1, 574, 1.111) ;
   cbuf_update(cb1, 581, 1.119) ;
   cbuf_update(cb1, 582, 1.123) ;
   cbuf_update(cb1, 583, 1.151) ;
   cbuf_update(cb1, 584, 1.153) ;

   cbuf_dump(cb1) ;

   cbuf_update(cb1, 750, 1.200) ;
   cbuf_dump(cb1) ;

   cbuf_update(cb1, 818, 1.210) ;
   cbuf_dump(cb1) ;

   cbuf_update(cb1, 868, 1.230) ;
   cbuf_dump(cb1) ;

   cbuf_update(cb1, 878, 1.230) ;
   cbuf_dump(cb1) ;

   cbuf_update(cb1, 900, 1.240) ;
   cbuf_dump(cb1) ;

   cbuf_update(cb1, 2000, 1.240) ;
   cbuf_dump(cb1) ;


   return 0 ;
}
