#include <stdio.h>
#include <stdlib.h>

int is_prime(int n){
    
    for (int i = 2; i <= (n/2); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

typedef struct prime{
    int pNumber;            // is a prime number
    struct prime* next;     // points to next prime number
}prime;

//gobal struct prime head, used to work with linked list
prime* head = NULL;

// returns the head of linked list with prime numbers  2 - n
prime* gen_primelist(int n){
    prime* temp = malloc(sizeof(struct prime));
   
        // loops through every potential prime number 2 - n
        for (int i = 2; i < n; i++){
        
            // first prime (2) gets assigned to head
            if (head == NULL) {
                temp -> pNumber = i;
                temp -> next = NULL;
                head = temp;
            }  
        
        // the other primes get added to the end of the list
        else if (is_prime(i)){
            
            prime* temp = malloc(sizeof(struct prime));
            prime* current = head;
            
            while (current -> next != NULL) {
                current = current -> next;
            }
            
            temp -> pNumber = i;
            temp -> next = NULL;
            current -> next = temp;
        }
    }
    return head;
}

// Columns wanted for print function
int COLUMNS = 6;

// prints a linked list
void print_primeList(const prime* curr) {
    int counter = 0;
    
    while (curr -> next != NULL) {
        
        printf("%10d", curr -> pNumber);
        curr = curr->next;
        counter++;
     
        if (counter % COLUMNS == 0) {
            
            printf("\n");
        }
    }
    
    if (curr -> next == NULL){
        printf("%10d", curr -> pNumber);
    }
    
}

// frees the space used a Linked List
void free_primeList(prime* curr){

    while (curr -> next != NULL) {
        prime* temp = curr;
        curr = curr->next;
        free(temp);
    }
}

int main(int argc, char *argv[]){
    
    if (argc == 2) {
        prime* p = gen_primelist(atoi(argv[1]));
    
        print_primeList(p);
        free_primeList(p);
    }
    else
        printf("Please state an interger number.\n");
    
    printf("\n");

    return 0;
}
