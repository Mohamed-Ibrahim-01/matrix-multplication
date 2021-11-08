#include "matrix.h"
matrix strassen_mat(matrix A,const matrix& B);

/**
 * Dividing the matrix to 4 matrices of size n/2 * n/2 
 * 
 * @param
 *  A --> a matrix with size 2^n * 2^n
 * 
 * @return
 * A tuple of the 4 matrices from the input matrix.
*/
tuple<matrix, matrix, matrix, matrix> divide(matrix A){
	int nrows, ncols; tie(nrows, ncols) = A.shape();
	tuple<int, int> sub_matrix_shape = make_tuple(nrows/2, ncols/2);
	matrix A11 = A.get_sub_matrix(make_tuple(0,0), sub_matrix_shape);
	matrix A12 = A.get_sub_matrix(make_tuple(0,ncols/2), sub_matrix_shape);
	matrix A21 = A.get_sub_matrix(make_tuple(nrows/2,0), sub_matrix_shape);
	matrix A22 = A.get_sub_matrix(make_tuple(nrows/2,ncols/2), sub_matrix_shape);
	return make_tuple(A11, A12, A21, A22);
}

/**
 * 
 * Merging 4 matrices into one matrix.
 * 
 * @param
 *  C11 --> a matrix with size 2^n * 2^n to fill top left quarter.
 *  C12 --> a matrix with size 2^n * 2^n to fill top right quarter.
 *  C21 --> a matrix with size 2^n * 2^n to fill bottom left quarter.
 *  C22 --> a matrix with size 2^n * 2^n to fill bottom right quarter.
 *
 *         /C11  C12\
 *   C =   |        |
 *         \C21  C21/
 * 
 * @return C
 * A merged matrix of the 4 matrices .
*/
matrix conquer(matrix C11, matrix C12, matrix C21, matrix C22){
	matrix C1 = C11.expand_right(C12);
	matrix C2 = C21.expand_right(C22);
	matrix C = C1.stack_bottom(C2);
	return C;
}

/**
 * Strassen divide and conquer algorithm for matrix multiplication
 * 
 * @param
 *  a --> a matrix with size 2^n * 2^n
 *  b --> a matrix with size 2^n * 2^n
 * 
 * @return
 * the result of a*b "matrix multiplcation" as matrix object.
*/
matrix strassen_mat(matrix A,const matrix& B){
    int nrows, ncols; tie(nrows, ncols) = A.shape();
    if(nrows == 1 && ncols ==1) return A*B;
    matrix A11, A12, A21, A22;
    tie(A11, A12, A21, A22) = divide(A);

    matrix B11, B12, B21, B22;
    tie(B11, B12, B21, B22) = divide(B);

    matrix M1 = strassen_mat((A11+A22), (B11+B22));
    matrix M2 = strassen_mat((A21+A22), (B11));
    matrix M3 = strassen_mat((A11),     (B12-B22));
    matrix M4 = strassen_mat((A22),     (B21-B11));
    matrix M5 = strassen_mat((A11+A12), (B22));
    matrix M6 = strassen_mat((A21-A11), (B11+B12));
    matrix M7 = strassen_mat((A12-A22), (B21+B22));

    matrix C = conquer(M1+M4-M5+M7, M3+M5, M2+M4, M1-M2+M3+M6);
    return C;
}

/**
 * Wrapper Strassen divide and conquer algorithm for matrix multiplication
 * 
 * @param
 *  a --> a 2d vector with size 2^n * 2^n
 *  b --> a 2d vector with size 2^n * 2^n
 * 
 * @return
 * the result of a*b "matrix multiplcation" as 2d vector
*/
l2d_vector strassen(l2d_vector& a,l2d_vector& b){
	matrix A(a), B(b);
	return strassen_mat(A, B).get_vector();
}
