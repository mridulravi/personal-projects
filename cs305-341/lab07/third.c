#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
#define KB 1024
#define MB 1024 * 1024
#define Stride 16
 
int main() {

 int sizes[] = {
1 * KB, 4 * KB, 8 * KB, 16 * KB, 32 * KB, 64 * KB, 128 * KB, 256 * KB,
512 * KB, 1 * MB, 1.5 * MB, 2 * MB, 2.5 * MB, 3 * MB, 3.5 * MB, 4 * MB
};

unsigned int steps = 512 * 1024 * 1024;
static int arr[4 * 1024 * 1024];
int lengthMod,dummy;
unsigned int i, j;
double timeTaken;
clock_t start;
 

for ( j = 0; j < 16 ; j++)
{

lengthMod = sizes[j] - 1;

//start = clock();
for (i = 0; i < steps; i++) {
     for (i=0; i < 4 * 1024 * 1024; i = i + Stride)
           arr[i] = 1; 
}
//timeTaken = (double)(clock() - start)/CLOCKS_PER_SEC;
//printf("%d, %.8f \n", (lengthMod+1)/ 1024, timeTaken);
}


for ( j = 0; j < 16 ; j++)
{

lengthMod = sizes[j] - 1;

start = clock();
for (i = 0; i < steps; i++) {
     for (i=0; i < 4 * 1024 * 1024; i = i + Stride)
           dummy = arr[i]; 
}
timeTaken = (double)(clock() - start)/CLOCKS_PER_SEC;
printf("%d, %.8f \n", (lengthMod+1)/ 1024, timeTaken);
}
return 0;
}
