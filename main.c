#include <stdlib.h>
#include <stdio.h>
#include <time.h>


/*
	This function takes in the size of the matrix and its dimension; 
	either 2 for 2D or 3 for 3D.
	These values are used to calculate the total number of elements in the matrix.
*/
int getNumberOfElements(int N, int dimension)
{
	int number_of_elements = 1;
	for(int i = 0; i<dimension; i++)
		number_of_elements*= N;
	return number_of_elements;
}

/*
	Because we will be representing it as 1 Dimensional Array, we will allocate 
	memory for the matrix and return a pointer to access it.
*/
int* allocateMarix(int number_of_elements)
{	
	int *result = (int*)calloc(number_of_elements,sizeof(int));
	return result;
}

/*
	This function (fn) takes a pointer to a matrix and the number of elements.
	It then populates it with random numbers ranging from 0 to 20.
*/

void populateMatrix(int *matrix, int number_of_elements)
{
	for(int i=0; i<number_of_elements; ++i)
	{
		*matrix = rand()%21;
		matrix++;
	}
	return;
}

/*
	This function takes two pointers to 2D matrices and their size.
	It adds the matrices, element wise, and stores the results.
	The functon returns the result.
*/
int *rank2TensorAdd(int *matrixA, int *matrixB, int number_of_elements)
{
	
	int *result = allocateMarix(number_of_elements);
	int *temp   = result;
	if (temp != NULL)
	{ 
		for(int i=0; i<number_of_elements; ++i)
		{
			*temp = *matrixA + *matrixB;
			temp++;
			matrixA++;
			matrixB++;
		}
	}
	else	
	{
		printf("Memory allocation failed.");
	}
	return result;	
}


void print2DMatrix(int *matrix, int N)
{
	printf("\n");
	for(int i=0; i< N*N; ++i)
	{
		if( i%N == 0) printf("\n");
	
		printf("%d ", *matrix);
		++matrix;
	}
	printf("\n");
}

int main()
{

	int N = 5;
	int dimension = 2;
	int number_of_elements = getNumberOfElements( N, dimension);
	srand(time(0));
	
	printf("Matrix A");
	int *matrixA = allocateMarix(number_of_elements);
	populateMatrix(matrixA, number_of_elements);
	print2DMatrix(matrixA, N);
	
	printf("\nMatrix B");
	int *matrixB = allocateMarix(number_of_elements);
	populateMatrix(matrixB, number_of_elements);
	print2DMatrix(matrixB, N);
	
	printf("\n===== Addition Result =====");
	int *result = rank2TensorAdd(matrixA, matrixB, number_of_elements);
	
	print2DMatrix(result, N);
	
	free(matrixA);
	free(matrixB);
	free(result);
	
	return 0;
}
