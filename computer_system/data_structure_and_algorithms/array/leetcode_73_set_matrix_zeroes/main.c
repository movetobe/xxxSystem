#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void set_zeroes(int **matrix, int matrixSize, int *matrixColSize)
{
	int i, j;
	int first_row = 0, first_col = 0;

	/* record first column/row's status */
	for (i = 0 ; i < matrixSize; i++) {
		if (matrix[i][0] == 0) {
			first_col = 1;
		}
	}
	for (j = 0; j < matrixColSize[0]; j++) {
		if (matrix[0][j] == 0) {
			first_row = 1;
		}
	}
	/* each row/col's status save in its first element */
	for (i = 1; i < matrixSize; i++) {
		for (j = 1; j < matrixColSize[i]; j++) {
			if (matrix[i][j] == 0) {
				matrix[i][0] = 0;
				matrix[0][j] = 0;
			}
		}
	}
	/* set to zero according its first element */
	for (i = 1; i < matrixSize; i++) {
		if (matrix[i][0] == 0) {
			memset(matrix[i], 0, sizeof(int) * matrixColSize[i]);
		}
	}
	for (j = 1; j < matrixColSize[0]; j++) {
		if (matrix[0][j] == 0) {
			for (i = 0; i < matrixSize; i++) {
				matrix[i][j] = 0;
			}
		}
	}

	/* first row/col origin status */
	if (first_row) {
		memset(matrix[0], 0, sizeof(int) * matrixColSize[0]);
	}
	if (first_col) {
		for (i = 0; i < matrixSize; i++) {
			matrix[i][0] = 0;
		}
	}
	return;
}

int main(void)
{
	int matrixSize;
	int *matrixColSize;
	int **matrix;
	int i, j;

	scanf("%d", &matrixSize);

	matrix = calloc(1, sizeof(int *) * matrixSize);
	matrixColSize = calloc(1, sizeof(int) * matrixSize);
	scanf("%d", &matrixColSize[0]);
	for (i = 0; i < matrixSize; i++) {
		matrix[i] = calloc(1, sizeof(int) * matrixColSize[0]);
		matrixColSize[i] = matrixColSize[0];
		for (j = 0; j < matrixColSize[i]; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}

	set_zeroes(matrix, matrixSize, matrixColSize);
	for (i = 0; i < matrixSize; i++) {
		for (j = 0; j < matrixColSize[i]; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < matrixSize; i++) {
		free(matrix[i]);
	}
	free(matrix);
	free(matrixColSize);

	return 0;
}
