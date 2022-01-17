
// C program for generating a 
// random number in a given range. 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

int printRandoms(int,int,int,int);


int main() 
{ 
    int lower = 100, upper = 1000, count = 1, num = 1;
    int returnVal; 
  
    // Use current time as  
    // seed for random generator 
    srand(time(0)); 
  
    //printRandoms(lower, upper, count, num); 

    returnVal = printRandoms(lower, upper, count, num);

    printf("Returned?? %d\n", returnVal);
  
    return 0; 
} 



int printRandoms(int lower, int upper, int count, int num) 
{ 
    int i; 
    for (i = 0; i < count; i++) { 
        num = (rand() % 
           (upper - lower + 1)) + lower; 
        printf("%d\n ", num); 
    }

   return num; 
} 
