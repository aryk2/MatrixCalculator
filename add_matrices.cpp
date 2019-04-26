#include "matrix.h"

int add(matrices & mtrs, int coef) {
    if(mtrs.rows1 != mtrs.rows2)
	return 0;
    if(mtrs.columns1 != mtrs.columns2)
	return 0;
    mtrs.result = new float*[mtrs.rows1];
    for(int i = 0; i < mtrs.rows1; ++i)
	mtrs.result[i] = new float[mtrs.columns1];
    for(int i = 0; i < mtrs.rows1; ++i) {
        for(int k = 0; k < mtrs.columns1; ++i) {
            mtrs.result[i][k] = mtrs.matrix1[i][k] 
            + coef*mtrs.matrix2[i][k];
        }
    }
    return 1;
}
