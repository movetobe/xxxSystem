#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *p1, const void *p2)
{
	return (*(int *)p1 - *(int *)p2);
}

int search_matrix(int **matrix, int matrixSize, int *matrixColSize, int target)
{
	/* double binary search: 1. which row. 2. which one */
	int i, j;
	int left, right, middle;
	int row;

	if ((matrix == NULL) || (matrixSize == 0) || (matrixColSize == NULL)
		|| (matrixColSize[0] == NULL) || (matrix[0] == NULL)) {
		return 0;
	}

	/* which row */
	left = 0;
	right = matrixSize - 1;
	middle = (left + right) / 2;

	while ((left + 1) < right) {
		if (matrix[middle][0] == target) {
			return 1;
		} else if (matrix[middle][0] < target) {
			left = middle;
		} else {
			right = middle;
		}
		middle = (left + right) / 2;
	}

	if ((matrix[left][0] <= target) && (matrix[right][0] > target)) {
		row = left;
	} else if (matrix[right][0] <= target) {
		row = right;
	} else {
		return 0;
	}

	/* which one */
	if (bsearch(&target, matrix[row], matrixColSize[0], sizeof(int), compare)) {
		return 1;
	}
	return 0;
}

int main(void)
{
	int matrixSize;
	int *matrixColSize;
	int **matrix;
	int target;
	int i, j;

	scanf("%d", &matrixSize);
	matrix = calloc(1, sizeof(int *) * matrixSize);
	matrixColSize = calloc(1, sizeof(int) * matrixSize);

	scanf("%d", &matrixColSize[0]);
	for (i = 0; i < matrixSize; i++) {
		matrixColSize[i] = matrixColSize[0];
		matrix[i] = calloc(1, sizeof(int) * matrixColSize[i]);
		for (j = 0; j < matrixColSize[i]; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	scanf("%d", &target);
	printf("%d\n", search_matrix(matrix, matrixSize, matrixColSize, target));

	for (i = 0; i < matrixSize; i++) {
		free(matrix[i]);
	}
	free(matrix);
	return 0;
}
