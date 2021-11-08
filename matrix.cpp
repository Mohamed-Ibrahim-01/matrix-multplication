#include "matrix.h"
#include <numeric>
#include <algorithm>

using llong = long long;
/**
 * Printing the matrix by overloading << operator (can be used with cout or any out stream).
 *
 * Elements of a row are printed with a single space between and after 
 * each row a new line is created.
 *
 * @param outStream an ostream object used to write the data.
 * @param b is the matrix to be printed.
 * @return outStream after clearing it.
 */
ostream& operator<<( ostream& outStream, matrix &b ) {
	for(unsigned int i = 0; i < b.matrix_long.size(); i++, outStream << endl)
		for(long long & it : b.matrix_long[i])
			outStream << it << ' ';
	outStream.clear();
	return outStream;
}


/**
 * Adding to matrices together by overloading + operator 
 *
 * Each element in matrix a is added with its corresponding element in matrix b. The size
 * have to matched to perform addition else error is thron.
 *
 * @param a first matrix to add
 * @param b second matrix to add
 * @return c new matrix of the added a, b
 */
matrix operator+(const matrix &a,const matrix &b) {
	matrix c;
	if(a.shape() != b.shape())
		cerr << "Can't add up!! The two matrices are different in size." << endl;
	else {
		for(unsigned int i = 0; i < a.matrix_long.size(); i++) {
			vector<llong> results_int;
			for(unsigned int j = 0; j < a.matrix_long.size(); j++) {
				results_int.push_back(a.matrix_long[i][j] + b.matrix_long[i][j]);
			}
			c.matrix_long.push_back(results_int);
		}
	}
    c.update_shape();
    return c;
}

/**
 * Adding to matrices together by overloading - operator 
 *
 * Each element in matrix a is subtracted with its corresponding element in matrix b. The size
 * have to matched to perform addition else error is thron.
 *
 * @param a first matrix to subtract from
 * @param b second matrix to subtract with
 * @return c new matrix of the subtracted a, b
 */
matrix operator-(const matrix &a,const matrix &b) {
	matrix c;
	if(a.shape() != b.shape())
		cerr << "Can't be subtracted!! The two matrices are different in size." << endl;
	else {
		for(unsigned int i = 0; i < a.matrix_long.size(); i++) {
			vector<llong> results_int;
			for(unsigned int j = 0; j < a.matrix_long.size(); j++) {
				results_int.push_back(a.matrix_long[i][j] - b.matrix_long[i][j]);
			}
			c.matrix_long.push_back(results_int);
		}
	}
    c.update_shape();
	return c;
}

/**
 * Adding to matrices together by overloading - operator 
 *
 * Each element in matrix a is subtracted with its corresponding element in matrix b. The size
 * have to matched to perform addition else error is thron.
 *
 * @param a first matrix to subtract from
 * @param b second matrix to subtract with
 * @return c new matrix of the subtracted a, b
 */
matrix operator*(const matrix &a,const matrix &b) {
	matrix c;
	if(a.matrix_long[0].size() != b.matrix_long.size())
		cerr << "Can't multiply!!" << endl;
	else {
		for(int row_i = 0; row_i < a.get_nrows(); row_i++) {
			vector<llong> results;
			auto curr_row = a.get_row(row_i);
			for(int col_j = 0; col_j < b.get_ncols(); col_j++){
				auto curr_col = b.get_col(col_j);
				llong result_ij = inner_product(
					begin(curr_row), end(curr_row), begin(curr_col), 0L
				);
				results.push_back(result_ij);
			}
			c.matrix_long.push_back(results);
		}	
	}
    c.update_shape();
	return c;
}

/**
 * Getting column data by index. 
 *
 * Each element in the column index given is collected in a vector and returned 
 *
 * @param col index of the column needed
 * @return column a vector contains a sepecific column data. 
 */
vector<llong> matrix::get_col(int col)const{
	vector<llong> column;
	for(unsigned int row_i = 0; row_i < this->get_nrows(); row_i++){
		column.push_back(this->matrix_long[row_i][col]);
	}
	return column;
}

/**
 * Getting a portion of a row (sub row)
 *
 * A subset of row elements collected from a starting sepecific colmun index.
 *
 * @param row index of the row to get sub set from.
 * @param col index of the column to start with. 
 * @param width num of elements to be returned. 
 * @return sub_row a vector contains a subset of row.
 */

vector<llong> matrix::get_sub_row(int row, int start, int width) const{
	vector<llong> sub_row;
	int max_row_width = static_cast<int>(ncols) - start+1;
	bool valid_width = max_row_width - width > 0;
	if(!valid_width && row < nrows && start < nrows-1)
		cerr << "Not valid size" << endl;
	else{
		vector<llong> complete_row = this->get_row(row);
		for(unsigned int i = 0; i < width; i++){
			sub_row.push_back(complete_row[i+start]);
		}
	}
	return sub_row;
}

/**
 * Getting a sub matrix of a valid size from any starting point.
 *
 * get_sub_row method is usd to get a sub row with a number of columns 
 * and the process is repeated for the required number of rows.
 *
 * @param start index of the starting position (have to be top right) as tuple.
 * @param shape subset matrix shape (#rows, #columns) as tuple.
 * @return sub_matrix the required sub_matrix. 
 */
matrix matrix::get_sub_matrix(tuple<int, int> start, tuple<int, int> shape) const{
	l2d_vector sub_matrix;
	int start_row, start_col; tie(start_row, start_col) = start;
	int nsub_rows, nsub_cols; tie(nsub_rows, nsub_cols) = shape;
	if(
		start_row >= 0 && start_row < nrows &&
		start_col >= 0 && start_col < ncols &&
		ncols - start_col+1 - nsub_cols > 0 &&
		static_cast<int>(nrows - start_row+1 - nsub_rows) > 0
	)
	for(int i = 0; i < nsub_rows; i++){
		sub_matrix.push_back(get_sub_row(i+start_row, start_col, nsub_cols));
	}
	else return {};
	return matrix(sub_matrix);
}

/**
 * Expanding matrix from the right with another matrix of same number of rows. 
 *
 * Each row in the base matrix is expanded (transformed by appending from back) 
 * with the corresponding row in the expanding matrix.
 *
 * @param b a matrix to expand the base matrix (current matrix of the calling object) with.
 * @return expanded_matrix the required exapnded matrix.
 */
matrix matrix::expand_right(matrix &b){
	l2d_vector expanded = this->matrix_long;
	if(this->get_nrows() != b.get_nrows())
		cerr << "Can't expand to right, rows not matched" << endl;
	else{
		transform(begin(b.matrix_long), end(b.matrix_long), begin(expanded), begin(expanded),
				[](const auto& b_row, auto& expanded_row) {
					expanded_row.insert(end(expanded_row), begin(b_row), end(b_row));
					return expanded_row;
				}
		);
	}
    matrix expanded_matrix(expanded);
    return expanded_matrix;
}

/**
 * Expanding matrix from the bottom (Stacking) with another matrix of same number of columns.
 *
 * Each row in the expanding matrix is taken and appended as a whole new row in the base
 * matrix.
 *
 * @param b a matrix to expand the base matrix (current matrix of the calling object) with.
 * @return expanded_matrix the required exapnded matrix.
 */
matrix matrix::stack_bottom(matrix &b){
	l2d_vector stacked = this->matrix_long;
	if(this->get_ncols() != b.get_ncols())
		cerr << "Can't stack together, columns not matched" << endl;
	else{
		for(const auto& row : b.matrix_long){
			stacked.push_back(row);
		}
	}
    return matrix(stacked);
}
