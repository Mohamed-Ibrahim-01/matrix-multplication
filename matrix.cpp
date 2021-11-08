#include "matrix.h"
#include <numeric>
#include <algorithm>

using llong = long long;

ostream& operator<<( ostream& outStream, matrix &b ) {
	for(unsigned int i = 0; i < b.matrix_long.size(); i++, outStream << endl)
		for(long long & it : b.matrix_long[i])
			outStream << it << ' ';
	outStream.clear();
	return outStream;
}


matrix operator+(const matrix &a,const matrix &b) {
	matrix c;
	if( a.matrix_long.size() != a.matrix_long[0].size() || b.matrix_long.size() != b.matrix_long[0].size())
		cerr << "Can't add up!! Not a square array." << endl;
	else if(a.matrix_long.size() != b.matrix_long[0].size())
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

matrix operator-(const matrix &a,const matrix &b) {
	matrix c;
	if( a.matrix_long.size() != a.matrix_long[0].size() || b.matrix_long.size() != b.matrix_long[0].size())
		cerr << "Can't be subtracted!! Not a square array." << endl;
	else if(a.matrix_long.size() != b.matrix_long[0].size())
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

vector<llong> matrix::get_col(int col)const{
	vector<llong> column;
	for(unsigned int row_i = 0; row_i < this->get_nrows(); row_i++){
		column.push_back(this->matrix_long[row_i][col]);
	}
	return column;
}

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
