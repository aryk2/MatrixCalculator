//header file for rref converter
#include <iostream>
using namespace std;

//this is an outside function that creates the class and starts
//the converter which makes the process more useful because 
//the converter becomes a function that can be called instead 
//of calling itsself in main. 
float ** rref_converter(float **new_matrix, int rows, int columns);

//class interface
//this is the class that manages the converter, it has data members 
//for the matrix and its dimensions. I decided to use a class for
//this to reduce the amount of args for each function. all functions
//that touch the matrix after it has been inputted are members 
class converter {
  public:
    converter();
    ~converter();

    void set_matrix(float ** new_matrix) {matrix = new_matrix;}
    void set_columns(int mcolumns) {COLUMNS = mcolumns;}
    void set_rows(int mrows) {ROWS = mrows;}
    float ** get_matrix() {return matrix;}

    void display_matrix();
    void dimensions(int rows, int columns);
    int make_matrix();
    int is_ref();
    int convert();
    bool check_pivot(int row, int column);
    void reorder();
    void row_reduce(int i);
  private:
    float ** matrix;
    int COLUMNS;
    int ROWS;
};

