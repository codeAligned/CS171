#include "matrix.h"
#include <iostream>

int main(int argc, char *argv[])
{

  int cols = 4;
  int rows = 4;
  Matrix A = Matrix(rows, cols);

  // fill in some values in matrix a
  int count = 0;
  for (int r = 1; r <= rows; r++) {
    for (int c = 1; c <= cols; c++) {
      count ++;
      A(r, c) = count;
    }
  }

  // change some values
  A(1,1) = 0;
  A(2,1) = 1.23;
  A(3,3) = 10;

  std::cout << "Creating a 4x4 matrix..." << std::endl;
  std::cout << "A=" << std::endl;
  A.print();
  std::cout << " " << std::endl;

  
  // test copying a matrix
  Matrix B = A;
  B.multiply(3);
  std::cout << "TESTING SCALAR MULTIPICATION!" << std::endl;
  std::cout << "B = 3 * A" << std::endl;
  std::cout << "B=" << std::endl;
  B.print();  
  std::cout << " " << std::endl;


  Matrix C = A * B;

  std::cout << "TESTING MATRIX MULTIPICATION!" << std::endl;
  std::cout << "C = A * B" << std::endl;
  std::cout << "C=" << std::endl;
  C.print();  
  std::cout << " " << std::endl;

  Matrix D = Matrix(4,1);
  D(1,1) = 3;
  D(2,1) = 2;
  D(3,1) = 1;
  std::cout << "Creating a 4x1 Vector" << std::endl;
  std::cout << "D=" << std::endl;
  D.print();  
  std::cout << " " << std::endl;

  Matrix E = A * D;

  std::cout << "TESTING MATRIX * VECTOR MULTIPLICATION!" << std::endl;
  std::cout << "E = A * D" << std::endl;
  std::cout << "E=" << std::endl;
  E.print();  
  std::cout << " " << std::endl;

  std::cout << "TESTING DOT PRODUCT!" << std::endl;
  std::cout << "Dot Product of E and D = " << E.dot(D) << std::endl;
  std::cout << " " << std::endl;

  std::cout << "TESTING MATRIX TRANSPOSE!" << std::endl;
  Matrix Atrans = A.transpose();
  std::cout << "Atrans = Tranpose of A" << std::endl;
  std::cout << "Atrans=" << std::endl;
  Atrans.print();  
  std::cout << " " << std::endl;

  std::cout << "TESTING MATRIX INVERSE!" << std::endl;
  Matrix AtransInv = Atrans.invert();
  std::cout << "AtransInv = Inverse of Atrans" << std::endl;
  std::cout << "AtransInv=" << std::endl;
  AtransInv.print();  
  std::cout << " " << std::endl;

  std::cout << "TESTING MATRIX INVERSE MULTIPLIED BY MATRIX!" << std::endl;
  Matrix AtransXinv = Atrans * AtransInv;
  std::cout << "AtransXinv = Atrans * AtransInv" << std::endl;
  std::cout << "(Note that this should be the unit matrix)" << std::endl;
  std::cout << "AtransXinv=" << std::endl;
  AtransXinv.print();  
  std::cout << "(Note that we have at least 15 digits of accurate precision in this case)" << std::endl;
  std::cout << " " << std::endl;

  std::cout << "TESTING MATRIX ADDITION!" << std::endl;
  Matrix F = A + B;
  std::cout << "F = A + B" << std::endl;
  std::cout << "F=" << std::endl;
  F.print();  
  std::cout << " " << std::endl;

  std::cout << "TESTING MATRIX SCALAR MULTIPLICATION!" << std::endl;
  Matrix G = F;
  G.multiply(3);
  std::cout << "G = 3 * F" << std::endl;
  std::cout << "G=" << std::endl;
  G.print();  
  std::cout << " " << std::endl;



  /*
  if (C == A) {
    std::cout << "YES C = A!" << std::endl;
  } else {
    std::cout << "ERROR" << std::endl;
  }

  C += B;
  std::cout << "C += B" << std::endl;
  C.print();  
  std::cout << " " << std::endl;

  std::cout << "Making a 3x1 Vector!" << std::endl;
  Matrix D = Matrix(3,1);
  D(1,1) = 3;
  D(2,1) = 2;
  D(3,1) = 1;
  std::cout << "D=" << std::endl;
  D.print();  
  std::cout << " " << std::endl;

  std::cout << "Determinant of C = " << C.determinant() << std::endl;

  int ecount = 0;
  Matrix E = Matrix(4,4);
  for (int r = 1; r <= 4; r++) {
    for (int c = 1; c <= 4; c++) {
      ecount ++;
      E(r, c) = ecount;
    }
  }
  E(3,3) = -5;
  E(1,2) = 3.24;


  std::cout << "E=" << std::endl;
  E.print();  
  std::cout << " " << std::endl;

  std::cout << "Determinant of E = " << E.determinant() << std::endl;

  Matrix F = C * D;
  std::cout << "F= C * D  (TESTING MATRIX MULTIPLICATION)" << std::endl;
  std::cout << "F=" << std::endl;
  F.print();  
  std::cout << " " << std::endl;

  std::cout << "Dot Product of F and D = " << F.dot(D) << std::endl;

  std::cout << "Normalizing F..." << std::endl;
  F.normalize();
  std::cout << "F=" << std::endl;
  F.print();  
  std::cout << " " << std::endl;

  std::cout << "Homogenizing F..." << std::endl;
  F.homogenize();
  std::cout << "F=" << std::endl;
  F.print();  
  std::cout << " " << std::endl;

  std::cout << "G = Tranpose of F" << std::endl;
  Matrix G = F.transpose();
  std::cout << "G=" << std::endl;
  G.print();  
  std::cout << " " << std::endl;

  std::cout << "Et = Tranpose of E" << std::endl;
  Matrix Et = E.transpose();
  std::cout << "Et=" << std::endl;
  Et.print();  
  std::cout << " " << std::endl;

  Matrix ETransInv = Et.invert();
  std::cout << "Inverse of Et=" << std::endl;
  ETransInv.print();  
  std::cout << " " << std::endl;

  std::cout << "C=" << std::endl;
  C.print();  
  std::cout << " " << std::endl;

  Matrix CTrans = C.invert();
  std::cout << "Inverse of C=" << std::endl;
  CTrans.print();
  std::cout << " " << std::endl;
  */



 
  return 0;
}
