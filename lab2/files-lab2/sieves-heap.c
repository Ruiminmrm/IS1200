#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
void print_sieves(int n){
	int* numbers = malloc(n*sizeof(int));// sizeof(int) = 4 , allocate n st integers (n*4 bytes)
	//bestäma att det är prime or not 
	for(int i = 2; i < n ; i++)// antar alla number är prime numbers
        numbers[i] = 1;
    for (int i = 2 ; i <sqrt(n) ; i++)// ta bort alla number som är delbar(divisible) med i 
    {
    	if(numbers[i])//om det är prime number 
    	{
    		for(int j = i+1; j <= n ; j++ )// testa alla tal som är mindre än sprt(i) enligt sieve of Eratosthenes
    		    if ( j % i == 0)// om det är divisible , which means the numbe is a prime number 
    		    	numbers[j] = 0;// ändra den till ett icke-prime tal
		}
	}
	//print prime numbers
	for ( int i = 2; i < n ; i++)
		if ( numbers[i] == 1)
			print_number(i);
	printf("\n");
	free(numbers);// free memory (like POP)
}
int main(int argc, char* argv[]) {
    if (argc == 2)
        print_sieves(atoi(argv[1]));
    else
        printf("Please state an integer number.\n");
    return 0;
}

