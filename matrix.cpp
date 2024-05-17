#include "matrix.h"

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

void Matrix::T(){
  std::vector<std::vector<double>>vec;
  for(int i = 0; i<Matrix::size.col_size; i++){
    vec.push_back({});
    for(int j = 0; j<Matrix::size.row_size; j++){
      vec[i].push_back(Matrix::matrix[j][i]);
    }
  }
  Matrix::matrix = std::move(vec); //questionable moment. vec is passed as a reference not copied.
  std::swap(Matrix::size.row_size, Matrix::size.col_size);  
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
  for(int i=0; i<row_size; i++){
    vec.push_back({});
    for(int j=0; j<col_size; j++){
      vec[i].push_back(generateRandom(lower_bound, upper_bound));
    }
  }
  return Matrix(vec);  
}


int main(){
  std::vector<std::vector<double>>vec({{1, 2, 3}, {4, 5, 6}});
  Matrix mat(vec);
  std::cout<<mat<<std::endl;
  Matrix mat2 = generateOnes(6, 10);
  Matrix mat3 = generateRandom(10, 2, 0, 1);
  std::cout<<mat3<<'\n';
  mat3.T();
  std::cout<<mat3<<'\n';
  std::cout<<mat3.size.row_size<<" "<<mat3.size.col_size<<'\n';
  std::cout<<mat3+mat3<<"\n";
  return 0;
}
