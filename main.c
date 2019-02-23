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
	This function takes two pointers to matrices and their size.
	It adds the matrices, element wise.
*/
void addMatrice(int *arrayA, int *arrayB,int *result, int number_of_elements)
{
	for(int i=0; i<number_of_elements; ++i)
	{
		*result = *arrayA + *arrayB;
		result++;
		arrayA++;
		arrayB++;
	}
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
		addMatrice( matrixA, matrixB, temp, number_of_elements);

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
	if(result!=NULL)
	{
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
	}
	else	
	{
		printf("Memory allocation failed.");
	}
	return result;
}

/*
	This function takes two pointers to 3D matrices and their size.
	It adds the matrices, element wise, and stores the results.
	The functon returns the result.
*/
int *rank3TensorAdd(int *matrixA, int *matrixB, int number_of_elements)
{
	int *result = allocateMarix(number_of_elements);
	int *temp   = result;
	if (temp != NULL)
	{ 
		addMatrice( matrixA, matrixB, temp, number_of_elements);
	}
	else	
	{
		printf("Memory allocation failed.");
	}
	return result;	
}

int *rank3TensorMult(int *matrixA, int *matrixB, int N, int number_of_elements)
{
	int startPos = 0;
	int* result  = allocateMarix(number_of_elements);
	int* temp = result;

	if (temp != NULL)
	{ 
		int elements2D = N*N;
		for(int i=0;i<N;++i)
		{
			 int* result_2D = rank2TensorMult(matrixA+startPos, matrixB+startPos, 
			 								   N, elements2D);
			 										          
			// Copy elements:
			for(int i = 0; i<elements2D; i++)
			{
				*temp = *result_2D;
				temp++;
				result_2D++;
			}
			
			// Change starting position:
		 	startPos+= elements2D;
		 	
		 	result_2D = result_2D-elements2D;//reset position to beginning of array
		 	free(result_2D);// free memory
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
	
		printf("%4d ", *matrix);
		++matrix;
	}
	printf("\n");
}

void print3DMatrix(int *matrix, int N)
{
	printf("\n");
	for(int i=0; i< N*N*N; ++i)
	{
		if( i%(N*N) == 0)
		{
			printf("\n\nLayer");
			printf(" %d ", (i/(N*N)+1));
		}
		
		if( i%N == 0) printf("\n");
	
		printf("%4d ", *matrix);
		++matrix;
	}
	printf("\n");
}

void printRows(int rowA[], int rowB[], int N)
{
	for(int j = 0; j<N; j++) printf("%4d ", rowA[j]);
	printf("\t");
	for(int j = 0; j<N; j++) printf("%4d ", rowB[j]);
}

void printMatrices(int* matrixA, int* matrixB, int N, int dimensions, int number_of_elements)
{
	printf("\n");
	int rowA[N];
	int rowB[N];
	int column_counter = 0;
	int number_of_2D_elements = N*N;
	int number_tabs = (N/2)+2;
	
	printf("Matrix A");
	for(int i = 0; i<number_tabs; i++) printf("\t");
	printf("Matrix B\n");
	
	for(int i = 0; i< number_of_elements; i++)
	{ 
		if( i%number_of_2D_elements-1 == 0)
		{	
			// Print Layer number heading:
			for(int j = 0; j<2; j++)
			{
				if(j==0) printf("\n");
				printf("Layer");
				printf(" %d ", (i/(number_of_2D_elements)+1));
				if(j==0)
				{
					for(int k = 0; k<number_tabs; k++) printf("\t");
				}
			}
			printf("\n");
		}
		
		// Print Row:
		if(column_counter == N)
		{
			printRows(rowA, rowB, N);
			printf("\n");
			column_counter = 0;
		}
		
		rowA[column_counter] = *matrixA;		
		rowB[column_counter] = *matrixB;	
		++matrixA;
		++matrixB;
		++column_counter;
	}
	
	printRows(rowA, rowB, N); // Print last row
}

void printHeader()
{
	printf("       * ELEN4020A Data Intensive Computing: Laboratory 1 * \n");
    printf("       ****************************************************\n");
    printf("             +--------------------+----------------+ \n");
    printf("             |    Student Name    | Student Number | \n");
    printf("             +--------------------+----------------+ \n");
    printf("             | Lynch Mwaniki      |        1043475 | \n");
    printf("             | Madimetja Sethosa  |        1076467 | \n");
    printf("             | Teboho Matsheke    |        1157717 | \n");
    printf("             +--------------------+----------------+ \n");
}

void printMatrixSize(int N)
{
	printf("\n=========================================");
	printf("=========================================");
	printf("=====================================\n\n");
	printf("                                                         ");
	printf("N=%d", N);
	printf("                                                         \n");
	printf("\n=========================================");
	printf("=========================================");
	printf("=====================================\n");
} 

void run(int N)
{	
	int dimension = 2;
	int number_of_elements = getNumberOfElements(N, dimension);

	srand(time(0));
	
	int *matrixA = allocateMarix(number_of_elements);
	populateMatrix(matrixA, number_of_elements);
	
	int *matrixB = allocateMarix(number_of_elements);
	populateMatrix(matrixB, number_of_elements);
	
	// Print matrices:
	printMatrices(matrixA, matrixB, N, dimension, number_of_elements);
	
	printf("\n\n------------------------------------");
	printf(" 2D Addition Result ------------------------------------ ");
	int *resultAddition = rank2TensorAdd(matrixA, matrixB, number_of_elements);
	print2DMatrix(resultAddition, N);
	
	printf("\n\n------------------------------------ ");
	printf(" 2D Multiplication Result ------------------------------------ ");
	int *resultMultiplication = rank2TensorMult(matrixA, matrixB, N, number_of_elements);
	print2DMatrix(resultMultiplication, N);

	dimension = 3;
	number_of_elements = getNumberOfElements(N, dimension);

	printf("\n\n ==================================================  3D  ");
	printf(" ================================================== ");
	int *matrix3DA = allocateMarix(number_of_elements);
	populateMatrix(matrix3DA, number_of_elements);

	int *matrix3DB = allocateMarix(number_of_elements);
	populateMatrix(matrix3DB, number_of_elements);
	
	printMatrices(matrix3DA, matrix3DB, N, dimension, number_of_elements);

	printf("\n\n ------------------------------------ 3D Addition Result ");
	printf(" ------------------------------------ ");
	int *result_3D_Addition = rank3TensorAdd(matrix3DA, matrix3DB, number_of_elements);
	print3DMatrix(result_3D_Addition, N);

	printf("\n\n ------------------------------------ ");
	printf("3D Multiplication ------------------------------------ ");
	int* result_3D_Multiplication = rank3TensorMult(matrix3DA, matrix3DB, N, number_of_elements);
	printMatrices(matrix3DA, matrix3DB, N, dimension, number_of_elements);
	
	printf("\n\n ------------------------------------ ");
	printf(" 3D Multiplication Result ------------------------------------ ");
	print3DMatrix(result_3D_Multiplication, N);


	free(matrixA);
	free(matrixB);
	free(resultAddition);
	free(resultMultiplication);
	free(matrix3DA);
	free(matrix3DB);
	free(result_3D_Addition);
	free(result_3D_Multiplication);
}

int main()
{
	// Print Header:
	printHeader();
	
	int N = 10;
	printMatrixSize(N);
	run(N);
	
	N = 20;
	printMatrixSize(N);
	run(N);
	
	return 0;
}
