#include <stdio.h>

char* text1 = "This is a string.";// a0
char* text2 = "Yet another thing.";//a0

int list1[20]; //a1  length of the list ( sizeof(int) = 4 , sizeof(word) = 4 , list1 .space 80) 
int list2[20]; //a1  length of the list ( sizeof(int) = 4 , sizeof(word) = 4 , list2 .space 80)
int count = 0 ;//a2  hur många char som använt

void copycodes(int* list , char* text, int* count)// 
{	
	while(*text != 0) // beq $t0,$0,done ----> *text = 0, while loop slut 
	                  // j  loop----> så länge *text = 0----> försätt köra denn loop 
	{
		*list = *text;// lb $t0, 0($a0)     place char in the list ,  
		list++; // addi	$a1,$a1,4 -----next adress sizeof(int) 
		text++; // addi	$a0,$a0,1 -----next adress sizeof(char)
		*count = *count + 1 ; // addi $t1,$t1,1    increments count 
	}
}
void work()
{	
	copycodes(list1,text1, &count); 
	copycodes(list2,text2, &count);
}
void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
//Explain how you get the pointer addresses to the two char arrays (text1 and text2) and
//the counter variable (count) in function work().
//-----text1 and text2 is global varaible, and we use *text1 ang *text2 to point these value and text1 and text2 to get addresses of them. 

//What does it mean to increment a pointer? What is the difference between incrementing the
//pointer that points to the ASCII text string, and incrementing the pointer that points to the
//integer array? In what way is the assembler code and the C code different?
//-----incremnet a pointer : char++ , go to the next index of the array (sizeof(char) = 1)
//                           int++ , go to the next index of the array (sizeof(int) = 4
//                           difference between incrementing them is that they need different different amount of space in the memory
//-----difference : In c we dont need to use PUSH and POP to reserve slots in the stack
//                  Codes are much more simplified in c than assembly

//What is the difference between incrementing a pointer and incrementing a variable that a
//pointer points to? Explain how your code is incrementing the count variable.
//-----we can look at pointers as array indexes , when pointer increasing, it will go to the next index( sizeof(n))
//-----when a variable is increment, it incremnet the value of the variable.
//

//Explain a statement in your code where you are dereferencing a pointer. What does this
//mean? Explain by comparing with the corresponding assembler code
//-----in copycodes this function, we dereference them by useing *list and *text to get value at their own addresses
//     in assembly , we use a la to load address from the label , it will store the memeory addesss into the register we chose. 
//     when we want to use its value, we use the lb/lw (same as dereferencing)

//Is your computer using big-endian or little-endian? How did you come to your conlusion?
//Is there any benefit of using either of the two alternatives?
//-----my computer use the big-endian, 
//-----endian experiment : 0x23, 0x00,0x00,0x00 in heximal = 35 in decimal----litte-endian




