#ifndef HELPER_H
#define HELPER_H
#include <iostream>
#include <vector>

/* header file for helper functions*/

std::vector<double> 
populate_vector(double start, double inc, int n); 

void 
read_from_file(int file);

void 
slice_c_str(char * str, char * buffer, size_t start, size_t end); 
#endif
