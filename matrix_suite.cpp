#include "matrix.h"


int main() {
    bool stop = false;
    while(!stop) {
        cout << "\nmatrix calculator\n"
             << "please select an operation: \n"
             << "\n  two matrix operations: \n"
             << "1 - addition\n"
             << "2 - subtraction\n"
             << "3 - multiplication\n"   
             << "\n  single matrix operations: \n"
             << "4 - convert to row echelon form\n"
             << "5 - convert to reduced row echelon form\n"
             << "6 - find determinant\n"
             << "7 - find inverse\n"
             << "8 - multiply by a scalar\n"
             << "\n 0 to exit\n"
             << "\n your selection: ";
        int choice; 
        cin >> choice;
        if(choice == 0)
            stop = true;
	else if(choice < 0) 
	    cout << "\nplease make valid choice\n";
        else if (choice > 8)    	 
	    cout << "\nplease make valid choice\n";
	else if(choice <= 3)
            two_matrix(choice);
        else
            single_matrix(choice);
    }
    cout << "\nexiting\n";
    return 0;
}

//**********functions that deal with 2 matrices ***************

void two_matrix(int choice) {
    matrices mtrs;
    user_input_twomatrix(mtrs);
    int returned = 0;
    if(choice == 1)
        returned = add(mtrs, 1);
    if(choice == 2)
        returned = add(mtrs, -1);
    if(choice == 3) 
        returned = matrix_multiply(mtrs);
    if(returned)
        test_display_twomatrix(mtrs, choice);
    else 
        cout << "\noperation could not be completed due to dimensions\n";
    free_mem_twomatrix(mtrs);
}

//function that allows user to enter 2 matrices of any size
void user_input_twomatrix(matrices & mtrs) {
    cout << "\nenter first matrix"
         << "\nplease enter how many rows: ";
    cin >> mtrs.rows1;
    cout << "\nplease enter how many columns: ";
    cin >> mtrs.columns1;
    
    char col = 'a';
    cout << "\n\n";
    for(int k = 0; k < mtrs.columns1; ++k) 
	cout << "   " << k + 1;
    cout << endl;
    for(int i = 0; i < mtrs.rows1; ++i) {
	cout << char(col+i) << " ";
	for(int k = 0; k < mtrs.columns1; ++k) 
	    cout << "[" << char(col+i) << k+1 << "]";
	cout << endl;
    }
  
    mtrs.matrix1 = new float*[mtrs.rows1];
    for(int i = 0; i < mtrs.rows1; ++i)
        mtrs.matrix1[i] = new float[mtrs.columns1];

    cout << "\n";
    for(int i = 0; i < mtrs.rows1; ++i) {
        for(int k = 0; k < mtrs.columns1; ++k) {
	    cout << char(col+i) << k+1 << ":";
            cin >> mtrs.matrix1[i][k];
        }  
        cout << endl;
    }
    cout << "\nenter matrix to multiply"
         << "\nplease enter how many rows: ";
    cin >> mtrs.rows2;
    cout << "\nplease enter how many columns: ";
    cin >> mtrs.columns2;
    
    cout << "\n\n";
    for(int k = 0; k < mtrs.columns2; ++k) 
	cout << "   " << k + 1;
    cout << endl;
    for(int i = 0; i < mtrs.rows2; ++i) {
	cout << char(col+i) << " ";
	for(int k = 0; k < mtrs.columns2; ++k) 
	    cout << "[" << char(col+i) << k+1 << "]";
	cout << endl;
    }
  
    mtrs.matrix2 = new float*[mtrs.rows2];
    for(int i = 0; i < mtrs.rows2; ++i)
        mtrs.matrix2[i] = new float[mtrs.columns2];

    cout << "\n";
    for(int i = 0; i < mtrs.rows2; ++i) {
        for(int k = 0; k < mtrs.columns2; ++k) {
	    cout << char(col+i) << k+1 << ":";
            cin >> mtrs.matrix2[i][k];
        }  
        cout << endl;
    }
    mtrs.result = NULL;
}


//displays the matrices in the matrices struct
void test_display_twomatrix(matrices & mtrs, int choice) {
    for(int i = 0; i < mtrs.rows1; ++i) {
	for(int k = 0; k < mtrs.columns1; ++k) 
	    cout << "[" << mtrs.matrix1[i][k] << "]";
	cout << endl;
    }
    if(choice == 1)
        cout << "\n Plus \n";
    if(choice == 2)
        cout << "\n Minus \n";
    if(choice == 3)
        cout << "\n Times \n";
    for(int i = 0; i < mtrs.rows2; ++i) {
	for(int k = 0; k < mtrs.columns2; ++k) 
	    cout << "[" << mtrs.matrix2[i][k] << "]";
	cout << endl;
    }
    cout << "\n equals \n\n";
    for(int i = 0; i < mtrs.rows1; ++i) {
	for(int k = 0; k < mtrs.columns2; ++k) 
	    cout << "[" << mtrs.result[i][k] << "]";
	cout << endl;
    }
}

//frees dynamic memory created when new matrix is made
void free_mem_twomatrix(matrices & mtrs) {
    if(mtrs.matrix1) {
	for(int i = 0; i < mtrs.rows1; ++i) {
	    delete mtrs.matrix1[i];
   	    mtrs.matrix1[i] = NULL;
	}
	delete mtrs.matrix1;
	mtrs.matrix1 = NULL;
    }
    if(mtrs.matrix2) {
	for(int i = 0; i < mtrs.rows2; ++i) {
	    delete mtrs.matrix2[i];
   	    mtrs.matrix2[i] = NULL;
	}
	delete mtrs.matrix2;
	mtrs.matrix2 = NULL;
    }
    if(mtrs.result) {
	for(int i = 0; i < mtrs.rows1; ++i) {
	    delete mtrs.result[i];
   	    mtrs.result[i] = NULL;
	}
	delete mtrs.result;
	mtrs.result = NULL;
    }
}


//*************functions that deal with 1 matrix******************

void single_matrix(int choice) {
    int rows, columns;
    float ** matrix = user_input_matrix(rows, columns);
    if(choice == 4) 
        matrix = rref_converter(matrix, rows, columns, 1);
    if(choice == 5)
        matrix = rref_converter(matrix, rows, columns, 0);
    if(choice == 6)
        float det = determinant(matrix, rows);
    if(choice == 7)
        invert(matrix, rows);
    if(choice == 8) {
        cout << "\nMultiply by what scalar? ";
        int scalar;
        cin >> scalar;
        scalar_mult(matrix, scalar, rows, columns); 
    }
    test_display(matrix, rows, columns);
    free_mem(matrix, rows, columns);
}

//function that allows user to enter a matrix of any dimension
float ** user_input_matrix(int & rows, int & columns) {
    cout << "\nplease enter 1 matrix of any size"
         << "\nplease enter how many rows are in the matrix: ";
    rows = 0;
    cin >> rows;
    cout << "\nplease enter how many columns are in the matrix: ";
    columns = 0;
    cin >> columns;
    
    char col = 'a';
    cout << "\n\n";
    for(int k = 0; k < columns; ++k) 
	cout << "   " << k + 1;
    cout << endl;
    for(int i = 0; i < rows; ++i) {
	cout << char(col+i) << " ";
	for(int k = 0; k < columns; ++k) 
	    cout << "[" << char(col+i) << k+1 << "]";
	cout << endl;
    }
  
    float** matrix = new float*[rows];
    for(int i = 0; i < rows; ++i)
        matrix[i] = new float[columns];

    cout << "\n";
    for(int i = 0; i < rows; ++i) {
        for(int k = 0; k < columns; ++k) {
	    cout << char(col+i) << k+1 << ":";
            cin >> matrix[i][k];
        }  
        cout << endl;
    }
    return matrix;
}

//displays matrix passed as arg
void test_display(float ** matrix, int rows, int columns) {
    for(int i = 0; i < rows; ++i) {
	for(int k = 0; k < columns; ++k) 
	    cout << "[" << matrix[i][k] << "]";
	cout << endl;
    }
}

//frees dynamic memory created when new matrix is made
void free_mem(float ** matrix, int rows, int columns) {
    if(matrix) {
	for(int i = 0; i < rows; ++i) {
	    delete matrix[i];
   	    matrix[i] = NULL;
	}
	delete matrix;
	matrix = NULL;
    }
}  
         
