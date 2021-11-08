#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <tuple>

using namespace std;
using llong = long long;
using l2d_vector = vector<vector<llong>>;

class matrix {
	private:
		l2d_vector matrix_long;
		tuple<int, int> _shape;
		unsigned long nrows{};
		unsigned long ncols{};

		void update_shape(){
			nrows = matrix_long.size();
			ncols = matrix_long[0].size();
			_shape = make_tuple(nrows, ncols);
		}
		
	public:
		explicit matrix(l2d_vector input_matrix) : matrix_long(input_matrix){
			update_shape();
		}
		matrix()= default;

		unsigned long get_nrows() const{return nrows;};
		unsigned long get_ncols() const{return ncols;};
		tuple<int, int> shape(){return _shape;};
		l2d_vector get_vector(){ return matrix_long;}
		vector<llong> get_row(int row) const{return matrix_long[row];};
		vector<llong> get_col(int col) const;
		vector<llong> get_sub_row(int row, int start, int width) const;
        matrix get_sub_matrix(tuple<int, int> start, tuple<int, int> shape) const;
        matrix expand_right(matrix &b);
        matrix stack_bottom(matrix &b);

		friend ostream& operator<<( ostream& outStream, matrix &b );
		friend matrix operator-(const matrix &a,const matrix &b);
		friend matrix operator*(const matrix &a,const matrix &b);
        friend matrix operator+(const matrix &a,const matrix &b);
};
