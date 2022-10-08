/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>
#define COLUMNS 6
int tomt = COLUMNS;

void print_number (int n)
{
	if(tomt < 1) // när tomt plats är mindre än 1, 
	{
		printf("\n");// jump to next line
		tomt = COLUMNS;// och tomt plats = 6 igen
	}
	printf("%10d", n);// 10 gives spaces that can or can not be filled by numbers
	tomt --;// tomt plats minskar 
}
int is_prime(int n) {
    int a = 1;
    int i = 2;
    if (n == 2)// när n = 2, det är prime number---> a = 1 direct 
        a = 1;
    for ( i = 2; i < n; i++)// alla tal delar med ett tal som mindre än sig själv
        if (n % i == 0)// så om rest = 0 ,så det är delbar med i , det betyder att det inte är  prime number.
            a = 0;
    return a;
}

void print_primes(int n) {
	int prime ; //
	int p = 2 ; // prime number börjar från 2 
	while (p <= n) // alla prime numbr är <= n 
	{
		prime = is_prime(p);//prime är resultat av is_prime , 1--p är en prime number , 0--p är inte en prime number 
		if (prime)//om is_prime är true 
		{
			print_number(p);// print out number 
			p++;// testa nästa tal  
		}
		else
		    p++;// is-prime är false, så testa nästa tal 
	}
	printf("\n");
}
// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char* argv[]) {
    if (argc == 2)
        print_primes(atoi(argv[1]));
    else
        printf("Please state an integer number.\n");
    return 0;
}

//What does it mean when a function does not return a value? How do you state that in a
//program? How can then the function (or more precisely, the procedure) perform anything
//useful?
//-----Void functions are used just like value-returning functions except they do not return a value after the function executes.
//-----It can perform actions like' print', which do not need a return value. 

//How did you implement the side effect that is needed to make print_number behave
//correctly?
//--- we need a global variable to be able to be used each time we call it
//--- columns is a static valur , so we need a another variable which can be modified (tomt in this code )
//--- Cause COLUMN is a fixed variable, so the tomt will go back to the value of COLUMN.  


