#include "matrix.h"

void invert(float ** & matrix, int size) {
    float det = determinant(matrix, size);
    float scalar = 1 / det;
  
    float * det_array = new float[size * size];
 
    int det_count = 0;
    for(int i = 0; i < size; ++i) {
        for(int k = 0; k < size; ++k) {
            det_array[det_count] = matrix_minor(matrix, size, i, k);
            ++det_count;
        } 
    }

    int index = 0;
    for(int i = 0; i < size; ++i) {
        for(int k = 0; k < size; ++k) {
            matrix[i][k] = det_array[index];
            ++index;
        }
    }
    delete [] det_array;
    
    float ** adjugate = new float * [size];
    for(int i = 0; i < size; ++i) 
        adjugate[i] = new float [size];
    
    transpose(matrix, adjugate, size);

    float ** temp = matrix;
    matrix = adjugate;
    free_mem(temp, size, size);

    cofactor_matrix(matrix, size);

    scalar_mult(matrix, scalar, size, size);
}

float matrix_minor(float ** matrix, int size, int row, int column) {
    int new_size = size -1;
    float ** sub_matrix = new float * [new_size];
    for(int i = 0; i < new_size; ++i) 
        sub_matrix[i] = new float[new_size];
    
    int subrow = 0;
    int subcol = 0;
    for(int i = 0; i < size; ++i) {
        if(i == row)
            continue;
        for(int k = 0; k < size; ++k) {
            if(k == column)
                continue;
            sub_matrix[subrow][subcol] = matrix[i][k];
            if(subcol < new_size -1)
                ++subcol;
            else {
		subcol = 0;
                ++subrow;
            }
        }
    }
    return determinant(sub_matrix, new_size);
}

void cofactor_matrix(float ** & matrix, int size) {
    int negate = 0;
    for(int i = 0; i < size; ++i) {
        for(int k = 0; k < size; ++k) {
            if(negate % 2 != 0)
                matrix[i][k] = matrix[i][k] *-1;
            ++negate;
        }
    }
}

void transpose(float ** matrix, float ** & adjugate, int size) {
    int row = 0;
    int column = 0;
    for(int k = 0; k < size; ++k) {
        for(int i = 0; i < size; ++i) {
            adjugate[row][column] = matrix[i][k];
            if(column < size-1)
                ++column;
            else {
                column = 0;
                ++row;
            }
        }
    }
}
