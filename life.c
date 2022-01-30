/**
 * @file life.c
 * @brief functions for Conway's Game of Life
 * @details Functions used in the Game of Life program. Contains the functions
 * to initialize matrixes, to free matrixes, and three functions containing
 * the main logic for cell reproduction with three different border patterns.
 * @author Josiah Cury
 * @date 4/29/2019
 * @todo Implement more error checking to make sure the initialization pattern
 * is within parameters.
 * @bug
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "life.h"

/**
* @remark Initialized a 2 dimensional array, or a matrix
* @param rows the number of rows in the matrix assigned space
* @param cols the number of columns in the matrix assigned space
* @return a pointer holding the memory address of the newly initialized matrix
*/
unsigned char **init_matrix(int rows, int cols)
{
	int i, j;
	unsigned char **a;

	a = malloc(rows * sizeof(int *));
	if (!a) {
		return NULL;
	}
	for (i = 0; i < rows; i++) {
		a[i] = malloc(cols * sizeof(int));
		if (!a[i]) {
			for (j = 0; j < i; j++) {
				free(a[j]);
			}
			free(a);
			return NULL;
		}
	}

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			a[i][j] = 0;
		}
	}

	return a;
}

/**
* @remark Freeing the memory allocated for a 2 dimensional array, or a matrix
* @param **A matrix that is being freed
* @param rows the number of rows in the matrix assigned space
*/
void free_matrix(unsigned char **A, int rows)
{
	int i;

	for (i = 0; i < rows; i++) {
		free(A[i]);
	}

	free(A);
}

/**
* @remark The logic determing which cells live or die for the next generation.
* This function has a border all around with permanently dead cells.
* @param **A the initial generation. This generation will be searched through 
* each cell to determine if it dies or lives. After assigning to the next
* generation, the initial is cleared and all life is reset to 0.
* @param **B the next generation. This is the output or next generation. We 
* will record the results of the initial matrix A to matrix B.
* @param rows the number of rows in the matrix assigned space
* @param cols the number of columns in the matrix assigned space
*/
void hedge_life(unsigned char **A, unsigned char **B, int rows, int cols)
{
	int i, j, x, y, chk;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			chk = 0;

			//This for loop sets the boundaries so it doesn't seg fault!
			for (x = -1; x <= 1; x++) {
				for (y = -1; y <= 1; y++) {
					if ((i + x) < rows && (j + y) < cols) 
						if ((i + x) >= 0 && (j + y) >= 0)
							if(A[i + x][j + y] == 1)
								chk += 1;
				}
			}

			if (A[i][j] == 1) {
				chk -= 1;
				if (chk < 2) {
					B[i][j] = 0;
				} else if (chk > 3) {
					B[i][j] = 0;
				} else {
					B[i][j] = 1;
				}
			} else {
				B[i][j] = 0;
				if (chk == 3) {
					B[i][j] = 1;
				}
			}
		}
	}
	
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			A[i][j] = 0;
		}
	}
	
}

/**
* @remark The logic determing which cells live or die for the next generation.
* This function has a border that connects the left and right edges and the
* top and bottom edges.
* @param **A the initial generation. This generation will be searched through 
* each cell to determine if it dies or lives. After assigning to the next
* generation, the initial is cleared and all life is reset to 0.
* @param **B the next generation. This is the output or next generation. We 
* will record the results of the initial matrix A to matrix B.
* @param rows the number of rows in the matrix assigned space
* @param cols the number of columns in the matrix assigned space
*/
void torus_life(unsigned char **A, unsigned char **B, int rows, int cols)
{
	int i, j, x, y, chk, tmp1, tmp2;
	//Two for loops to check every cell in the matrix
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			chk = 0;

			//This for loop checks around the current cell and returns the number of cells alive.
			for (x = -1; x <= 1; x++) {
				for (y = -1; y <= 1; y++) {
					tmp1 = ((i + x) % rows);
					tmp2 = ((j + y) % cols);
					if (tmp1 < 0)
						tmp1 = rows - 1;
					if (tmp2 < 0)
						tmp2 = cols - 1;
					
					if(A[tmp1][tmp2] == 1)
						chk += 1;
				}
			}

			if (A[i][j] == 1) {
				chk -= 1;
				if (chk < 2) {
					B[i][j] = 0;
				} else if (chk > 3) {
					B[i][j] = 0;
				} else {
					B[i][j] = 1;
				}
			} else {
				B[i][j] = 0;
				if (chk == 3) {
					B[i][j] = 1;
				}
			}
		}
	}
	
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			A[i][j] = 0;
		}
	}
	
}

/**
* @remark The logic determing which cells live or die for the next generation.
* This function has a border that connects the top and bottom edges and inverts
* the left and right edges. (the top left is connected with the bottom right,
* the bottom left is connected with the top right.)
* @param **A the initial generation. This generation will be searched through 
* each cell to determine if it dies or lives. After assigning to the next
* generation, the initial is cleared and all life is reset to 0.
* @param **B the next generation. This is the output or next generation. We 
* will record the results of the initial matrix A to matrix B.
* @param rows the number of rows in the matrix assigned space
* @param cols the number of columns in the matrix assigned space
*/
void klein_life(unsigned char **A, unsigned char **B, int rows, int cols)
{
	int i, j, x, y, chk, tmp1, tmp2;
	//Two for loops to check every cell in the matrix
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			chk = 0;

			//This for loop checks around the current cell and returns the number of cells alive.
			for (x = -1; x <= 1; x++) {
				for (y = -1; y <= 1; y++) {
					tmp2 = ((j + y) % cols);
					tmp1 = i + x;
					if (tmp2 < 0)
						tmp2 = cols - 1;
					
					if (tmp1 < 0) {
						tmp2 = cols - tmp2 - 1;
						tmp1 = rows - 1;
					} else if (tmp1 >= rows) {
						tmp2 = cols - tmp2 - 1;
						tmp1 = ((i + x) % rows);						
					}
						
					if(A[tmp1][tmp2] == 1)
						chk += 1;
				}
			}

			if (A[i][j] == 1) {
				chk -= 1;
				if (chk < 2) {
					B[i][j] = 0;
				} else if (chk > 3) {
					B[i][j] = 0;
				} else {
					B[i][j] = 1;
				}
			} else {
				B[i][j] = 0;
				if (chk == 3) {
					B[i][j] = 1;
				}
			}
		}
	}
	
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			A[i][j] = 0;
		}
	}
	
}
