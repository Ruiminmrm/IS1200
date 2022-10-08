/*
 prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>

int is_prime(int n)
{
	int a = 1;
	int i ; 
	if (n == 2)
		a = 1;
    else 
	    for (i = 2; i < n; i++)
		    if (n % i == 0)
		    	a = 0;
	return a;
}


int main(void){
  printf("%d\n", is_prime(2));  // 11 is a prime.      Should print 1.
  printf("%d\n", is_prime(383)); // 383 is a prime.     Should print 1.
  printf("%d\n", is_prime(987)); // 987 is not a prime. Should print 0.
}
