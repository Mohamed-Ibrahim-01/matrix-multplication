#include "matrix.h"

/**
 * implement the naive matrix multiplication algorithm
 * 
 * @param
 *  a --> a 2d vector
 *  b --> a 2d vector
 * 
 * @return
 * the result of a*b "matrix multiplcation"
*/
l2d_vector naive(l2d_vector a,l2d_vector b){
	matrix A(a), B(b);
    matrix C = A*B;
    return C.get_vector();
}
