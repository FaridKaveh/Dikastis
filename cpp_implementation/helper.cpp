#include <vector> 

/* A file for helper function implmentation.*/

std::vector<double> 
populate_vector(double start, double inc, int n){ 

    /* Returns a vector v populated by {start - inc, start - 2* inc, ... , start - n*inc}*/
	std::vector<double> v; 
	v.reserve(n-1);	
	for (int i = 1; i < n; i++){ 
        v.push_back(start - inc*i); 
    }

    return v; 
}

void 
read_from_file(int file){ 
    /* reads the contents of a file stream and prints to stdout*/


    FILE *stream; //the FILE struct identifies a stream and info needed to control it
    stream = fdopen(file, "r"); 
    int c; //fgetc returns an unsigned char cast to an int
    while ((c= fgetc(stream) )!= EOF) { 
        putchar (c); 
    }
    
}

