#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define ARRAY_SIZE 10

void NONRAND(int *out)
{
	int array[] = {75, -18, 216, 21, -6, 352, 39, -68, -318, 182};
	memcpy(out, array, ARRAY_SIZE * sizeof(int));
}

void RANDOM(int *out)
{
	int i;
	for (i = 0; i < ARRAY_SIZE; i++)
	{
		out[i] = rand() % (1999) -999;
	}
}

void printarr(const int *arr, const char *name)
{
	printf("Here are the numbers from %s:\n", name);
	float average = 0;
	float sum = 0;
	int smallest = INT_MAX;
	int largest = INT_MIN;
	int counter;
	for (counter = 0; counter < ARRAY_SIZE; counter++)
	{
		// Determine smallest
		if (arr[counter] < smallest)
			smallest = arr[counter];
		// Determine largest
		if (arr[counter] > largest)
			largest = arr[counter];
		
		sum += arr[counter];
		
		printf("%i\n", arr[counter]);
	}
	
	average = sum / (float)ARRAY_SIZE;
	
	printf("Smallest number: %i\n", smallest);
	printf("Largest number: %i\n", largest);
	printf("Average: %.2f\n", average);
}

int main(void) {
	int *nonrands = (int*)calloc(ARRAY_SIZE, sizeof(int));
	int *rands = (int*)calloc(ARRAY_SIZE, sizeof(int));
	srand(867530942069L);
	
	printf("Calling NONRAND...\n");
	NONRAND(nonrands);
	printarr(nonrands, "NONRAND");
	
	printf("\n");
	
	printf("Calling RANDOM...\n");
	RANDOM(rands);
	printarr(rands, "RANDOM");
	
	// Free the memory allocated
	free(nonrands);
	free(rands);
	
	return 0;
}