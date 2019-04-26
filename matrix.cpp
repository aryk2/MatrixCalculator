//functions for inputing a new matrix
#include "rref.h"

//test functions prototype
//this function allows for the input of matrices and will
//hopefully (eventually) test the edge cases automatically
float ** user_input_matrix(int & rows, int & columns);
void test_display(float ** matrix, int rows, int columns);
void free_mem(float ** matrix, int rows, int columns);

//main calls the user input function, displays the input matrix, calls
//the rref function and then displays the result 
int main() {
    int rows, columns;
    float ** new_matrix = user_input_matrix(rows, columns);
    if(new_matrix)
	test_display(new_matrix, rows, columns);
    float ** returned_matrix = rref_converter(new_matrix, rows, columns);
    if(!returned_matrix)
	cout << "ERROR: NOT IN REF FORM\n";
    else {
	cout << "\nRESULTING MATRIX: \n";
        test_display(returned_matrix, rows, columns);
        free_mem(returned_matrix, rows, columns);
    }
    free_mem(new_matrix, rows, columns);
    return 0;
}

//function that allows user to enter a matrix of any dimension
float ** user_input_matrix(int & rows, int & columns) {
    cout << "\nthis function tests the REF converter"
         << "\nplease enter how many rows are in the system: ";
    rows = 0;
    cin >> rows;
    cout << "\nplease enter how many columns are in the system: ";
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
