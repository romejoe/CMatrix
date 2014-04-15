#include <stdlib.h>
#include <stdio.h>

#ifndef ___MATRIX_H___
#define ___MATRIX_H___

#define __DEFAULT_SIZE 32

#define TRIM_WHITESPACE(src) while(isspace(*src)) ++src


#define READ_MATRIX_FILE(f, mat, type, blank, format, delimiter, linesep){\
    int rowSize = -1, curRowSize = 0, i = 0, rowCount = 0;\
    char error = 0;\
    int size = __DEFAULT_SIZE;\
    type *buf = malloc(size * sizeof(type));\
    type tmp;\
    char dummy_char;\
    while(!feof(f)){\
        if( i >= size){\
            size <<= 1;\
            buf = realloc(buf, size * sizeof(type));\
        }\
        if(fscanf(f, format, &tmp) != 1) break;\
        buf[i] = tmp;\
        ++i;\
        ++curRowSize;\
        if(fscanf(f, " %[" delimiter linesep "]", &dummy_char) == 1){\
            if(dummy_char == delimiter[0]){\
                dummy_char = 0;\
            }\
            else{\
                if(rowSize == -1){\
                    if(curRowSize == 0){\
error = 1; break;\
}\
                    rowSize = curRowSize;\
                }\
                else if(rowSize < curRowSize){\
error = 1; break;\
}\
                else while(curRowSize < rowSize){\
                    if( i >= size){\
                        size <<= 1;\
                        buf = realloc(buf, size * sizeof(type));\
                    }\
                    buf[i] = blank;\
                    ++i;\
                    ++curRowSize;\
                    ++tmp;\
                }\
                curRowSize = 0;\
                ++rowCount;\
            }\
        }\
        else{\
            error = 1;\
            break;\
        }\
    }\
\
    if(error){\
        printf("Error Reading Matrix\n"); exit(-1);\
    }\
    (mat)->data = buf;\
    (mat)->row = rowCount;\
    (mat)->col = rowSize;\
}


#define READ_DOUBLE_MATRIX(mat, src){\
        int physicalSize = __DEFAULT_SIZE * sizeof(double), rowSize = -1, curRowSize = 0, i = 0, rowCount = 0;\
        double *tmp = malloc(physicalSize);\
        char *localSrc = src;\
        TRIM_WHITESPACE(localSrc);\
        while(*localSrc){\
            switch(*localSrc){\
            case ' ':\
            case '\t':\
            case '\v':\
            case '\f':\
            case '\r':\
                ++localSrc;\
                break;\
            case '\n':\
                if(rowSize == -1){\
                    if(curRowSize == 0){\
                        break;\
                    }\
                    else{\
                        rowSize = curRowSize;\
                    }\
                }\
                else{\
                    while(curRowSize < rowSize){\
                        if(i == physicalSize) {physicalSize = physicalSize<< 1;tmp = realloc(tmp, physicalSize);}\
                        tmp[i] = 0.0;\
                        ++i;\
                        ++curRowSize;\
                    }\
                }\
                curRowSize = 0;\
                ++rowCount;\
                ++localSrc;\
                break;\
            case '+':\
            case '-':\
            case '.':\
            case '0':\
            case '1':\
            case '2':\
            case '3':\
            case '4':\
            case '5':\
            case '6':\
            case '7':\
            case '8':\
            case '9':\
                if(i == physicalSize) {physicalSize = physicalSize<< 1;tmp = realloc(tmp, physicalSize);}\
                tmp[i] = atof(localSrc);\
                ++i;\
                ++curRowSize;\
                while(!isspace(*localSrc) && *localSrc != 0) ++localSrc;\
                break;\
            default:\
                break;\
            }\
        }\
        mat->data = tmp;\
        mat->row = rowCount;\
        mat->col = rowSize;\
    }

#define INIT_MATRIX(mat, row, col, type) \
    mat = malloc(sizeof(struct matrix)); \
    mat->data = malloc(sizeof(type) * row * col); \
    mat->row = row; \
    mat->col = col

#define INIT_DOUBLE_MATRIX(mat, row, col) \
    INIT_MATRIX(mat, row, col, double)


#define GET_MATRIX_ADDR(mat, _row, _col) \
    (mat)->data[(_row) * (mat)->col + (_col)]

#define COPY_MATRIX_XY(src, dst, r1, r2, c1, c2, type){\
        int x, y;\
        int i, colSize = ((c2) - (c1)) * sizeof(type);\
        for (x = r1, i = 0; x <= r2; ++x) {\
            memcpy(&(GET_MATRIX_ADDR(dst, i, 0)), &(GET_MATRIX_ADDR(src, x, c1)), colSize); \
        }\
    }

#define COMPARE_MATRIX_SIZE(a,b) \
    ((a->row == b->row) && (a->col == b->col))

#define GET_MATRIX_VAL(mat, row, col)  \
    GET_MATRIX_ADDR(mat, row, col)

#define SET_MATRIX_VAL(mat, row, col, val)  \
    GET_MATRIX_ADDR(mat, row, col) = val


#define SUM_MATRICES(a,b,c){\
        if(!COMPARE_MATRIX_SIZE(a,b) || !COMPARE_MATRIX_SIZE(b,c)){\
            raise(SIGFPE);\
        }\
        int i, j;\
        for(i = 0; i < a->row; ++i){\
            for(j = 0; j < a->col; ++j){\
                GET_MATRIX_ADDR(c, i, j) = \
                                           GET_MATRIX_ADDR(a, i, j) + \
                                           GET_MATRIX_ADDR(b, i, j); \
            }\
        }

#define MUL_MATRICES(a,b,c){\
        int x,y,i;\
        for(x = 0; x < a->row; ++x){\
            for(y = 0; y < b->col; ++y){\
                GET_MATRIX_ADDR(c, x, y) = 0.0;\
                for(i = 0; i < b->row; ++i){\
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
        for(x = 0; x < (a)->row; ++x){\
            for(y = 0; y < (a)->col -1 ; ++y){\
                printf(format ", ", GET_MATRIX_VAL(a, x, y));\
            }\
            printf(format "\n", GET_MATRIX_VAL(a, x, y));\
        }\
    }

#define FREE_MATRIX(mat) \
    free(mat->data); \
    free(mat)

#endif
