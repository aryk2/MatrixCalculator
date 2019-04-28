#include "matrix.h"

void invert(float ** & matrix, int size) {
    float det = determinant(matrix, size);
    float scalar = 1 / det;
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

//do I need to find cofactor matrix??

//adjugate, (flip)
//then multiply by 1/determinant
