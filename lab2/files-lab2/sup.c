#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6
int tomt = COLUMNS;
void print_number (int n)
{
	if(tomt < 1) // n?r tomt plats ?r mindre ?n 1, 
	{
		printf("\n");// jump to next line
		tomt = COLUMNS;// och tomt plats = 6 igen
	}
	printf("%10d", n);// 10 gives spaces that can or can not be filled by numbers
	tomt --;// tomt plats minskar 
}
void print_sieves(int n){
    int* numbers = malloc(n*sizeof(int));
	//best?ma att det ?r prime or not 
	for(int i = 2; i < n ; i++)// antar alla number ?r prime numbers
        numbers[i] = 1;
    for (int i = 2 ; i <sqrt(n) ; i++)// ta bort alla number som ?r delbar(divisible) med i 
    {
    	if(numbers[i])//om det ?r prime number 
    	{
    		for(int j = i+1; j <= n ; j++ )// testa alla tal som ?r mindre ?n sprt(i) enligt sieve of Eratosthenes
    		    if ( j % i == 0)// om det ?r divisible , which means the numbe is a prime number 
    		    	numbers[j] = 0;// ?ndra den till ett icke-prime tal
		}
	}
    int par = 0;
	int  i = 2 , j = 3, dis = 8;
	while (j < n)
	{
		if ((j - i) == dis )
		{
			par ++;
			printf("%d %d", i,j);
			printf("\n");
		}		
		i = j ;
		j++;
		while ( numbers[j] == 0 && j < n)
	    	j++;
	}
	printf("%d", par);
	free(numbers);
}
int main(int argc, char* argv[]) {
    if (argc == 2)
        print_sieves(atoi(argv[1]));
    else
        printf("Please state an integer number.\n");
    return 0;
}
