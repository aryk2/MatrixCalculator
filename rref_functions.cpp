//functions for rref converter
#include "rref.h"

//this function can be called to start the ref conversion process.
//it requires a int ** matrix and the row, columns of that matrix.
//it returns a reduced matrix 
float ** rref_converter(float **new_matrix, int rows, int columns) {
    converter c;
    c.set_matrix(new_matrix);
    c.dimensions(rows, columns);
    int status = c.convert();
    if(status == 1) {
	return c.get_matrix();
    }
    if(status == 7)
	cout << "\nexiting\n";
    return 0; //only reaches this return if something has gone wrong
}

//inits class members to their 0 value to prep for start
converter::converter() {
    matrix = NULL;
    COLUMNS = 0;
    ROWS = 0;
}

//frees dynamically allocated memory for matrix and NULL's
converter::~converter() {
//there is currently not dynamic mem managed by this class
//the matrix ptr is a ptr to dynamic mem outside of class
}

//display function for 2d array
void converter::display_matrix() {
    for(int i = 0; i < ROWS; ++i) {
        cout << endl;
        for(int k = 0; k < COLUMNS; ++k) {
            cout << matrix[i][k] << "   ";
        }
    }
    cout << endl;
}

//This function takes the inputed dimensions and then sets 
//the corresponding values in the class to those values
void converter::dimensions(int rows, int columns) {
    set_columns(columns);
    set_rows(rows);
}

//This function should check the whole matrix to see if 
//it is in REF form by going through each row, checking
//that the leading coef is equal to 1 and then checking
//that pivot column to see if all other entries are 0
int converter::is_ref() {
    if(!matrix) {
	cout << "\n error with matrix\n";
	return 7;
    }

    //the for loop below iterates through each row of the matrix.
    //for each row, it sets 3 conditions, zeros means all 0 row, 
    //leading is 1 means that leading coef is correct value.
    //clear pivot means that there are no non 0 values below pivot.
    //for each column in a row, it checks if its 0, changes zeros to 
    //false if its not, it its not a zero, it checks if its 1, if it is
    //not a 1, it can return false, this is not in ref form. if it is one
    //it can call a check pivot column. if there are no 0's below the 1 
    //then this column is in ref form and the column for loop can break
    //to the next row. if it is not in ref form, the function can return

    for(int i = 0; i < ROWS; ++i) {
	bool zeros = true;
	bool leading_is_one = false; 
	bool clear_pivot = false;
	for(int k = 0; k < COLUMNS; ++k) {
	    if(matrix[i][k] != 0)
	        zeros = false;  
	    if(!zeros) { 
		if(matrix[i][k] == 1) 
		    clear_pivot = check_pivot(i, k);
		else if(matrix[i][k] != 1) 
		    return false;
	        if(!clear_pivot)
		    return false;
		else
		    break;
	    }
	}  
    }
    
    return true;
}

//this function checks all entries in a column below the 
//leading coeffiecient (called the pivot), this column is listed
//as a pivot column if it has a 1 in the leadinf coef position
//it is in the correct form if there are all 0s below the 1
bool converter::check_pivot(int row, int column) {
    for(int i = row+1; i < ROWS; ++i) {
	if(matrix[i][column] != 0) 
	    return false;
    }
    return true;
}

//This function will go through the matrix and reduce by calling
//helper functions, this function manages the reducing
int converter::convert() {
    int *pivots = new int[ROWS]; //record of pivot column indices
    for(int i = 0; i < ROWS; ++i) 
	pivots[i] = 0;
    bool ref = is_ref();
    if(ref == 7) return ref; //error for matrix being NULL 
    if(ref) return 1; //nothing else needed to convert
    reorder();
    
    for(int i = 0; i < ROWS; ++i) 
	row_reduce(i);
    return 1;
}

//this function reorders the matrix rows so that the initial
//leading coefficients that are in columns closer to 0 are above 
//rows with leading coefficients that are farther from 0

//NOTE the old array has not been freed yet so this is a memleak
void converter::reorder() {
    int *pivots = new int[ROWS]; //record of pivot column indices
    for(int i = 0; i < ROWS; ++i) 
	pivots[i] = 99;
    int max = 0;
    for(int i = 0; i < ROWS; ++i) {
	for(int k = 0; k < COLUMNS; ++k) {
	    if(matrix[i][k] != 0) {
		if(i > max)
		    max = k;
		pivots[i] = k;
		break;
	    }
        }
    }
    if(max > 0) {
        float** reorderedmatrix = new float*[ROWS];
        for(int i = 0; i < ROWS; ++i)
            reorderedmatrix[i] = new float[COLUMNS];
        int index = ROWS - 1;
        while(index >= 0) {
            for(int i = 0; i < ROWS; ++i) {
                if(pivots[i] >= max) {
		    if(max > 0)
		        --max;
		    reorderedmatrix[index] = matrix[i];
		    for(int x = 0; x < COLUMNS; ++x) {
		        reorderedmatrix[index][x] = matrix[i][x];
 	            }
	            pivots[i] = -1;
		    break;
                }	
	    }  
	    --index;
        }
        matrix = reorderedmatrix;
    }
}

//This function reduces a row in the matrix and fixes its pivot
//it does this by first dividing the row by the leading coef
//which makes the leading coef 1 (a condition for rref). it then
//moves down the rows below and 0's out the pivot column
//it then starts at the top and does the same thing so all 
//other entries in the row with the leading coef of this row are 0
void converter::row_reduce(int row) {
    int pivot;
    for(int i = 0; i < COLUMNS; ++i) {
        if(matrix[row][i] != 0) {
	    pivot = i; 	
	    break;
	}
    }
    if(matrix[row][pivot] != 1) {
        float divisor = matrix[row][pivot];
	if(divisor) {
	    for(int i = 0; i < COLUMNS; ++i) 
	        matrix[row][i] = matrix[row][i] / divisor;
        }
    }    
    for(int i = row+1; i < ROWS; ++i) {
	float scalar = matrix[i][pivot];
	for(int k = 0; k < COLUMNS; ++k) {
	    matrix[i][k] = matrix[i][k] - (scalar * matrix[row][k]);
	    if(matrix[i][k] == -0)
		matrix[i][k] = 0;
        }
    }
    if(row != 0) {
	for(int i = 0; i < row; ++i) {
	    float scalar = matrix[i][pivot]; 
            for(int k = 0; k < COLUMNS; ++k) {
		matrix[i][k] = matrix[i][k] - (scalar * matrix[row][k]);
                if(matrix[i][k] == -0)
		    matrix[i][k] = 0;
            }
	}
    }
}

