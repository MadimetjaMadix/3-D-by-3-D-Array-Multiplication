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
	This function returns the mapped position in the 1D array for the element
	located at the index in the 2D array.
*/
int getElementLocation2D(int index[2], int N)
{
	int row    = index[0];
	int column = index[1];

	return ((row*N)+column);
}

/*
	This function returns the value stored in the element at the specified index.
	index is a 1D array with to elements. It contains the desired row and the 
	desired column.
*/
int retrieveElement2D(int* matrix, int index[2], int N)
{
	return *(matrix+getElementLocation2D(index, N));
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

int* rank2TensorMult(int *matrixA, int *matrixB, int N, int number_of_elements)
{
	int* result = allocateMarix(number_of_elements);
	int total_multiplication_operations = number_of_elements*N;
	for(int m=0; m<total_multiplication_operations; m++)
	{
		int i = m/number_of_elements;
		int j = m%N;
		int k = (m/N)%N;
		
		int indexA[2] = {i, k}; 
		int indexB[2] = {k, j};
		
		int elementA = retrieveElement2D(matrixA, indexA, N);
		int elementB = retrieveElement2D(matrixB, indexB, N);
		
		int indexC[2] = {i, j};
		int* total = result+getElementLocation2D(indexC, N);
		*total+=(elementA*elementB);
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
	int N = 3;
	int dimension = 2;
	int number_of_elements = getNumberOfElements(N, dimension);

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
	int *resultAddition = rank2TensorAdd(matrixA, matrixB, number_of_elements);
	print2DMatrix(resultAddition, N);
	
	printf("\n===== Multiplication Result =====");
	int *resultMultiplication = rank2TensorMult(matrixA, matrixB, N, number_of_elements);
	print2DMatrix(resultMultiplication, N);
	
	free(matrixA);
	free(matrixB);
	free(resultAddition);
	free(resultMultiplication);
	return 0;
}
