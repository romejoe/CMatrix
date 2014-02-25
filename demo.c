#include <stdio.h>
#include "Matrix.h"

struct matrix{
	double *_data;
	int _row, _col;
};

int main(){
	struct matrix *a;
	int fileSize;
	char *buff;
	FILE *f = fopen("demo.mat", "r");
	fseek(f,0,SEEK_END);
	fileSize = ftell(f);
	fseek(f,0,SEEK_SET);
	buff = malloc(fileSize+1);
	fread(buff,fileSize,1,f);
	buff[fileSize] = 0x0;
	fclose(f);
	
	a = malloc(sizeof(struct matrix));
	READ_DOUBLE_MATRIX(a, buff);
	printf("rowSize = %d\n", a->_col);
	printf("colSize = %d\n", a->_row);
	printf("a = \n");
	PRINT_MATRIX(a, "%lf");

	return 0;
}
