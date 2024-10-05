#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define CACHE_LINE_SIZE 64

int opt_random_access = 1;
long x = 1, y = 4, z = 7, w = 13;
long simplerand(void) {
	long t = x;
	t ^= t << 11;
	t ^= t >> 8;
	x = y;
	y = z;
	z = w;
	w ^= w >> 19;
	w ^= t;
	return w;
}

void do_mem_access(char* p, int size) 
{
    int i, j, count, outer, locality;
    int ws_base = 0;
    int max_base = ((size/CACHE_LINE_SIZE) - 512);
	for(outer = 0; outer < (1<<20); ++outer) {
      long r = simplerand() % max_base;
      // Pick a starting offset
      if(opt_random_access) {
         ws_base = r;
      } else {
         ws_base += 512;
         if( ws_base >= max_base ) {
            ws_base = 0;
         }
      }
      for(locality = 0; locality < 16; locality++) {
         volatile char *a;
         char c;
         for(i = 0; i < 512; i++) {
            // Working set of 512 cache lines, 32KB
            a = p + (ws_base + i) * CACHE_LINE_SIZE;
            if((i%8) == 0) {
               *a = 1;
            } else {
               c = *a;
            }
         }
      }
   }
}
int main ()
{

    int sizeOfArray = 125000;
    char accessArray[sizeOfArray];
   
    do_mem_access(accessArray, sizeOfArray);
}

