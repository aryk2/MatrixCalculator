#include "matrix.h"

void invert(float ** & matrix, int size) {
    float det = determinant(matrix, size);
    float scalar = 1 / det;

    float ** sub_matrix = new float * [size -1];
    for(int i = 0; i < size; ++i) 
        sub_matrix[i] = new float [size];
  
    float * det_array = new float[size * size];
 
    int det_count = 0;
    for(int i = 0; i < size; ++i) {
        for(int k = 0; k < size; ++k) {
            int row = 0; 
            int column = 0;
            for(int x = 0; x < size; ++x) {
                for(int y = 0; y < size; ++y) {
                    if(x == i)
                        continue;
                    if(y == k)
                        continue;
                    sub_matrix[row][column] = matrix[x][y];
                    if(column < size-1)
                        ++column;
                    else {
                        column = 0;
                        ++row;
                    }
                }
                det_array[det_count] = determinant(sub_matrix, size-1); 
                ++det_count;
            }
        }
    }

    int index = 0;
    for(int i = 0; i < size; ++i) {
        for(int k = 0; k < size; ++k) {
            matrix[i][k] = det_array[index];
            ++index;
        }
    }
    
    float ** adjugate = new float * [size];
    for(int i = 0; i < size; ++i) 
        adjugate[i] = new float [size];
    
    int row = 0;
    int column = 0;
    for(int k = 0; k < size; ++k) {
        for(int i = 0; i < size; ++i) {
            adjugate[row][column] = matrix[i][k];
            if(column < size)
                ++column;
            else {
                column = 0;
                ++row;
            }
        }
    }              

    int negate = 0;
    for(int i = 0; i < size; ++i) {
        for(int k = 0; k < size; ++k) {
            if(negate % 2 != 0)
                matrix[i][k] = matrix[i][k] *-1;
            ++negate;
        }
    }
    
    scalar_mult(matrix, scalar, size, size);
}

//wat is left to fix
//print each phase and find small error that is changing result
