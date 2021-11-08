#include <chrono>
#include <iostream>
#include <random>
#include <iomanip>
#include <vector>
#include "matrix.h"

using std::cout;
using std::endl;
using std::setprecision;
using std::chrono::high_resolution_clock;
using l2d_vector = std::vector<std::vector<llong>>;
using llong = long long;


l2d_vector naive(l2d_vector a,l2d_vector b);
l2d_vector strassen(l2d_vector& a,l2d_vector& b);
/**
 * generate 2 2d-vectors with fixed size 128*128 
 * 
 * @return
 *  a 2d vector with size 128*128 contains random numbers
 * 
 */
l2d_vector generate_random_matrix() {

    constexpr int MIN = 1;
    constexpr int MAX = 10;
    constexpr int ROW_SIZE = 128;
    constexpr int COL_SIZE = 128;

    l2d_vector random_matrix;
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<> distr(MIN, MAX);

    for(unsigned int row_i = 0; row_i < ROW_SIZE; row_i++) {
        vector<llong> new_row ;
        for(unsigned int col_j = 0; col_j < COL_SIZE; col_j++){
            auto random_num = static_cast<llong>(distr(eng));
            new_row.push_back(random_num);
        }
        random_matrix.push_back(new_row);
    }	
    return random_matrix;
}

/**
 * driving stress test for both algorithms
 * 
 * generate 2 2d-vectors with fixed size 128*128
 * compare their output and runnig time
*/
int main(int argc, char **argv)
{

    while (true)
    {
        l2d_vector a = generate_random_matrix();
        l2d_vector b = generate_random_matrix();
        l2d_vector naive_result;
        l2d_vector strassen_result;

        auto naive_start = high_resolution_clock::now();
        // fill this line
        naive_result = naive(a, b);
        matrix A(naive_result);
        auto naive_finish = high_resolution_clock::now();

        auto strassen_start = high_resolution_clock::now();
        // fill this line
        strassen_result = strassen(a, b);
        auto strassen_finish = high_resolution_clock::now();

        auto naive_time = (naive_finish - naive_start).count();
        auto strassen_time = (strassen_finish - strassen_start).count();

        if (strassen_result == naive_result)
        {
            cout << "equivalent result ";
            cout << "naive_time ==> " << naive_time << " *** ";
            cout << "strassen_time ==> " << strassen_time << " *** ";
            cout << "performance loss ==>" << strassen_time / naive_time<< " *** ";
            cout << "performance enhancment ==>" << naive_time / strassen_time << endl;
        }
        else
        {
            cout << "error, check your inputs and algortihms " << endl;
            // you may want to store your variables in a file to re-run the test on the same inputs;
            break;
        }
    }
    return 0;
}

