#include <vector> 
#include "math.h"

std::vector<double> populate_vector(double start, double inc, int n){ 
	std::vector<double> v; 
	v.reserve(n-1);	
	for (int i = 1; i < n; i++){ 
        v.push_back(start - inc*i); 
    }

    return v; 
}

