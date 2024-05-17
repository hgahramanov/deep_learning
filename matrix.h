#include <iostream>
#include <vector>
#include <math.h>

struct dimension{
  int row_size;
  int col_size;
};

class Matrix{
  public:
    std::vector<std::vector<double>> matrix;
    dimension size;
    Matrix(std::vector<std::vector<double>>);
    Matrix()=default;
    ~Matrix(){};
    dimension getSize(){
      return size;
    }
    friend Matrix generateNs(double val, const int row_size, const int col_size);
    friend Matrix generateZeros(const int row_size, const int col_size);
    friend Matrix generateOnes(const int row_size, const int col_size);
    friend Matrix generateRandom(const int row_size, const int col_size, double lower_bound, double upper_bound); //between the range
    friend Matrix operator*(Matrix&, Matrix&);
    void T();
    friend std::ostream& operator<<(std::ostream&, const Matrix&);
};
