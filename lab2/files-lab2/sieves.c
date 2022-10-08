#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
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
void print_sieves(int n)
{
	char numbers[n];
	//bestäma att det är prime or not 
	for(int i = 2; i < n ; i++)// antar alla number är prime numbers
        numbers[i] = 1;
    for(int i = 2 ; i <sqrt(n) ; i++)// ta bort alla number som är delbar(divisible) med i 
    {
    	if(numbers[i])//om det är prime number 
    	{
    		for(int j = i+1; j < n ; j++ )// testa alla tal som är mindre än sprt(i) enligt sieve of Eratosthenes
    		    if ( j % i == 0)// om det är divisible , which means the numbe is a prime number 
    		    	numbers[j] = 0;// ändra den till ett icke-prime tal
		}
	}
	//print prime numbers
	for ( int i = 2; i < n ; i++)
		if ( numbers[i] == 1)
			print_number(i);
	printf("\n");
	free(numbers);
}

int main(int argc, char* argv[])
{
    if (argc == 2)
        print_sieves(atoi(argv[1]));
    else
        printf("Please state an integer number.\n");
    return 0;
}
//How did you represent the marking of 'prime' and 'not a prime' in the memory array?
//-----use 1 for 'prime', use 0 for 'not a prime'


//Which are the main steps in the algorithm? How have you implemented these steps? 
//-----'bestämt att det är prime or not' part . Frist , asseum that all the numbers are prime numbers.
//-----Then, delete the numbers that is divisble by the number I choose before( number[i] in the code , i < sprt(n) )
//-----Print out the valid elements


//What is the largest prime number that you can print within 2 seconds of computation? What
//is the largest number you can print within 10 seconds? Is it the same for print_prime.c,
//sieves.c, and sieves-heap.c? Why or why not?
//-----sieves----2s---
//-----
//-----
