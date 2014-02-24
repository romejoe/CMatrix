#include <stdlib.h>
#include <stdio.h>

#ifndef ___MATRIX_H___
#define ___MATRIX_H___

#define INIT_MATRIX(mat, row, col, type) \
	mat = malloc(sizeof(struct matrix)); \
	mat->_data = malloc(sizeof(type) * row * col); \
	mat->_row = row; \
	mat->_col = col

#define INIT_DOUBLE_MATRIX(mat, row, col) \
	INIT_MATRIX(mat, row, col, double)


#define GET_MATRIX_ADDR(mat, row, col) \
	(mat)->_data[(row) * (mat)->_col + (col)]

#define COPY_MATRIX_XY(src, dst, r1, r2, c1, c2, type){\
		int x, y;\
		int i, colSize = ((c2) - (c1)) * sizeof(type);\
		for (x = r1, i = 0; x <= r2; ++x) {\
			memcpy(&(GET_MATRIX_ADDR(dst, i, 0)), &(GET_MATRIX_ADDR(src, x, c1)), colSize); \
		}\
	}

#define COMPARE_MATRIX_SIZE(a,b) \
	((a->_row == b->_row) && (a->_col == b->_col))

#define GET_MATRIX_VAL(mat, row, col)  \
	GET_MATRIX_ADDR(mat, row, col)

#define SET_MATRIX_VAL(mat, row, col, val)  \
	GET_MATRIX_ADDR(mat, row, col) = val


#define SUM_MATRICES(a,b,c){\
		if(!COMPARE_MATRIX_SIZE(a,b) || !COMPARE_MATRIX_SIZE(b,c)){\
			raise(SIGFPE);\
		}\
		int i, j;\
		for(i = 0; i < a->_row; ++i){\
			for(j = 0; j < a->_col; ++j){\
				GET_MATRIX_ADDR(c, i, j) = \
				                           GET_MATRIX_ADDR(a, i, j) + \
				                           GET_MATRIX_ADDR(b, i, j); \
			}\
		}

#define MUL_MATRICES(a,b,c){\
		int x,y,i;\
		for(x = 0; x < a->_row; ++x){\
			for(y = 0; y < b->_col; ++y){\
				GET_MATRIX_ADDR(c, x, y) = 0.0;\
				for(i = 0; i < b->_row; ++i){\
					GET_MATRIX_ADDR(c, x, y) =  \
					                            GET_MATRIX_ADDR(c, x, y) +\
					                            GET_MATRIX_ADDR(a, x, i) *\
					                            GET_MATRIX_ADDR(b, i, y);\
				}\
			}\
		}\
	}

#define PRINT_MATRIX(a, format) {\
		int x, y;\
		for(x = 0; x < a->_row; ++x){\
			for(y = 0; y < a->_col - 1; ++y){\
				printf(format ", ", GET_MATRIX_VAL(a, x, y));\
			}\
			printf(format "\n", GET_MATRIX_VAL(a, x, y));\
		}\
	}

#define FREE_MATRIX(mat) \
	free(mat->_data); \
	free(mat)

#endif
