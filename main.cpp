#include <iostream>
#include "matrix.hpp"
#include "cmatrix.hpp"

/*
 * Entry Point
 */
int main() {

    cmatrix r;
    cmatrix c("connectivity.txt");

    r = c.full_process();

    r.print_result();

    return 0;
}