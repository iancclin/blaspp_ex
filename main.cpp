#include <iostream>
#include <vector>
#include <blas.hh>

void printMatrix(const std::vector<double> &mat, int64_t m, int64_t n) {
  for (auto i = 0; i < m; ++i) {
    for (auto j = 0; j < n; ++j) {
      printf("%.8f, ", mat[i+j*m]);
    }
    printf("\n");
  }
}

#ifdef WITH_CUDA
int main() {
  blas::Op transA = blas::Op::NoTrans;
  blas::Op transB = blas::Op::NoTrans;
  int64_t Am = 10, An = 5, Bm = An, Bn = 3, Cm = Am, Cn = Bn;
  int64_t lda = Am, ldb = Bm, ldc = Cm;
  std::vector<double> A(Am*An), B(Bm*Bn), C(Cm*Cn, 0.0);

  double alpha = 1.5, beta = 0.0;
  for (auto i = 0; i < A.size(); ++i) {
    A[i] = i;
  }
  std::cout << "mat A: " << std::endl;
  printMatrix(A, Am, An);

  for (auto i = 0; i < B.size(); ++i) {
    B[i] = A.size() + i;
  }
  std::cout << "mat A: " << std::endl;
  printMatrix(B, Bm, Bn);

  int device;
  cudaGetDevice(&device);
  blas::Queue queue(device, 0);
  double *dA, *dB, *dC;
  dA = blas::device_malloc<double>(Am*An);
  dB = blas::device_malloc<double>(Bm*Bn);
  dC = blas::device_malloc<double>(Cm*Cn);

  blas::device_setmatrix(Am, An, A.data(), lda, dA, lda, queue);
  blas::device_setmatrix(Bm, Bn, B.data(), ldb, dB, ldb, queue);
  blas::device_setmatrix(Cm, Cn, C.data(), ldc, dC, ldc, queue);

  blas::gemm(blas::Layout::ColMajor, transA, transB,  Am,  Cn,  An, alpha, dA, lda, dB, ldb, beta, dC, ldc, queue);

  std::cout << "mat C: " << std::endl;
  printMatrix(C, Cm, Cn);

  blas::device_getmatrix(Cm, Cn, dC, ldc, C.data(), ldc, queue);

  std::cout << "mat C: " << std::endl;
  printMatrix(C, Cm, Cn);



  return 0;
}
#else
int main() {
  blas::Op transA = blas::Op::NoTrans;
  blas::Op transB = blas::Op::NoTrans;
  int64_t Am = 10, An = 5, Bm = An, Bn = 3, Cm = Am, Cn = Bn;
  int64_t lda = Am, ldb = Bm, ldc = Cm;
  std::vector<double> A(Am*An), B(Bm*Bn), C(Cm*Cn, 0.0);
  double alpha = 1.5, beta = 0.0;
  for (auto i = 0; i < A.size(); ++i) {
    A[i] = i;
  }
  std::cout << "mat A: " << std::endl;
  printMatrix(A, Am, An);

  for (auto i = 0; i < B.size(); ++i) {
    B[i] = A.size() + i;
  }
  std::cout << "mat A: " << std::endl;
  printMatrix(B, Bm, Bn);

  blas::gemm(blas::Layout::ColMajor, transA, transB,  Am,  Cn,  An, alpha, A.data(), lda, B.data(), ldb, beta, C.data(), ldc);

  std::cout << "mat C: " << std::endl;
  printMatrix(C, Cm, Cn);

  return 0;
}
#endif
