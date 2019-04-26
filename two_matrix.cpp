//functions that help test the matrix multiplcation class
#include "m_mult.h"

void user_input_matrix(matrices & mtrs);
void test_display(matrices & mtrs);
void free_mem(matrices & mtrs);



//main calls the user input function, displays the input matrix, calls
//the rref function and then displays the result 
int main() {
    matrices mtrs;
    user_input_matrix(mtrs);
    int result = matrix_multiply(mtrs);
    if(result)
        test_display(mtrs);
    else {
        cout << "matrices of these sizes cannot be multiplied\n"
             << "amount of columns in first matrix must match amount\n"
             << "of rows in second matrix\n";
    }
    return 0;
}

//function that allows user to enter 2 matrices of any size
void user_input_matrix(matrices & mtrs) {
    cout << "\nenter first matrix to multiply"
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
void test_display(matrices & mtrs) {
    for(int i = 0; i < mtrs.rows1; ++i) {
	for(int k = 0; k < mtrs.columns1; ++k) 
	    cout << "[" << mtrs.matrix1[i][k] << "]";
	cout << endl;
    }
    cout << "\n times \n\n";
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
void free_mem(matrices & mtrs) {
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
