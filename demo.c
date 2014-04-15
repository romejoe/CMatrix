#include <stdio.h>
#include "Matrix.h"

struct matrix{
	int *data;
	int row, col;
};

int main(){
	/*struct matrix *a;
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
*/
	FILE *f = fopen("demo.mat", "r");
	struct matrix *a;
	a = malloc(sizeof(struct matrix));
	READ_MATRIX_FILE(f, a, int, 0, " %d ", ",", ";");
	PRINT_MATRIX(a, "%d");

	return 0;
}
