#include "matrix.h"

void invert(float ** & matrix, int size) {
    float det = determinant(matrix, size);
    float scalar = 1 / det;
    scalar_mult(matrix, scalar, size, size);
}

//wat is left to fix
//cofactors, (every other negative)
//adjugate, (flip)
//then multiply by 1/determinant
