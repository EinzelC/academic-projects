
#include <stdio.h>
#include <stdlib.h>

int** matMult(int **a, int **b, int size) {
	// (4) Implement your matrix multiplication here. 
	// You will need to create a new matrix to store the product.
	int **multMat = (int**)malloc(size*sizeof(int*));
	for (int i = 0; i < size; i++){
		*(multMat+i) = (int*)malloc(size*sizeof(int));
	}
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			for(int k = 0; k < size; k++){
				*(*(multMat+i)+j) += *(*(a+i)+k) * *(*(b+k)+j);
			}
		}
	}
	return multMat;
}

void printArray(int **arr, int n) {
	// (2) Implement your printArray function here
	printf("Printed out Matrix: \n");
	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("  %d  ", *(*(arr+i)+j));
		}
		printf("\n");
	}
}

void allocateAndFillArray(int **arr, int n){
	int input;
	for (int i = 0; i < n; i++){
		*(arr+i) = (int*)malloc(n*sizeof(int));
	}
	for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
			printf("Input for [%d][%d]: ", i, j);
			scanf("%d", &input);
            *(*(arr + i) + j) = input; 
        }
    }
}


int main() {
	int n;
	int **matA, **matB, **matC;
	printf("Input size of array: ");
	scanf("%d", &n);
	// (1) Define 2 (n x n) arrays (matrices). 
	matA = (int**)malloc(n*sizeof(int*));
	matB = (int**)malloc(n*sizeof(int*));

	// (3) Call printArray to print out the 2 arrays here.
	printf("Fill Matrix A:\n");
	allocateAndFillArray(matA, n);
	printf("Fill Matrix B:\n");
	allocateAndFillArray(matB, n);
	printArray(matA, n);
	printArray(matB, n);

	
	// (5) Call matMult to multiply the 2 arrays here.
	matC = matMult(matA, matB, n);
	
	// (6) Call printArray to print out resulting array here.
	printArray(matC, n);

	for (int i = 0; i < n; i++) {
		free(*(matA+i));
	}
	free(matA);
	for (int i = 0; i < n; i++) {
		free(*(matB+i));
	}
	free(matB);
	for (int i = 0; i < n; i++) {
		free(*(matC+i));
	}
	free(matC);

    return 0;
}