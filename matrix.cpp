#include "matrix.h"
#include <time.h>

namespace deepl{

  double generateRandom(double lower_bound, double upper_bound){
    double val = (double)std::rand() / RAND_MAX;
    return lower_bound + val * (upper_bound - lower_bound);
  }

  Matrix::Matrix(std::vector<std::vector<double>>vec){
    Matrix::matrix = vec;
    Matrix::size.row_size = vec.size();
    if(size.row_size != 0){
      size.col_size = vec[0].size();
    }
    else{
      size.col_size = 0;
    }
  }

  Matrix Matrix::T(){
    std::vector<std::vector<double>>vec;
    for(int i = 0; i<Matrix::size.col_size; i++){
      vec.push_back({});
      for(int j = 0; j<Matrix::size.row_size; j++){
        vec[i].push_back(Matrix::matrix[j][i]);
      }
    }

    return Matrix(vec);
  }

  std::ostream& operator<<(std::ostream& os, const Matrix& matriks){
    int row_length = matriks.matrix.size();
    int col_length = matriks.matrix[0].size();
    for(int i=0; i<row_length; i++){
      for(int j=0; j<col_length; j++){
        os<<matriks.matrix[i][j]<<" ";
      }
      os<<std::endl;
    }
    return os;
  }

  Matrix operator*(Matrix& A, Matrix& B){
    std::vector<std::vector<double>> vec;
    double lin_comb;
    try{
      if(A.size.col_size == B.size.row_size){
        for(int i=0; i<A.size.row_size; i++){
          vec.push_back({});
          for(int j = 0; j<B.size.col_size; j++){
            lin_comb = 0;
            for(int k=0; k<A.size.col_size; k++){
               lin_comb= lin_comb + (A.matrix[i][k] * B.matrix[k][j]);
            }
            vec[i].push_back(lin_comb);
          }
        }
      }

      else{
        throw 505;
      }
    }

    catch(...){
      std::cout<<"Matrix sizes do not match for multiplication"<<std::endl;
    }
    return Matrix(vec);
  }

  Matrix operator+(Matrix& A, Matrix& B){
    std::vector<std::vector<double>>vec;
    try{
      if(A.size.row_size == B.size.row_size && A.size.col_size == B.size.col_size){
        for(int i=0; i<A.size.row_size; i++){
          vec.push_back({});
          for(int j=0; j<A.size.col_size; j++){
            vec[i].push_back(A.matrix[i][j] + B.matrix[i][j]);
          }
        }
      }
      else{
        throw 505;
      }
    }
    catch(...){
      std::cout<<"Matrix sizes don't match for addition"<<std::endl;
    }
    return Matrix(vec);
  }


  Matrix generateNs(double val, const int row_size, const int col_size){
    std::vector<std::vector<double>> vec;
    for(int i=0; i<row_size; i++){
      vec.push_back({});
      for(int j=0; j<col_size; j++){
        vec[i].push_back(val);
      }
    }
    return Matrix(vec);
  }

  Matrix generateZeros(const int row_size, const int col_size){
    return generateNs(0, row_size, col_size);
  }

  Matrix generateOnes(const int row_size, const int col_size){
    return generateNs(1, row_size, col_size);
  }

  Matrix generateRandom(const int row_size, const int col_size, double lower_bound, double upper_bound){
    std::vector<std::vector<double>> vec;
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    for(int i=0; i<row_size; i++){
      vec.push_back({});
      for(int j=0; j<col_size; j++){
        vec[i].push_back(generateRandom(lower_bound, upper_bound));
      }
    }

    return Matrix(vec);  
  }
}

int main(){
  std::vector<std::vector<double>>vec({{1, 2, 3}, {4, 5, 6}});
  deepl::Matrix mat(vec);
  std::cout<<mat<<std::endl;
  deepl::Matrix mat2 = deepl::generateOnes(6, 10);
  deepl::Matrix mat3 = deepl::generateRandom(10, 2, 0, 1);
  //std::cout<<mat3<<mat3.size.row_size<<" "<<mat3.size.col_size<<'\n';
  deepl::Matrix mat4(std::vector<std::vector<double>>({{2, 4}, {6, 8}, {10, 12}}));
  std::cout<<mat4<<'\n';
  deepl::Matrix a = mat*mat4;
  std::cout<<a<<a.size.col_size<<"\n";
  std::cout<<mat3;
  return 0;
}
