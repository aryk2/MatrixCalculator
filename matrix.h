//header file for rref converter
#include <iostream>
using namespace std;

//function prototypes for matrix_suite.cpp file

//struct for two matrix functions
struct matrices;
void two_matrix(int choice);
void user_input_twomatrix(matrices & mtrs);
void test_display_twomatrix(matrices & mtrs);
void free_mem_twomatrix(matrices & mtrs);

void single_matrix(int choice);
float ** user_input_matrix(int & rows, int & columns);
void test_display(float ** matrix, int rows, int columns);
void free_mem(float ** matrix, int rows, int columns);


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

//struct for two matrix functions
struct matrices {
    int rows1;
    int rows2;
    int columns1;
    int columns2;
    float ** matrix1;
    float ** matrix2;
    float ** result;
};
